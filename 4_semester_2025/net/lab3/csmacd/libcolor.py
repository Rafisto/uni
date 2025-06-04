from libparams import MEDIUM_LENGTH

class Printer:
    RESET = "\033[0m"

    @staticmethod
    def rgb_to_ansi(r, g, b, background=False):
        return f"\033[{48 if background else 38};2;{r};{g};{b}m"

    @staticmethod
    def get_signal_color(age, max_age=2*MEDIUM_LENGTH):
        """Returns an RGB color based on signal age (fades from bright to dark)"""
        if age > max_age:
            age = max_age
        intensity = int(200 * (age / max_age) ** (1/2))
        return Printer.rgb_to_ansi(intensity, intensity, 255)

    @staticmethod
    def get_jam_color(age, max_age=2*MEDIUM_LENGTH):
        """Returns an RGB color for jamming signals (red fading to dark red)"""
        if age > max_age:
            age = max_age
        intensity = int(200 * (age / max_age) ** (1/2))
        return Printer.rgb_to_ansi(255, intensity, intensity)

    @staticmethod
    def colorize_medium(medium):
        colored_medium = []
        for cell in medium:
            if cell is None:
                colored_medium.append("_")
            else:
                source, age = cell
                if source == "x":
                    color = Printer.get_jam_color(age)
                else:
                    color = Printer.get_signal_color(age)
                colored_medium.append(f"{color}{source}{Printer.RESET}")
        return "".join(colored_medium)