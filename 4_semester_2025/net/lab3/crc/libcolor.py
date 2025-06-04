class Printer:
    @staticmethod
    def print_blue(message: str):
        print(f"\033[94m{message}\033[0m")
        
    @staticmethod
    def print_red(message: str):
        print(f"\033[91m{message}\033[0m")
        
    @staticmethod
    def print_match(message: str, match: str):
        if match in message:
            parts = message.split(match)
            for i, part in enumerate(parts):
                if i > 0:
                    print(f"\033[96m{match}\033[0m", end="")
                print(f"{part}", end="")
            print("\033[0m")
        else:
            print(f"{message}\033[0m")