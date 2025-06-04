echo 1 > /proc/sys/net/ipv4/ip_forward

# ETH0 - NET4
# ip route add 192.168.4.0/24 dev eth0
ip route add 192.168.1.0/24 via 192.168.4.10  # Route to PC1's network via Router6
ip route add 192.168.3.0/24 via 192.168.4.10  # Route to net3 via Router6

# uplink via net4 gateway (router6)
ip route add default via 192.168.4.10

# ETH1 - NET2
iptables -A FORWARD -i eth0 -o eth1 -j ACCEPT
iptables -A FORWARD -i eth1 -o eth0 -j ACCEPT

# Postrouting for outgoing traffic via eth1
iptables -t nat -A POSTROUTING -o eth1 -j MASQUERADE

# dns
echo "nameserver 1.1.1.1" > /etc/resolv.conf

sleep infinity