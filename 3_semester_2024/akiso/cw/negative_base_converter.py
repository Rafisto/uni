def decimal_to_negabinary(n):
    if n == 0:
        return "0"
    
    result = []
    while n != 0:
        remainder = n % -2
        n = n // -2
        if remainder < 0:
            remainder += 2
            n += 1
        result.append(str(remainder))
    
    return ''.join(result[::-1])

def decimal_to_negative_base(n, base):
    if base >= -1 or base == 0:
        raise ValueError("Base must be less than -1 and not zero.")
    
    if n == 0:
        return "0"
    
    result = []
    while n != 0:
        remainder = n % base
        n = n // base
        if remainder < 0:
            remainder += abs(base)
            n += 1
        result.append(str(remainder))
    
    return ''.join(result[::-1])

if __name__ == "__main__":
    decimal_number = int(input("Enter a decimal number: "))
    destination_base = int(input("Enter destination base: "))
    nega_number = decimal_to_negative_base(decimal_number,destination_base)
    print(f"The base {destination_base} representation of {decimal_number} is {nega_number}")