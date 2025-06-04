# uplink via net1 gateway (router6)
ip route add default via 192.168.1.10

# the default route for the host
# ip route add 192.168.3.0/24 via 192.168.1.10
# ip route add 192.168.4.0/24 via 192.168.1.10
# ip route add 192.168.2.0/24 via 192.168.1.10

# dns
echo "nameserver 1.1.1.1" > /etc/resolv.conf

sleep infinity