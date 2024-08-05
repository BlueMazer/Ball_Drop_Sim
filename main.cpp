//
// Copyright (c) [2024] [Rayan Raad]
//
// This software is released under the MIT License.
// See the LICENSE file for details.
//
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <thread>
#include <chrono>
#include "Ball.h"
#include "common.h"

using namespace std;

// Define the variables
double R = 0.0;
int n = 0.0;

// Define the function
double getValidNumber() {
    double number;
    while (true) {
        std::cin >> number;

        // Check if the input is valid
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. ";
            std::cout << "Please enter a valid number: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard remaining input
            return number;
        }
    }
}


constexpr double g = 9.81; // acceleration due to gravity (m/s^2)
constexpr double dt = 0.01; // time step size (s)
const int max_bounces = 30; // Maximum number of bounces

int main() {
    std::cout << std::fixed << std::setprecision(4);
    ofstream OutputFile;
    OutputFile.open("/Users/rayanraad/PycharmProjects/Ball_Drop_Phys_Graphing/simulation_C++_output_Python_Input.txt"); // Open file for writing

    if (!OutputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    Ball ball = {}; // Initialize the ball with default values
    ball.height = 0.0; // Initial height above ground (m)
    ball.distance = 0.0; // Initial horizontal distance
    ball.vert_velocity = 0.0; // Initial vertical velocity (m/s)
    ball.time = 0.0; // Initial time (s)
    ball.drag = 0.0; // Initial drag force
    ball.mass = 1.0; // Default mass
    double HorForce = 0.0; // Default horizontal force

    // Print the initial state of the ball
    OutputFile << "Initial State:" << endl;
    OutputFile << "Time: " << ball.time << " s, "
               << "Height: " << ball.height << " m, "
               << "Vertical Velocity: " << ball.vert_velocity << " m/s, "
               << "Horizontal Distance: " << ball.distance << " m, "
               << "Horizontal Velocity: " << ball.hor_vel << " m/s, "
               << "Mass: " << ball.mass << " kg, "
               << "Drag: " << ball.drag << " N, "
               << "Drag Coefficient: " << ball.drag_coefficient << endl << "\n" << endl;

    //Variable for tracking min and max
    double minHeight = numeric_limits<double>::max();
    double minVertVelocity = numeric_limits<double>::max();
    double minDragForce = numeric_limits<double>::max();
    double minHorVelocity = numeric_limits<double>::max();
    double minHorDistance = numeric_limits<double>::max();

    double maxHeight = numeric_limits<double>::lowest();
    double maxVertVelocity = numeric_limits<double>::lowest();
    double maxDragForce = numeric_limits<double>::lowest();
    double maxHorVelocity = numeric_limits<double>::lowest();
    double maxHorDistance = numeric_limits<double>::lowest();

    // Variables to track total sum
    double totalHeight = 0.0;
    double totalVertVelocity = 0.0;
    double totalDistance = 0.0;
    double totalDragForce = 0.0;
    double totalHorVel = 0.0;

    // Variable to track total time
    int timeSteps = 0;
    double finalTime = 0.0;

    // Arrays to store values for each time step
    vector<double> heights;
    vector<double> vert_velocities;
    vector<double> distances;
    vector<double> drag_forces;
    vector<double> horizontal_velocities;

    // Get the initial height from the user
    cout << "Please enter the initial height of the ball (H > 0) : ";
    ball.height = getValidNumber();
    // Check for valid input
    if (!value_check(ball.height, ball.mass, ball.drag_coefficient, HorForce, R)) return 1;

    // Get the mass of the ball from the user
    cout << "Please enter the mass of the ball (M > 0): ";
    ball.mass = getValidNumber();
    // Check for valid input
    if (!value_check(ball.height, ball.mass, ball.drag_coefficient, HorForce, R)) return 1;

    // Get the drag coefficient from the user
    cout << "Please enter the drag coefficient of the ball (D >= 0): ";
    ball.drag_coefficient = getValidNumber();
    // Check for valid input
    if (!value_check(ball.height, ball.mass, ball.drag_coefficient, HorForce, R)) return 1;

    // Get the force applied on the ball from the user
    cout << "Please enter the force applied on the ball (F >= 0): ";
    HorForce = getValidNumber();
    // Check for valid input
    if (!value_check(ball.height, ball.mass, ball.drag_coefficient, HorForce, R)) return 1;

    // Get the Coeff of Restitution from the user
    cout << "Please enter the Coefficient of Restitution of the ball (0 <= R <= 1): ";
    R = getValidNumber();
    // Check for valid input
    if (!value_check(ball.height, ball.mass, ball.drag_coefficient, HorForce, R)) return 1;

    // Simulate the ball dropping and bouncing
    while (n < max_bounces || ball.height > 0.0) {
        // Update the ball's state
        updateBall(ball, HorForce);

        // Update min/max and totals for averages
        minHeight = min(minHeight, ball.height);
        maxHeight = max(maxHeight, ball.height);

        minVertVelocity = min(minVertVelocity, ball.vert_velocity);
        maxVertVelocity = max(maxVertVelocity, ball.vert_velocity);

        minHorDistance = min(minHorDistance, ball.distance);
        maxHorDistance = max(maxHorDistance, ball.distance);

        minHorVelocity = min(minHorVelocity, ball.hor_vel);
        maxHorVelocity = max(maxHorVelocity, ball.hor_vel);

        minDragForce = min(minDragForce, ball.drag);
        maxDragForce = max(maxDragForce, ball.drag);

        // Accumulate totals for average calculation
        totalHeight += ball.height;
        totalVertVelocity += fabs(ball.vert_velocity);
        totalDistance += ball.distance;
        totalDragForce += ball.drag;
        totalHorVel += ball.hor_vel;

        // Store values in arrays with the same precision
        heights.push_back(stod(formatDouble(ball.height)));
        vert_velocities.push_back(stod(formatDouble(ball.vert_velocity)));
        distances.push_back(stod(formatDouble(ball.distance)));
        drag_forces.push_back(stod(formatDouble(ball.drag)));
        horizontal_velocities.push_back(stod(formatDouble(ball.hor_vel)));
        timeSteps++;

        // Display the current state of the ball
        OutputFile << "Height: " << formatDouble(ball.height)
                   << " m, Time: " << formatDouble(ball.time)
                   << " s, Vertical Velocity: " << formatDouble(ball.vert_velocity)
                   << " m/s, Drag Force: " << formatDouble(ball.drag)
                   << " N, Horizontal Distance: " << formatDouble(ball.distance)
                   << " m, Horizontal Velocity: " << formatDouble(ball.hor_vel)
                   << " m/s" << endl;

        // Introduce a delay of 0.1 seconds to simulate real time
        this_thread::sleep_for(chrono::milliseconds(static_cast<int>(dt * 1000)));
    }
    finalTime = ball.time;

    OutputFile << endl << "Maximums" << endl
               << "Max Height: " << maxHeight << " m " << endl
               << "Max Vert Vel: " << maxVertVelocity << " m/s" << endl
               << "Max Drag Force: " << maxDragForce << " N" << endl
               << "Horz Dist: " << maxHorDistance << " m" << endl
               << "Horz Vel: " << maxHorVelocity << " m/s" << endl
               << "Time Taken: " << finalTime << " s" << endl << "\n";

    // Calculate averages
    double avgHeight = totalHeight / timeSteps;
    double avgVertVelocity = totalVertVelocity / timeSteps;
    double avgDistance = totalDistance / timeSteps;
    double avgDragForce = totalDragForce / timeSteps;
    double avgHorVelocity = totalHorVel / timeSteps;

    OutputFile << "Averages" << endl
               << "Average Height: " << avgHeight << " m" << endl
               << "Average Vert Vel: " << avgVertVelocity << " m/s" << endl
               << "Average Drag Force: " << avgDragForce << " N" << endl
               << "Average Horz Dist: " << avgDistance << " m" << endl
               << "Average Horz Vel: " << avgHorVelocity << " m/s" << endl;

    OutputFile.close(); // Close the file

    SearchMenu(minVertVelocity, maxHeight, maxVertVelocity, maxDragForce, minHorDistance,
               totalHeight, totalVertVelocity, totalDistance, totalDragForce, timeSteps,
               maxHorDistance, maxHorVelocity, totalHorVel, finalTime,
               heights, vert_velocities, horizontal_velocities, distances, drag_forces, avgHorVelocity);

    return 0;
}
