from scapy.all import IP, ICMP, sr1
import argparse
import socket
import time

ICMP_TIME_EXCEEDED = 11
ICMP_ECHO_REPLY = 0

def ping(destination, timeout=5):
    """
    Perform a ping to a destination using ICMP packets.
    """

    try:
        dest_ip = socket.gethostbyname(destination)
    except socket.gaierror:
        print(f"Could not resolve {destination}")
        return
    
    while True:
        time.sleep(1)    
        packet = IP(dst=dest_ip, ttl=64) / ICMP()
        start_time = time.time()
        reply = sr1(packet, verbose=0, timeout=timeout)
        rtt = (time.time() - start_time) * 1000

        if reply is None:
            print(f"Request timed out for {dest_ip}")
        else:
            print(f"Reply from {dest_ip}: bytes=32 time={rtt:.2f} ms")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Simple traceroute implementation using Scapy")
    parser.add_argument("destination", help="Destination hostname or IP address")
    parser.add_argument("-t", "--timeout", type=int, default=2,
                        help="Timeout in seconds for each reply (default: 2)")
    
    args = parser.parse_args()
    
    ping(
        args.destination,
        timeout=args.timeout
    )