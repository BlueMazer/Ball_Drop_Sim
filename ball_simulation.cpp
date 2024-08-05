//
// Copyright (c) [2024] [Rayan Raad]
//
// This software is released under the MIT License.
// See the LICENSE file for details.
//

#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <algorithm>
#include <fstream>
#include <limits>
#include "common.h"
#include "Ball.h"

using namespace std;

constexpr double g = 9.81; // acceleration due to gravity (m/s^2)
constexpr double dt = 0.01; // time step size (s)
const int max_bounces = 15; // Maximum number of bounces

// Function to calculate drag force based on velocity
double calculateDrag(double velocity, double drag_coefficient) {
    return 0.5 * drag_coefficient * velocity * velocity;
}

// Function for Formatting of Doubles
std::string formatDouble(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(4) << value;
    return oss.str();
}

// Checks if the value being inputted is valid
bool isNumber(const std::string& s) {
    std::istringstream iss(s);
    double d;
    char c;
    return iss >> d && !(iss >> c);
}

// Function to check if any input value is negative
bool value_check(double height, double mass, double drag_coefficient, double HorForce, double R) {
    if (height <= 0 || mass <= 0 || drag_coefficient < 0 || HorForce < 0 || R < 0 || R > 1) {
        cout << "Value does not fit parameter" << endl;
        return false;
    }
    return true;
}

// Function to update the ball's state
void updateBall(Ball& ball, double HorForce) {
    ball.drag = calculateDrag(ball.vert_velocity, ball.drag_coefficient);
    double vert_acceleration = g - (ball.drag / ball.mass);
    ball.vert_velocity += vert_acceleration * dt;
    ball.height -= ball.vert_velocity * dt;

    if (ball.height <= 0.0) {
        ball.height = 0.0;
        ball.vert_velocity = -ball.vert_velocity * R;
        n++;
    }

    double hor_accel = HorForce / ball.mass;
    ball.hor_vel += hor_accel * dt;
    ball.distance += ball.hor_vel * dt;

    ball.time += dt;
}

void DisplayAnalyzedResults(double minVertVelocity, double maxHeight, double maxVertVelocity, double maxDragForce,
                            double totalHeight, double totalVertVelocity, double totalDistance,
                            double totalDragForce, double totalHorVel, int timeSteps, double maxHorDistance,
                            double maxHorVelocity, double finalTime, double avgHorVelocity) {
    cout << endl << "Maximums" << endl
         << "Max Height: " << maxHeight << " m " << endl
         << "Max Vert Vel: " << maxVertVelocity << " m/s" << endl
         << "Max Drag Force: " << maxDragForce << " N" << endl
         << "Horz Dist: " << maxHorDistance << " m" << endl
         << "Max Horz Vel: " << maxHorVelocity << " m/s" << endl
         << "Time Taken: " << finalTime << " s" << endl << endl;

    cout << "Minimums" << endl
         << "Min Vert Vel: " << minVertVelocity << " m/s" << endl << endl;

    double avgHeight = totalHeight / timeSteps;
    double avgVertVelocity = totalVertVelocity / timeSteps;
    double avgDistance = totalDistance / timeSteps;
    double avgDragForce = totalDragForce / timeSteps;
    avgHorVelocity = totalHorVel / timeSteps;

    cout << "Averages" << endl
         << "Average Height: " << avgHeight << " m" << endl
         << "Average Vert Vel: " << avgVertVelocity << " m/s" << endl
         << "Average Drag Force: " << avgDragForce << " N" << endl
         << "Average Horz Dist: " << avgDistance << " m" << endl
         << "Average Horz Vel: " << avgHorVelocity << " m/s" << endl << "\n" << endl;
}

double snapValue(const vector<double>& values, double target) {
    if (values.empty()) {
        throw runtime_error("The vector is empty.");
    }

    double closest = values[0];
    double min_diff = fabs(target - closest);

    for (double value : values) {
        double diff = fabs(target - value);
        if (diff < min_diff) {
            closest = value;
            min_diff = diff;
        }
    }

    return closest;
}

