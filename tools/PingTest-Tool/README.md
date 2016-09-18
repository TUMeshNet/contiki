The following a is Ping6 script used to ping the motes 1000 times. 
The file ping66 is an executable. In order to run it, download this folder and then run the following commands.

ping66 reguires the input of the address, date, and time.

Example run for 09/18/2016 at 4:33pm:

./ping66 aaaa::212:7401:1:101 2016-09-18 04:33

After it finish running, it will store all the ping results in a ping file called:
pingdata_2016-09-18T04:33:00.tx

This text file will contain 1000 results and the packet lost. 


Example Output:

user@instant-contiki:~/Work$ more pingdata_2016-09-18T04-05\:00.txt 
PING google.com (209.85.201.139) 56(84) bytes of data.
64 bytes from qu-in-f139.1e100.net (209.85.201.139): icmp_seq=1 ttl=128 time=33.0 ms
64 bytes from qu-in-f139.1e100.net (209.85.201.139): icmp_seq=2 ttl=128 time=29.3 ms
64 bytes from qu-in-f139.1e100.net (209.85.201.139): icmp_seq=3 ttl=128 time=29.4 ms
64 bytes from qu-in-f139.1e100.net (209.85.201.139): icmp_seq=4 ttl=128 time=39.4 ms
64 bytes from qu-in-f139.1e100.net (209.85.201.139): icmp_seq=5 ttl=128 time=29.2 ms
64 bytes from qu-in-f139.1e100.net (209.85.201.139): icmp_seq=6 ttl=128 time=28.9 ms
64 bytes from qu-in-f139.1e100.net (209.85.201.139): icmp_seq=7 ttl=128 time=29.6 ms
64 bytes from qu-in-f139.1e100.net (209.85.201.139): icmp_seq=8 ttl=128 time=46.7 ms
64 bytes from qu-in-f139.1e100.net (209.85.201.139): icmp_seq=9 ttl=128 time=47.9 ms
64 bytes from qu-in-f139.1e100.net (209.85.201.139): icmp_seq=10 ttl=128 time=28.8 ms

--- google.com ping statistics ---
10 packets transmitted, 10 received, 0% packet loss, time 9020ms
rtt min/avg/max/mdev = 28.827/34.269/47.954/7.232 ms

