import serial
import time
import math
import matplotlib.pyplot as plt

# Configuration
SERIAL_PORT = '/dev/rfcomm1' 
BAUD_RATE = 9600
WHEEL_DIAMETER = 0.065  
TICKS_PER_REV = 20      
TRACK_WIDTH = 0.135     
METERS_PER_TICK = (math.pi * WHEEL_DIAMETER) / TICKS_PER_REV 

def main():
    x, y, theta = 0.0, 0.0, 0.0
    last_l, last_r = 0, 0

    plt.ion() 
    fig, ax = plt.subplots()
    path_line, = ax.plot([], [], 'b-', label="Path") 
    robot_dot, = ax.plot([], [], 'ro', label="Robot") 
    ax.set_xlabel("X (meters)")
    ax.set_ylabel("Y (meters)")
    ax.set_title("Robot Real-Time Path Mapping")
    ax.grid(True)
    ax.legend()

    history_x, history_y = [0.0], [0.0]

    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.5)
        print(f"Connected to {SERIAL_PORT}. Starting mapping...")

        ser.reset_input_buffer()

        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8', errors='ignore').strip()
                
                if "L:" in line and "R:" in line:
                    try:
                        parts = line.replace(' ', '').split(',')
                        curr_l = int(parts[0].split(':')[1])
                        curr_r = int(parts[1].split(':')[1])

                        delta_l = (curr_l - last_l) * METERS_PER_TICK
                        delta_r = (curr_r - last_r) * METERS_PER_TICK
                        
                        d_center = (delta_l + delta_r) / 2.0
                        phi = (delta_r - delta_l) / TRACK_WIDTH
                        
                        x += d_center * math.cos(theta + phi / 2.0)
                        y += d_center * math.sin(theta + phi / 2.0)
                        theta += phi
                        
                        last_l, last_r = curr_l, curr_r

                        history_x.append(x)
                        history_y.append(y)
                        
                        path_line.set_data(history_x, history_y)
                        robot_dot.set_data([x], [y])
                        
                        ax.relim()
                        ax.autoscale_view()
                        
                        plt.pause(0.001) 

                    except (ValueError, IndexError) as e:
                        print(f"Parse error: {e}")
                        continue

    except KeyboardInterrupt:
        print("\nMapping stopped by user.")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        plt.ioff()
        if 'ser' in locals(): 
            ser.close()
            print("Serial connection closed.")
        plt.show() 

if __name__ == "__main__":
    main()