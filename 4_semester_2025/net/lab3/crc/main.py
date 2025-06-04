import sys

from libcolor import Printer
from libcrc import CRC, CRC_0x04C11DB7
from libpackets import Packets

def writeframe(input):
    rc = 0
    original_size = len(input)

    payload_size = 32

    payloads = Packets.build_packets(input, payload_size)

    stuffed_packets = []
    for payload in payloads:
        crc = CRC.crc_remainder(payload, CRC_0x04C11DB7, '0')
        full_packet = payload + crc
        stuffed = Packets.bit_stuff(full_packet)
        stuffed_packets.append(stuffed)

    encapsulated = Packets.encapsulate(stuffed_packets)
    
    if len(encapsulated) >= len(payloads) * ((payload_size + 32) * 1.2 + 16):
        rc += 1
        Printer.print_red("Error: Encapsulated size is bigger than expected, check your input.")

    output_size = len(encapsulated)
    ratio = ((output_size - original_size) / original_size) * 100

    Printer.print_blue("> Statistics")
    print(f"Original size: {original_size} bits")
    print(f"Output size: {output_size} bits")
    print(f"Packeting cost: {ratio:.2f}%")
    print(f"\n{encapsulated}")
    
    sys.exit(rc)


def readframe(input):
    rc = 0
    packets = Packets.decapsulate(input)
    message = []

    for i, packet in enumerate(packets):
        Printer.print_blue(f"> Analyzing packet {i}")
        unstuffed = Packets.bit_unstuff(packet)
        payload = unstuffed[:-31]
        crc_value = unstuffed[-31:]

        if CRC.crc_check(payload, CRC_0x04C11DB7, crc_value):
            print(f"Valid payload: {payload}")
            message.append(payload)
        else:
            print(f"CRC check failed")
            rc = 1
            message.append(''.join(['x' for _ in range(len(payload))]))
            
    final_message = ''.join(message)
    print(f"\n{final_message}")
    sys.exit(rc)

def main():
    if len(sys.argv) != 3:
        print("Usage: python main.py <(b)uild|(t)ake> <message>")
        sys.exit(1)

    mode, input = sys.argv[1], sys.argv[2]

    if mode == "b" or mode == "build":
        writeframe(input)
    elif mode == "t" or mode == "take":
        readframe(input)
    else:
        print("Invalid mode. Use 'write' or 'read'.")
        sys.exit(1)
    
    
if __name__ == "__main__":
    main()