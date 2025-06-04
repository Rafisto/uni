from scapy.all import Ether, IP, TCP, UDP, ICMP, sniff
import argparse
import signal
import sys
from datetime import datetime

packet_count = 0
start_time = None

def signal_handler(sig, frame):
    print("\n--- Packet capture summary ---")
    if start_time:
        duration = datetime.now() - start_time
        print(f"Capture duration: {duration}")
    print(f"Total packets captured: {packet_count}")
    sys.exit(0)

def packet_callback(packet, display_filter=None, verbose=False, output_file=None):
    global packet_count
    
    packet_count += 1
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
    
    if display_filter and not display_filter(packet):
        return
    
    output = f"[{timestamp}]#{packet_count}:{len(packet)} bytes"
    
    if Ether in packet:
        output += f"\n  Ethernet: {packet[Ether].src} -> {packet[Ether].dst}"
    
    if IP in packet:
        ip = packet[IP]
        output += f"\n  IP: {ip.src}:{ip.sport if hasattr(ip, 'sport') else '?'} -> " \
                 f"{ip.dst}:{ip.dport if hasattr(ip, 'dport') else '?'} " \
                 f"(Proto: {ip.proto}, TTL: {ip.ttl})"
    
    if TCP in packet:
        tcp = packet[TCP]
        output += f"\n  TCP: Flags: {tcp.flags}, Seq: {tcp.seq}, Ack: {tcp.ack}"
    
    elif UDP in packet:
        udp = packet[UDP]
        output += f"\n  UDP: Length: {udp.len}, Checksum: {udp.chksum}"
    
    elif ICMP in packet:
        icmp = packet[ICMP]
        output += f"\n  ICMP: Type: {icmp.type}, Code: {icmp.code}"
    
    if verbose:
        output += f"\n  Full packet:\n{packet.show(dump=True)}"
    
    print(output)
    
    if output_file:
        with open(output_file, 'a') as f:
            f.write(output + "\n")

def create_display_filter(filter_str):
    """Create a display filter function from a string"""
    if not filter_str:
        return None
    
    def filter_func(packet):
        try:
            return packet.haslayer(filter_str)
        except:
            return filter_str.lower() in str(packet).lower()
    
    return filter_func

def main():
    global start_time
    
    parser = argparse.ArgumentParser(description="Packet sniffer using Scapy")
    parser.add_argument("-i", "--interface", default=None, help="Network interface to sniff on (default: auto-detect)")
    parser.add_argument("-f", "--filter", default="", help="Filter to apply (e.g., 'tcp port 80')")
    parser.add_argument("-d", "--display-filter", default="", help="Display filter to show only matching packets")
    parser.add_argument("-c", "--count", type=int, default=0, help="Number of packets to capture (0 for unlimited)")
    parser.add_argument("-v", "--verbose", action="store_true", help="Show verbose packet output")
    parser.add_argument("-o", "--output", default=None, help="Output file to save captured packets")
    parser.add_argument("-t", "--timeout", type=int, default=10, help="Capture timeout in seconds (10 default)")
    
    args = parser.parse_args()
    
    signal.signal(signal.SIGINT, signal_handler)
    
    print(f"Starting packet capture on interface {args.interface or 'default'}...")
    print(f"Filter: {args.filter or 'none'}")
    if args.display_filter:
        print(f"Display filter: {args.display_filter}")
    if args.count > 0:
        print(f"Capturing {args.count} packets")
    if args.timeout > 0:
        print(f"Timeout: {args.timeout} seconds")
    
    start_time = datetime.now()
    
    display_filter = create_display_filter(args.display_filter)
    
    sniff(
        iface=args.interface,
        prn=lambda p: packet_callback(p, display_filter, args.verbose, args.output),
        filter=args.filter,
        count=args.count,
        timeout=args.timeout
    )
    
    signal_handler(None, None)

if __name__ == "__main__":
    main()