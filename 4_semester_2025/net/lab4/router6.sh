echo 1 > /proc/sys/net/ipv4/ip_forward

# ETH0 - NET1

# 192.168.1.0/24 <- private network
# 192.168.1.10 - device address
iptables -A FORWARD -i eth0 -o eth1 -j ACCEPT
iptables -A FORWARD -i eth0 -o eth2 -j ACCEPT

# ETH1 - NET3

# 192.168.3.0/24 <- private network
# 192.168.3.10 - device address
iptables -A FORWARD -i eth1 -o eth0 -j ACCEPT
iptables -A FORWARD -i eth1 -o eth2 -j ACCEPT

# ETH2 - NET4

# 192.168.4.0/24 <- private network
# 192.168.4.10 - device address
iptables -A FORWARD -i eth2 -o eth0 -j ACCEPT
iptables -A FORWARD -i eth2 -o eth1 -j ACCEPT

# Postrouting for outgoing traffic via eth1
iptables -t nat -A POSTROUTING -o eth1 -j MASQUERADE
iptables -t nat -A POSTROUTING -o eth2 -j MASQUERADE

# uplink to net5 via router5
# ip route add 192.168.5.0/24 via 192.168.3.11

# uplink via net5 gateway (internet)
ip route add default via 192.168.3.11

# downlink to net2
ip route add 192.168.2.0/24 via 192.168.4.11

# dns
echo "nameserver 1.1.1.1" > /etc/resolv.conf

sleep infinity