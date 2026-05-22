import serial
import math

# Configuration
SERIAL_PORT = '/dev/rfcomm1' 
BAUD_RATE = 9600
WHEEL_DIAMETER = 0.065  
TICKS_PER_REV = 20      
TRACK_WIDTH = 0.135     
METERS_PER_TICK = (math.pi * WHEEL_DIAMETER) / TICKS_PER_REV 

def main():
    # Odometry state
    x, y, theta = 0.0, 0.0, 0.0
    last_l, last_r = 0, 0

    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.1)
        ser.reset_input_buffer()
        print(f"{'X (m)':>10} | {'Y (m)':>10} | {'Theta (deg)':>12}")
        print("-" * 40)

        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8', errors='ignore').strip()
                
                if "L:" in line and "R:" in line:
                    try:
                        # Parse "L:val, R:val"
                        parts = line.replace(' ', '').split(',')
                        curr_l = int(parts[0].split(':')[1])
                        curr_r = int(parts[1].split(':')[1])

                        # Calculate distance moved by each wheel
                        delta_l = (curr_l - last_l) * METERS_PER_TICK
                        delta_r = (curr_r - last_r) * METERS_PER_TICK
                        
                        # Odometry math
                        d_center = (delta_l + delta_r) / 2.0
                        phi = (delta_r - delta_l) / TRACK_WIDTH
                        
                        # Update Pose
                        x += d_center * math.cos(theta + phi / 2.0)
                        y += d_center * math.sin(theta + phi / 2.0)
                        theta += phi
                        
                        last_l, last_r = curr_l, curr_r

                        # Convert theta to degrees for easier reading
                        theta_deg = math.degrees(theta) % 360
                        
                        # Clear-style output
                        print(f"{x:10.3f} | {y:10.3f} | {theta_deg:12.1f}")

                    except (ValueError, IndexError):
                        continue

    except KeyboardInterrupt:
        print("\nStopped.")
    finally:
        if 'ser' in locals(): 
            ser.close()

if __name__ == "__main__":
    main()