import serial
import math
import time
SERIAL_PORT = '/dev/rfcomm0'
BAUD_RATE = 9600
WHEEL_DIAMETER = 0.065
TICKS_PER_REV = 20
TICKS_PER_FULL_ROTATION = 240
METERS_PER_TICK = (math.pi * WHEEL_DIAMETER) / TICKS_PER_REV


def connect_serial():
    """Attempts to connect to the serial port, blocking until successful."""
    while True:
        try:
            ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.1)
            ser.flushInput()
            print(f"\n[+] Successfully connected to {SERIAL_PORT}")
            return ser
        except (serial.SerialException, OSError):
            print(f"[-] Waiting for {SERIAL_PORT} to become available...")
            time.sleep(1)


def main():
    log_file = open("log.txt", "a")
    log_file.writelines(["Log Starting\n"])
    x, y, theta = 0.0, 0.0, 0.0
    last_l, last_r = 0, 0
    ser = None
    try:
        ser = connect_serial()
        while True:
            try:
                if ser.in_waiting > 0:
                    line = ser.readline().decode('utf-8', errors='ignore').strip()
                    log_file.write(line + "\n")
                    log_file.flush()
                    if "L:" in line and "R:" in line:
                        try:
                            parts = line.replace(' ', '').split(',')
                            curr_l = int(parts[0].split(':')[1])
                            curr_r = int(parts[1].split(':')[1])
                            if curr_l < last_l or curr_r < last_r:
                                print(
                                    "[!] Encoders reset to 0. Re-syncing baseline.")
                                last_l, last_r = curr_l, curr_r
                                continue
                            delta_l = (curr_l - last_l) * METERS_PER_TICK
                            delta_r = (curr_r - last_r) * METERS_PER_TICK
                            d_center = (delta_l + delta_r) / 2.0
                            phi = (delta_r - delta_l) / TICKS_PER_FULL_ROTATION
                            x += d_center * math.cos(theta + phi / 2.0)
                            y += d_center * math.sin(theta + phi / 2.0)
                            theta += phi
                            last_l, last_r = curr_l, curr_r
                            theta_deg = math.degrees(theta) % 360
                            print(
                                f"X: {x:10.3f} | Y: {y:10.3f} | Theta: {theta_deg:12.1f}°")
                        except (ValueError, IndexError):
                            continue
                print("Waiting for data...", end='\r')
            except (OSError, serial.SerialException) as e:
                print(f"\n[!] Connection lost: {e}")
                log_file.write(f"\n[!] Connection lost: {e}\n")
                if ser:
                    ser.close()
                ser = connect_serial()
                log_file.write("[!] Device reconnected.\n")
    except KeyboardInterrupt:
        print("\nStopped by user.")
    finally:
        if ser and ser.is_open:
            ser.close()
        log_file.close()


if __name__ == "__main__":
    main()
