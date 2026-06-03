import math
import re
import sys
import time
import os
import matplotlib.pyplot as plt

# Differential Drive Model
# https://en.wikipedia.org/wiki/Differential_wheeled_robot
axle_width = 20.0

prev_left = None
prev_right = None

x : float = 0
y : float = 0
theta : float = 0
vx : float = 0
vy : float = 0

rel_err = lambda x,y : abs(x-y)/abs(x) if x != 0 else 0 
rel_err_tolerance = 0.1

x_history : list[float] = []
y_history : list[float] = []

fig, ax = plt.subplots(figsize=(8, 6))
path_line, = ax.plot(x_history, y_history, 'b-o', markersize=3, label="Robot Path")
start_dot = ax.scatter(x, y, color='green', s=100, zorder=5, label='Start')
current_dot = ax.scatter(x, y, color='red', s=100, zorder=5, label='Current')
velocity_arrow = ax.arrow(x, y, vx, vy, head_width=1, head_length=2, fc='orange', ec='orange', label='Velocity')
left_axle, = ax.plot([x, x], [y, y], 'k-', label='Axle')
right_axle, = ax.plot([x, x], [y, y], 'k-', label='Axle')

ax.set_title('Differential Drive XY-Tracking')
ax.set_xlabel('X Position')
ax.set_ylabel('Y Position')
ax.grid(True, linestyle='--', alpha=0.6)
ax.legend()
ax.axis('equal')

filename = sys.argv[1]
last_skip = False

plt.ion()
plt.show()

if not os.path.exists(filename):
    print(f"Waiting for {filename} to be created...")
    while not os.path.exists(filename):
        time.sleep(1)

with open(filename, "r", encoding="utf-8") as file:
    print(f"Now tailing {filename} for live telemetry updates...")

    while True:
        line = file.readline()
        print(line)
        
        if not line:
            time.sleep(0.05)
            plt.pause(0.01) 
            continue

        left_re = re.search(r"L:(-?\d+)", line)
        right_re = re.search(r"R:(-?\d+)", line)
        
        if left_re and right_re:
            left, right = int(left_re.group(1)), int(right_re.group(1))

            if not last_skip:
                if left == 0 or prev_left == 0 or right == 0 or prev_right == 0:
                    continue

                if prev_left is None or prev_right is None:
                    prev_left, prev_right = left, right

                if rel_err(left, prev_left) > rel_err_tolerance or rel_err(right, prev_right) > rel_err_tolerance:
                    print("Skip bad frame")
                    last_skip = True
                    continue
            else:
                last_skip = False
                prev_left, prev_right = left, right

            print(f"Left: {left}, Right: {right}, PLeft: {prev_left}, PRight: {prev_right}")
            dl = left - prev_left
            dr = right - prev_right
            dtheta = (dr - dl) / axle_width 
            dpos = (dr + dl) / 2

            vx = dpos * math.cos(theta + dtheta/2)
            vy = dpos * math.sin(theta + dtheta/2)

            x += vx
            y += vy
            theta += dtheta

            x_history.append(x)
            y_history.append(y)

            print(f"({x},{y},{theta}) L({prev_left}=>{left}) R({prev_right}=>{right}) DL={dl} DR={dr}")

            path_line.set_xdata(x_history)
            path_line.set_ydata(y_history)
            current_dot.set_offsets([[x, y]])
            
            ax.relim()
            ax.autoscale_view()
            
            prev_left, prev_right = left, right

plt.ioff()
plt.show()
