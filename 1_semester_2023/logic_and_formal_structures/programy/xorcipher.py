# python3 xorcipher.py
import sys
import random


class XorCipher:
    @staticmethod
    def Encode(text: str):
        return ' '.join([f'{i:08b}' for i in text.encode(encoding='utf-8')])

    @staticmethod
    def Decode(bytes: str):
        return ''.join([chr(int(binary, 2)) for binary in bytes.split()])

    @staticmethod
    def GenerateKey(bytes: int):
        return ' '.join(f'{random.randint(0, 255):08b}' for i in range(bytes))

    @staticmethod
    def XOR(message: str, key: str):
        if len(message) != len(key):
            raise ValueError("Message and key must be of equal length")
        return ''.join((f'{int(a,base=2) ^ int(b,base=2)}' if a != ' ' else ' ') for a, b in zip(message, key))


class Main:
    def Encrypt():
        print("The following program encrypts your text using bitwise XOR operator.")
        print("Key is auto-generated on each input")
        raw = input("Enter text to xorencrypt (CTRL+D to quit):\n")
        message, key, cipher = (message := XorCipher.Encode(raw)),\
            (key := XorCipher.GenerateKey(len(raw))),\
            XorCipher.XOR(message, key)
        print(f"msg {message}\nkey {key}\ncyp {cipher}")

    def Decrypt():
        print("The following program decrypts your text using bitwise XOR operator.")
        raw = input("Enter cipher to xordecrypt (CTRL+D to quit):\n")
        key = input("Enter key:\n")
        message, result = (message := XorCipher.XOR(raw, key)),\
            (XorCipher.Decode(message))
        print(f"raw {raw}\nkey {key}\nmsg {message}\nres {result}")

    def Spoof():
        print("The following program spoofs your text using bitwise XOR operator.")
        cipher = input("Enter cipher to xorspoof (CTRL+D to quit):\n")
        result = input("Enter desired string result:\n")
        message, key = (message := XorCipher.Encode(result)),\
            (XorCipher.XOR(message, cipher))
        print(f"msg {message}\nkey {key}\n")

    arguments = {
        "-e": Encrypt,
        "-d": Decrypt,
        "-s": Spoof
    }

    if len(sys.argv) != 2 or sys.argv[1] not in arguments:
        print(f"Usage: python {sys.argv[0]} [-e|-d|-s]")
        print("-e : Encrypt text with an auto generated key")
        print("-d : Decrypt text provided with a cipher and a key")
        print("-s : Spoof a key provided with a cipher and a desired result")
        sys.exit(1)

    while True:
        try:
            arguments[sys.argv[1]]()
        except EOFError:
            print("EOF detected, exiting...")
            sys.exit(0)
        except KeyboardInterrupt:
            print("KeyboardInterrupt detected, exiting...")
            sys.exit(0)


Main()
