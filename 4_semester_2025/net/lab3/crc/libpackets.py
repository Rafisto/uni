from libcolor import Printer

FLAG_STARTSTOP = '01111110'


class Packets:
    @staticmethod
    def bit_stuff(input_bitstring: str) -> str:
        """
        Add a '0' after every sequence of five consecutive '1's.
        """
        Printer.print_blue("> Bit stuffing")
        Printer.print_match(input_bitstring, '11111')
        
        stuffed = ""
        count = 0
        for bit in input_bitstring:
            stuffed += bit
            if bit == '1':
                count += 1
                if count == 5:
                    stuffed += '0'
                    count = 0
            else:
                count = 0
                
        Printer.print_match(stuffed, '111110')
                
        return stuffed


    @staticmethod
    def bit_unstuff(input_bitstring: str) -> str:
        """
        Remove the '0' following every sequence of five consecutive '1's.
        """
        Printer.print_blue("> Bit unstuffing")
        Printer.print_match(input_bitstring, '111110')
        
        unstuffed = ""
        count = 0
        i = 0
        while i < len(input_bitstring):
            bit = input_bitstring[i]
            unstuffed += bit
            if bit == '1':
                count += 1
                if count == 5:
                    i += 1
                    count = 0
            else:
                count = 0
            i += 1
            
        Printer.print_match(unstuffed, '11111')
        return unstuffed

    @staticmethod
    def build_packets(input_bitstring: str, packet_size: int = 32) -> list[str]:
        """
        Split the input_bitstring into packets of size packet_size
        """   
        packets = []
        for i in range(0, len(input_bitstring), packet_size):
            packets.append(input_bitstring[i:i + packet_size])
        return packets

    @staticmethod
    def take_packets(packets: list[str]) -> str:
        """
        Take a list of packets and convert them to a single bitstream
        """
        Printer.print_blue("> Take packets and convert to bitstream")
        
        bitstream = ''
        for packet in packets:
            bitstream += packet
            
        print(f"Bitstream <- [{bitstream}] {len(bitstream)} bit(s)")
         
        return bitstream

    @staticmethod
    def encapsulate(packets: list[str]) -> str:
        """
        Convert list of packets to a single bitstream separated by start/end flags
        """
        Printer.print_blue(f"> Bitstream to packets")
        print(f"Bitstream -> {''.join(packets)}")
        
        Printer.print_blue(f"> Build packets")
        
        for i in range(len(packets)):
            print(f"Packet {i} -> [{packets[i]}] {len(packets[i])} bit(s)")
            packets[i] = FLAG_STARTSTOP + packets[i] + FLAG_STARTSTOP
        
        Printer.print_blue(f"> (HDLC) Encapsulate packets with FLAG_STARTSTOP ({FLAG_STARTSTOP})")
        Printer.print_match(''.join(packets), FLAG_STARTSTOP)
        
        return ''.join(packets)

    @staticmethod
    def decapsulate(bitstream: str) -> list[str]:
        """
        Convert bitstream back to packets
        """
        Printer.print_blue(f"> (HDLC) Lookup frame contents marked by FLAG_STARTSTOP ({FLAG_STARTSTOP})")
        Printer.print_match(bitstream, FLAG_STARTSTOP)

        packets = bitstream.split(FLAG_STARTSTOP)
        packets = [p for p in packets if p]

        Printer.print_blue("> Merge packets")
        for i, p in enumerate(packets):
            print(f"Packet {i} <- [{p}] {len(p)} bit(s)")

        return packets
