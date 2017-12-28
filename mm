rm *.o
LANG=en_US make
scp * 10.29.24.99:/root/tcp/tun/my
echo "=================================="
./tcptunnel --local-port=4444 --remote-port=3333 --remote-host=10.29.24.99 --stay-alive

