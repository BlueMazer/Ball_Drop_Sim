//
// Copyright (c) [2024] [Rayan Raad]
//
// This software is released under the MIT License.
// See the LICENSE file for details.
//
#ifndef BALL_DROP_PHYS_BALL_H
#define BALL_DROP_PHYS_BALL_H

#include <vector>
#include <string>

struct Ball { // Declare the Struct for the Ball
    double drag;
    double height;
    double vert_velocity;
    double time;
    double mass;
    double hor_vel;
    double distance;
    double drag_coefficient;
};

// Declare global variables as extern
extern double R;
extern int n;

// Declare every function and their parameters in here first
double calculateDrag(double velocity, double drag_coefficient);
std::string formatDouble(double value);
bool isNumber(const std::string& s);
double getValidNumber();
bool value_check(double height, double mass, double drag_coefficient, double HorForce, double R);
void updateBall(Ball& ball, double HorForce);
void DisplayAnalyzedResults(double minVertVelocity, double maxHeight, double maxVertVelocity, double maxDragForce,
                            double totalHeight, double totalVertVelocity, double totalDistance, double totalDragForce,
                            double timeSteps, double maxHorDistance, double maxHorVelocity, double finalTime);
double snapValue(const std::vector<double>& values, double target);
void SearchMenu(double minVertVelocity, double maxHeight, double maxVertVelocity, double maxDragForce, double minHorDistance,
                double totalHeight, double totalVertVelocity, double totalDistance, double totalDragForce, int timeSteps,
                double maxHorDistance, double maxHorVelocity, double totalHorVel, double finalTime,
                const std::vector<double> &heights, const std::vector<double> &vert_velocities,
                const std::vector<double> &horizontal_velocities, const std::vector<double> &distances,
                const std::vector<double> &drag_forces, double avgHorVelocity);
double getValidNumber(const std::string& prompt);

#endif //BALL_DROP_PHYS_BALL_H
