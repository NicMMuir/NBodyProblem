//
// Created by simon on 2021/06/27.
//

#ifndef NBODY_ALT_BODY_H
#define NBODY_ALT_BODY_H

#include "header.h"

struct Body{
    int id;

    // Measured in m
    double x, y;

    // Measured in kg
    double mass;

    // Momentum
    //double mx, my;
    // Velocity - Need to use velocity
    // Measured in m*s^-1
    double vel_x, vel_y;

    double force_x, force_y;
};

struct Body* InitBody(int id, double x, double y, double vel_x, double vel_y, double mass);

struct Body** CreateRandBodies(int n, double xy_min, double xy_max, double vel_min, double vel_max,
                               double mass_min, double mass_max);

void FreeBodies(struct Body** bodies, int n);
void PrintBody(struct Body* body);
void PrintAllBodies(struct Body** bodies, int n);
double RandFloat(double a, double b);
void UpdatePosAndVel(struct Body *body, double time_step);
void SaveBodiesToFile(FILE *fp, struct Body** bodies, int n, int time_step);
void CompMinMaxPosition(struct Body** bodies, int n, double *min_ptr, double *max_ptr);

#endif //NBODY_ALT_BODY_H
