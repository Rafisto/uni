from scapy.all import IP, TCP, sr1, send
import sys

SYN_ACK=0x12

def syn_scan(target, ports):
    open_ports = []
    for port in ports:
        syn_packet = IP(dst=target)/TCP(dport=port, flags="S") # SYN packet
        response = sr1(syn_packet, timeout=1, verbose=0)
        if response and response.haslayer(TCP):
            if response[TCP].flags == SYN_ACK:
                open_ports.append(port)
                rst_packet = IP(dst=target)/TCP(dport=port, flags="R") # RST packet
                send(rst_packet, verbose=0)
    return open_ports

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python nmap.py <domain> <port1> <port2> ...")
        sys.exit(1)

    target = sys.argv[1]
    ports = list(map(int, sys.argv[2:]))
    print(f"Scanning {target} for ports {ports}...")
    open_ports = syn_scan(target, ports)
    if open_ports:
        print(f"Open ports: {open_ports}")
    else:
        print("No open ports found.")