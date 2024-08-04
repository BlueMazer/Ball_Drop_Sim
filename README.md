#Ball_Drop_Sim

Project Overview
This project simulates the motion of a ball considering gravity, drag force, and restitution. Written in C++, it outputs results to a file and includes a search feature for specific data points. Useful for learning physics and C++ programming. Future improvements: advanced data visualization, detailed physical models, and enhanced UI.
Files
	•	Ball.h: Header file containing the definition of the Ball struct and function declarations.
	•	ball_simulation.cpp: Main simulation file containing the implementation of the functions declared in Ball.h.
	•	common.h: Header file containing common variable declarations and the getValidNumber function declaration.
Key Features
	•	Simulates the ball's motion considering gravity and drag force.
	•	Allows users to update the ball's state with each time step.
	•	Computes and displays maximum, minimum, and average values of various physical quantities.
	•	Provides a search menu for examining specific values from the simulation output.
	•	Finds and displays the closest approximation when an exact match is not found.
How to Run
1. Clone the Repository 
git clone <repository-url>
cd Ball_Drop_Phys
 
2. Build the Project Ensure you have a C++ compiler installed (e.g., g++), then compile the project:
g++ -o ball_simulation ball_simulation.cpp  3.Run the Simulation Execute the compiled program:  ./ball_simulation
4. Input Parameters When prompted, enter the following parameters:
	•	Initial height of the ball (in meters)
	•	Mass of the ball (in kilograms)
	•	Drag coefficient (dimensionless)
	•	Initial horizontal force (in Newtons)
	•	Coefficient of restitution (between 0 and 1)

5. Using the Search Menu After the simulation completes, you can use the search menu to examine specific values. Follow the on-screen prompts to enter your search criteria.

Functions and Their Descriptions

calculateDrag(double velocity, double drag_coefficient): Calculates the drag force based on velocity and drag coefficient.

formatDouble(double value): Formats a double value to four decimal places as a string.

isNumber(const std::string& s): Checks if a string represents a valid number.

value_check(double height, double mass, double drag_coefficient, double HorForce, double R): Validates that all input parameters are within 
acceptable ranges.

updateBall(Ball& ball, double HorForce): Updates the ball's state (position, velocity, etc.) for each time step.

DisplayAnalyzedResults(...): Displays the maximum, minimum, and average values of various physical quantities.

snapValue(const std::vector<double>& values, double target): Finds the closest value in a vector to a given target value.

SearchMenu(...): Provides a menu for searching specific values in the simulation output file.

Example Usage
Enter the initial height of the ball (in meters): 10
Enter the mass of the ball (in kilograms): 1
Enter the drag coefficient (dimensionless): 0.47
Enter the initial horizontal force (in Newtons): 5
Enter the coefficient of restitution (0-1): 0.9

Author
Rayan Raad, 2024-07-28
