import serial
import math
import matplotlib.pyplot as plt
import threading
import queue

SERIAL_PORT = '/dev/rfcomm1' 
BAUD_RATE = 9600
WHEEL_DIAMETER = 0.065  
TICKS_PER_REV = 20      
TRACK_WIDTH = 0.135
METERS_PER_TICK = (math.pi * WHEEL_DIAMETER) / TICKS_PER_REV 
ANGLE_DEADZONE = 0.5

data_queue = queue.Queue()

def serial_reader(port, baud):
    try:
        ser = serial.Serial(port, baud, timeout=0.1)
        ser.reset_input_buffer()
        print(f"Serial thread started on {port}")
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8', errors='ignore').strip()
                if "L:" in line and "R:" in line:
                    data_queue.put(line)
    except Exception as e:
        print(f"Serial Error: {e}")

def main():
    x, y, theta = 0.0, 0.0, 0.0
    last_l, last_r = 0, 0
    history_x, history_y = [0.0], [0.0]

    thread = threading.Thread(target=serial_reader, args=(SERIAL_PORT, BAUD_RATE), daemon=True)
    thread.start()

    plt.ion()
    fig, ax = plt.subplots(figsize=(8, 6))
    path_line, = ax.plot([], [], 'b-', linewidth=1, label="Path")
    robot_dot, = ax.plot([], [], 'ro', markersize=8, label="Robot")
    
    ax.set_xlabel("X (m)")
    ax.set_ylabel("Y (m)")
    ax.set_title("Robot Odometry Map")
    ax.legend()
    ax.grid(True)
    ax.axis('equal') # Keep 1 meter X looking like 1 meter Y

    print(f"{'X (m)':>8} | {'Y (m)':>8} | {'PHI ':>8} | {'Theta (deg)':>10}")
    print("-" * 35)

    try:
        while True:
            data_found = False
            while not data_queue.empty():
                line = data_queue.get()
                try:
                    parts = line.replace(' ', '').split(',')
                    curr_l = int(parts[0].split(':')[1])
                    curr_r = int(parts[1].split(':')[1])

                    d_ticks_l = curr_l - last_l
                    d_ticks_r = curr_r - last_r
                    
                    delta_l = d_ticks_l * METERS_PER_TICK
                    delta_r = d_ticks_r * METERS_PER_TICK
                    
                    d_center = (delta_l + delta_r) / 2.0
                    phi = (delta_r - delta_l) / TRACK_WIDTH
                    
                    if abs(phi) < ANGLE_DEADZONE:
                        phi = 0
                    
                    x += d_center * math.cos(theta + phi / 2.0)
                    y += d_center * math.sin(theta + phi / 2.0)
                    theta += phi
                    theta = (theta + math.pi) % (2 * math.pi) - math.pi
                    
                    last_l, last_r = curr_l, curr_r
                    history_x.append(x)
                    history_y.append(y)
                    data_found = True
                    
                    print(f"{x:8.2f} | {y:8.2f} | {phi:8.2f} | {math.degrees(theta):10.1f}°", end='\r')
                except:
                    continue

            if data_found:
                path_line.set_data(history_x, history_y)
                robot_dot.set_data([x], [y])
                
                # Rescale and refresh
                ax.relim()
                ax.autoscale_view()
                fig.canvas.draw_idle() 
            
            plt.pause(0.01)

    except KeyboardInterrupt:
        print("\nStopping...")
    finally:
        plt.ioff()
        if 'ser' in locals(): ser.close()
        plt.show()

if __name__ == "__main__":
    main()