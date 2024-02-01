We used `ifconfig` to find the address :
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

then, we used `nmap`