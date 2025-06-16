#!/bin/bash

echo 1 > /proc/sys/net/ipv4/ip_forward

iptables -A FORWARD -p tcp -d 192.168.0.10 \
--dport 80 -j ACCEPT

iptables -t nat -A PREROUTING -i eth1 -p tcp \
--dport 80 -j DNAT --to-destination 192.168.0.10

iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
