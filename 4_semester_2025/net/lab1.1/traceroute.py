from scapy.all import IP, ICMP, sr1
import argparse
import socket
import time

ICMP_TIME_EXCEEDED = 11
ICMP_ECHO_REPLY = 0

def traceroute(destination, max_hops=30, timeout=1, verbose=False):
    """
    Perform a traceroute to a destination using ICMP or UDP packets.
    """

    try:
        dest_ip = socket.gethostbyname(destination)
    except socket.gaierror:
        print(f"Could not resolve {destination}")
        return
    
    print(f"Traceroute to {destination} ({dest_ip}), {max_hops} hops max")
    
    for ttl in range(1, max_hops + 1):
        packet = IP(dst=dest_ip, ttl=ttl) / ICMP()
        start_time = time.time()
        reply = sr1(packet, verbose=0, timeout=timeout)
        rtt = (time.time() - start_time) * 1000
        
        if reply is None:
            print(f"{ttl}\t*")
            if verbose:
                print(f"Timeout waiting for TTL {ttl}")
        elif reply.type == ICMP_TIME_EXCEEDED:
            print(f"{ttl}\t{reply.src}\t{rtt:.2f} ms")
            if verbose:
                print(f"Received ICMP Time Exceeded from {reply.src}")
        elif reply.type == ICMP_ECHO_REPLY:
            print(f"{ttl}\t{reply.src}\t{rtt:.2f} ms")
            print("Destination reached!")
            break
        else:
            print(f"{ttl}\t{reply.src}\t{rtt:.2f} ms")
            if verbose:
                print(f"Received ICMP type {reply.type} from {reply.src}")
            
            if reply.src == dest_ip:
                print("Destination reached!")
                break

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Simple traceroute implementation using Scapy")
    parser.add_argument("destination", help="Destination hostname or IP address")
    parser.add_argument("-m", "--max-hops", type=int, default=30, 
                        help="Maximum number of hops (default: 30)")
    parser.add_argument("-t", "--timeout", type=int, default=2,
                        help="Timeout in seconds for each reply (default: 2)")
    parser.add_argument("-v", "--verbose", action="store_true",
                        help="Show verbose output")
    
    args = parser.parse_args()
    
    traceroute(
        args.destination,
        max_hops=args.max_hops,
        timeout=args.timeout,
        verbose=args.verbose
    )