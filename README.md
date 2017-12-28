# tcp_dedup
tcp Deduplication 
work as tcp port forward.

server :
./tcptunnel --local-port=3333 --remote-port=80 --remote-host=127.0.0.1 --stay-alive --asserver


client:
./tcptunnel --local-port=4444 --remote-port=3333 --remote-host=10.29.24.99 --stay-alive

wget http://127.0.0.1:4444/dd/Python-2.7.13.tar.xz -O /dev/null


2017-12-28 12:30:19 (85.3 MB/s) - '/dev/null' saved [12495628/12495628]

root@ubuntu:/tmp# LANG=en_US wget http://127.0.0.1:4444/dd/Python-2.7.13.tar.xz -O /dev/null
--2017-12-28 12:30:19--  http://127.0.0.1:4444/dd/Python-2.7.13.tar.xz
Connecting to 127.0.0.1:4444... connected.
HTTP request sent, awaiting response... 200 OK
Length: 12495628 (12M) [application/x-xz]
Saving to: '/dev/null'

/dev/null                   100%[===========================================>]  11.92M  71.2MB/s    in 0.2s

2017-12-28 12:30:19 (71.2 MB/s) - '/dev/null' saved [12495628/12495628]

root@ubuntu:/tmp# LANG=en_US wget http://127.0.0.1:4444/dd/Python-2.7.13.tar.xz -O /dev/null
--2017-12-28 12:30:20--  http://127.0.0.1:4444/dd/Python-2.7.13.tar.xz
Connecting to 127.0.0.1:4444... connected.
HTTP request sent, awaiting response... 200 OK
Length: 12495628 (12M) [application/x-xz]
Saving to: '/dev/null'

/dev/null                   100%[===========================================>]  11.92M  --.-KB/s    in 0.1s

2017-12-28 12:30:20 (85.4 MB/s) - '/dev/null' saved [12495628/12495628]



Tcptunnel is a simple TCP port forwarder. Please see http://www.vakuumverpackt.de/tcptunnel/ for details and binary downloads.
also at https://github.com/vakuum/tcptunnel

and 
KISSDB https://github.com/adamierymenko/kissdb
 *
 * Written by Adam Ierymenko <adam.ierymenko@zerotier.com>
 * KISSDB is in the public domain and is distributed with NO WARRANTY.
 *
 * http://creativecommons.org/publicdomain/zero/1.0/ */

