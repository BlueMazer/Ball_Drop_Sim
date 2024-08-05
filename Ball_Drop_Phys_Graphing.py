import matplotlib.pyplot as plt
import numpy as np  # Added import for numpy

# Define file path
file_path = "/Users/rayanraad/PycharmProjects/Ball_Drop_Phys_Graphing/simulation_C++_output_Python_Input.txt"

# Initialize lists to store the extracted values
times = []
heights = []
vertical_velocities = []
drag_forces = []
horizontal_distances = []
horizontal_velocities = []

# Read the file and extract data
with open(file_path, "r") as file:
    lines = file.readlines()
    # Skip initial state line
    lines = lines[1:]  # Assuming the first line is initial state and not needed

    for line in lines:
        if line.startswith("Height"):
            try:
                parts = line.split(',')  # Splits the line at every comma into an array called parts

                # Extract values and strip units
                height = float(parts[0].split(':')[1].strip().split()[0])
                # parts[0] -> 'Height: 15.0000 m'
                # .split(':')[1] -> ' 15.0000 m'
                # .strip() -> '15.0000 m'
                # .split()[0] -> '15.0000'
                # float() converts '15.0000' to 15.0000
                time = float(parts[1].split(':')[1].strip().split()[0])
                vertical_velocity = float(parts[2].split(':')[1].strip().split()[0])
                drag_force = float(parts[3].split(':')[1].strip().split()[0])
                horizontal_distance = float(parts[4].split(':')[1].strip().split()[0])
                horizontal_velocity = float(parts[5].split(':')[1].strip().split()[0])

                # Append values to the lists
                times.append(time)
                heights.append(height)
                vertical_velocities.append(vertical_velocity)
                drag_forces.append(drag_force)
                horizontal_distances.append(horizontal_distance)
                horizontal_velocities.append(horizontal_velocity)
            except (IndexError, ValueError) as e:
                print(f"Error parsing line: {line}. Error: {e}")

if not times:
    print("No data parsed. Please check the input file format.")

# Plot the data
fig, axs = plt.subplots(2, 2, figsize=(16, 12))  # 2x2 grid of subplots

# Plot Height vs Time
axs[0, 0].plot(times, heights, label='Height', color='blue')
axs[0, 0].set_xlabel('Time (s)')
axs[0, 0].set_ylabel('Height (m)')
axs[0, 0].set_title('Height vs Time')
axs[0, 0].legend()

# Plot Vertical Velocity vs Time
axs[0, 1].plot(times, vertical_velocities, label='Vertical Velocity', color='red')
axs[0, 1].set_xlabel('Time (s)')
axs[0, 1].set_ylabel('Vertical Velocity (m/s)')
axs[0, 1].set_title('Vertical Velocity vs Time')
axs[0, 1].legend()

# Plot Drag Force vs Time
axs[1, 0].plot(times, drag_forces, label='Drag Force', color='green')
axs[1, 0].set_xlabel('Time (s)')
axs[1, 0].set_ylabel('Drag Force (N)')
axs[1, 0].set_title('Drag Force vs Time')
axs[1, 0].legend()

# Plot Horizontal Velocity vs Time
axs[1, 1].plot(times, horizontal_velocities, label='Horizontal Velocity', color='purple')
axs[1, 1].set_xlabel('Time (s)')
axs[1, 1].set_ylabel('Horizontal Velocity (m/s)')
axs[1, 1].set_title('Horizontal Velocity vs Time')
axs[1, 1].legend()

plt.tight_layout()
plt.show()
