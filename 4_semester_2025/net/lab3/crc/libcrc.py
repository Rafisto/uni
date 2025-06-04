from libcolor import Printer

CRC_0x04C11DB7 = "10000100110000010001110110110111"

class CRC:
    @staticmethod
    def crc_remainder(
        input_bitstring: str,
        polynomial_bitstring: str = CRC_0x04C11DB7,
        initial_filler: str = "0"
    ) -> str:
        """
        Calculate the CRC remainder of a string of bits using a chosen polynomial.
        initial_filler should be '1' or '0'.
        """
        Printer.print_blue("> CRC remainder")
        
        polynomial_bitstring = polynomial_bitstring.lstrip("0")
        len_input = len(input_bitstring)
        initial_padding = (len(polynomial_bitstring) - 1) * initial_filler
        input_padded_array = list(input_bitstring + initial_padding)
        while "1" in input_padded_array[:len_input]:
            cur_shift = input_padded_array.index("1")
            for i in range(len(polynomial_bitstring)):
                input_padded_array[cur_shift + i] = str(
                    int(polynomial_bitstring[i] !=
                        input_padded_array[cur_shift + i])
                )
                
        crc = "".join(input_padded_array)[len_input:]       
                
        print(f"CRC: {crc}")
        print(f"Length of CRC: {len(crc)} bits")

        return crc

    @staticmethod
    def crc_check(
        input_bitstring: str,
        polynomial_bitstring: str = CRC_0x04C11DB7,
        check_value: str = "0"
    ) -> bool:
        """
        Calculate the CRC check of a string of bits using a chosen polynomial.
        check_value should be the provided CRC value.
        """
        Printer.print_blue("> CRC check")
        
        polynomial_bitstring = polynomial_bitstring.lstrip("0")
        len_input = len(input_bitstring)
        initial_padding = check_value
        input_padded_array = list(input_bitstring + initial_padding)
        while "1" in input_padded_array[:len_input]:
            cur_shift = input_padded_array.index("1")
            for i in range(len(polynomial_bitstring)):
                input_padded_array[cur_shift + i] = str(
                    int(polynomial_bitstring[i] !=
                        input_padded_array[cur_shift + i])
                )
                
        if "1" not in "".join(input_padded_array)[len_input:]:
            print("CRC check: PASSED")
            return True
        
        print("CRC check: FAILED")
        return False
