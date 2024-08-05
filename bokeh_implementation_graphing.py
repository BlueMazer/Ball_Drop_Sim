from bokeh.plotting import figure, output_file, show
from bokeh.layouts import gridplot
from bokeh.models import ColumnDataSource, HoverTool

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

# Output to a static HTML file
output_file("bokeh_interactive_plots_with_tooltips.html")

# Create ColumnDataSource
source = ColumnDataSource(data=dict(
    times=times,
    heights=heights,
    vertical_velocities=vertical_velocities,
    drag_forces=drag_forces,
    horizontal_velocities=horizontal_velocities
))

# Create a HoverTool
hover = HoverTool()
hover.tooltips = [
    ("Time", "@times s"),
    ("Height", "@heights m"),
    ("Vertical Velocity", "@vertical_velocities m/s"),
    ("Drag Force", "@drag_forces N"),
    ("Horizontal Velocity", "@horizontal_velocities m/s"),
]

# Create plots
p1 = figure(title="Height vs Time", x_axis_label='Time (s)', y_axis_label='Height (m)')
p1.line(x='times', y='heights', source=source, line_width=2, color='blue', legend_label='Height')
p1.add_tools(hover)

p2 = figure(title="Vertical Velocity vs Time", x_axis_label='Time (s)', y_axis_label='Vertical Velocity (m/s)')
p2.line(x='times', y='vertical_velocities', source=source, line_width=2, color='red', legend_label='Vertical Velocity')
p2.add_tools(hover)

p3 = figure(title="Drag Force vs Time", x_axis_label='Time (s)', y_axis_label='Drag Force (N)')
p3.line(x='times', y='drag_forces', source=source, line_width=2, color='green', legend_label='Drag Force')
p3.add_tools(hover)

p4 = figure(title="Horizontal Velocity vs Time", x_axis_label='Time (s)', y_axis_label='Horizontal Velocity (m/s)')
p4.line(x='times', y='horizontal_velocities', source=source, line_width=2, color='purple', legend_label='Horizontal Velocity')
p4.add_tools(hover)

# Arrange plots in a grid
grid = gridplot([[p1, p2], [p3, p4]])

# Show the plots
show(grid)