void SearchMenu(double minVertVelocity, double maxHeight, double maxVertVelocity, double maxDragForce, double minHorDistance,
                double totalHeight, double totalVertVelocity, double totalDistance, double totalDragForce, int timeSteps,
                double maxHorDistance, double maxHorVelocity, double totalHorVel, double finalTime,
                const std::vector<double> &heights, const std::vector<double> &vert_velocities,
                const std::vector<double> &horizontal_velocities, const std::vector<double> &distances,
                const std::vector<double> &drag_forces, double avgHorVelocity) {
    string fileName = "/Users/rayanraad/PycharmProjects/Ball_Drop_Phys_Graphing/simulation_C++_output_Python_Input.txt"; // File Path
    char SearchChoice;

    // Map to associate menu choices with their corresponding terms (unordered is faster?)
    unordered_map<char, string> searchTerms = {
            {'A', "Time"},
            {'B', "Height"},
            {'C', "Vertical Velocity"},
            {'D', "Horizontal Distance"},
            {'E', "Horizontal Velocity"},
            {'F', "Drag Force"}
    };

    cout << "What would you like to examine:" << endl
         << "A) Time" << " (0s - " << finalTime << "s)" << endl
         << "B) Height" << " (0m - " << maxHeight << "m)"
         << endl
         << "C) Vertical Velocity" << " (" << minVertVelocity << "m/s- " << maxVertVelocity << "m/s)"
         << endl
         << "D) Horizontal Distance" << " (0m- " << maxHorDistance << "m)"
         << endl
         << "E) Horizontal Velocity" << " (0m/s - " << maxHorVelocity << "m/s)"
         << endl
         << "F) Drag Force" << " (0N - " << maxDragForce << "N)"
         << endl
         << "G) Averages, Minimums, and Maximums" << endl
         << "H) Leave" << endl
         << "Input Choice: ";
    cin >> SearchChoice;
    if (SearchChoice >= 'a' && SearchChoice <= 'z') {// Valid range of uppercase letters to Convert
        SearchChoice = toupper(static_cast<unsigned char>(SearchChoice));
    }

    // Check if the choice is valid
    if (searchTerms.find(SearchChoice) == searchTerms.end() &&
        SearchChoice != 'G' && SearchChoice != 'H') {
        cout << "Invalid choice. Please select a valid option." << endl;
        SearchMenu(minVertVelocity, maxHeight, maxVertVelocity, maxDragForce, totalHeight,
                   totalVertVelocity, totalDistance, totalDragForce,
                   minHorDistance, timeSteps, maxHorDistance, maxHorVelocity, totalHorVel, finalTime,
                   heights, vert_velocities, horizontal_velocities, distances, drag_forces, avgHorVelocity);
        return; // Exit the current function to avoid further execution
    }

    if (SearchChoice == 'G') {
        // Display averages and maximums
        DisplayAnalyzedResults(minVertVelocity, maxHeight, maxVertVelocity, maxDragForce,
                               totalHeight, totalVertVelocity, totalDistance,
                               totalDragForce, totalHorVel, timeSteps, maxHorDistance,
                               maxHorVelocity, finalTime, avgHorVelocity);
        SearchMenu(minVertVelocity, maxHeight, maxVertVelocity, maxDragForce, totalHeight,
                   totalVertVelocity, totalDistance, totalDragForce,
                   minHorDistance, timeSteps, maxHorDistance, maxHorVelocity, totalHorVel, finalTime,
                   heights, vert_velocities, horizontal_velocities, distances, drag_forces, avgHorVelocity);
        return; // Exit the current function to avoid further execution
    }
    if (SearchChoice == 'H') {
        cout << "Simulation Ending... ";
        exit(0); //Terminates the Program
    }

    string searchTerm = searchTerms[SearchChoice]; // Get the term corresponding to the choice
    cout << "\nYou chose to examine " << searchTerm << "." << endl;
    cout << "Enter the value you want to Examine (Add Spaces after Number): ";

    string SearchString;
    cin.ignore(); // Clear the newline character from the input buffer
    getline(cin, SearchString); // Read the entire line including spaces

    // Build the grep command
    string command = "grep -i \"" + searchTerm + ": " + SearchString + "\" " + fileName;

    // Output the command for debugging
    cout << "Executing command: " << command << endl;

    // Execute the grep command
    int result = system(command.c_str());
    if (result != 0) {
        cout << "\nNo exact instance found. Finding closest approximation... " << endl;

        double searchValue = stod(SearchString);
        double closestValue = 0.0;
        bool found = false;

        switch (SearchChoice) {
            case 'B':
                closestValue = snapValue(heights, searchValue);
                found = true;
                break;
            case 'C':
                closestValue = snapValue(vert_velocities, searchValue);
                found = true;
                break;
            case 'D':
                closestValue = snapValue(distances, searchValue);
                found = true;
                break;
            case 'E':
                closestValue = snapValue(horizontal_velocities, searchValue);
                found = true;
                break;
            case 'F':
                closestValue = snapValue(drag_forces, searchValue);
                found = true;
                break;
            default:
                cout << "Unsupported search option for snapping." << endl;
                SearchMenu(minVertVelocity, maxHeight, maxVertVelocity, maxDragForce, totalHeight,
                           totalVertVelocity, totalDistance, totalDragForce,
                           minHorDistance, timeSteps, maxHorDistance, maxHorVelocity, totalHorVel, finalTime,
                           heights, vert_velocities, horizontal_velocities, distances, drag_forces, avgHorVelocity);
                return; // Exit the current function to avoid further execution
        }
        if (found) {
            string closestValueStr = formatDouble(closestValue);
            command = "grep -i \"" + searchTerm + ": " + closestValueStr + "\" " + fileName;

            cout << "Executing command: " << command << endl;
            result = system(command.c_str());
            if (result != 0) {
                cout << "No exact instance found for the closest value. Please verify the data." << endl;
            }
        }
        SearchMenu(minVertVelocity, maxHeight, maxVertVelocity, maxDragForce, totalHeight,
                   totalVertVelocity, totalDistance, totalDragForce,
                   minHorDistance, timeSteps, maxHorDistance, maxHorVelocity, totalHorVel, finalTime,
                   heights, vert_velocities, horizontal_velocities, distances, drag_forces, avgHorVelocity);
        return; // Exit the current function to avoid further execution
    }
}
