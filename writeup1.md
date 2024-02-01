- We used `ifconfig` to find the address :
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

- So our first idea was to try and reach the website hosted on the server. To do so, we used dirsearch:

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

- By visiting the forum, we saw a post by user lmezard on a thread called "Probleme login ?" which is a huge copy/paste of a connection log. In this log, we saw a suspicious line with what looked like a password 

```
Oct 5 08:45:29 BornToSecHackMe sshd[7547]: Failed password for invalid user !q\]Ej?*5K5cy*AJ from 161.202.39.38 port 57764 ssh2
```
With this password we can connect to the session of lmezard on the forum.
On his profile we can find her email address :
`laurie@borntosec.net`