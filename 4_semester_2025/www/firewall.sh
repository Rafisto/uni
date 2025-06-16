#!/bin/bash

iptables -A INPUT -p tcp --dport 22 -j ACCEPT
iptables -A INPUT -s 203.0.113.5 -j DROP
