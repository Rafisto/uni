echo 1 > /proc/sys/net/ipv4/ip_forward

# ETH0 - NET3

# 192.168.3.0/24 <- private network
# 192.168.3.11 - device address
iptables -A FORWARD -i eth1 -o eth0 -j ACCEPT

# ETH1 - NET5

# 192.168.5.0/24 <- internet 
# 192.168.5.10 - device address
# 192.168.5.1 - docker gateway
iptables -A FORWARD -i eth0 -o eth1 -m state --state RELATED,ESTABLISHED -j ACCEPT 

# Postrouting for outgoing traffic via eth1
iptables -t nat -A POSTROUTING -o eth1 -j MASQUERADE

# uplink via net5 gateway (internet)
ip route replace default via 192.168.5.1

# downlink to net2, net3, net4
ip route add 192.168.1.0/24 via 192.168.3.10
ip route add 192.168.4.0/24 via 192.168.3.10
ip route add 192.168.2.0/24 via 192.168.3.10

# dns
echo "nameserver 1.1.1.1" > /etc/resolv.conf

sleep infinity