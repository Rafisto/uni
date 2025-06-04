# uplink via net2 gateway (router2)
ip route add default via 192.168.2.10

# dns
echo "nameserver 1.1.1.1" > /etc/resolv.conf

sleep infinity