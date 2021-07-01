#include "Body.h"
#include "header.h"

struct Body* InitBody(int id, double x, double y, double vel_x, double vel_y, double mass){
    struct Body* body = (struct Body*) malloc(sizeof (struct Body));
    body->id = id;
    body->x = x;
    body->y = y;
    body->vel_x=vel_x;
    body->vel_y=vel_y;
    body->mass=mass;
    body->force_x = 0;
    body->force_y = 0;
    return body;
}

struct Body** CreateRandBodies(int n, double xy_min, double xy_max, double vel_min, double vel_max,
        double mass_min, double mass_max){

    struct Body** bodies = malloc(n * sizeof(struct Body*));
    for (int i = 0; i<n; i++){
        double x = RandFloat(xy_min, xy_max), y = RandFloat(xy_min, xy_max);
        double vel_x = RandFloat(vel_min, vel_max), vel_y = RandFloat(vel_min, vel_max);
        double mass = RandFloat(mass_min, mass_max);
        bodies[i] = InitBody(i, x, y, vel_x, vel_y, mass);
    }
    return bodies;
}

void FreeBodies(struct Body** bodies, int n){
    for (int i = 0; i<n; i++){
        free(bodies[i]);
    }
    free(bodies);
}

void PrintBody(struct Body* body){
    printf(" BODY - %d\n", body->id);
    printf("-----------\n");
    printf("Pos: (%lf, %lf)\n", body->x, body->y);
    printf("Vel: (%lf, %lf)\n", body->vel_x, body->vel_y);
    printf("Mass: %lf\n", body->mass);
}

void PrintAllBodies(struct Body** bodies, int n){
    for (int i = 0; i<n; i++){
        PrintBody(bodies[i]);
        printf("\n");
    }
}

void SaveBodiesToFile(FILE *fp, struct Body** bodies, int n, int time_step){
    fprintf(fp, "%d#", time_step);
    for (int i = 0; i<n; i++){
        //x,y,vel_x,vel_y;
        fprintf(fp, "%lf,%lf,%lf,%lf", bodies[i]->x, bodies[i]->y,
                bodies[i]->vel_x, bodies[i]->vel_y);
        if (i != n - 1){
            fprintf(fp, ";");
        }
    }
    fprintf(fp, "\n");
}

// Generate random double in [a,b]
double RandFloat(double a, double b){
    double range = b - a;
    double offset = a;
    double rand_no = (double) rand()/((double)RAND_MAX/range) + offset;
    return rand_no;
}

// Calculating from Newtons Second Law and Kinematics Equations
// Assuming forces have been calculated
void UpdatePosAndVel(struct Body *body, double time_step){
    // Force
    double fx = body->force_x, fy = body->force_y;
    // Mass
    double m = body->mass;
    // Change in time
    double delta_t = time_step;

    // Initial Position
//    double xi = body->x, yi = body->y;
    double xi = body->x, yi = body->y;

    // Change in Position
    double delta_x, delta_y;

    // Initial Velocity
    double vx_i = body->vel_x, vy_i = body->vel_y;
    // Final Velocity
    double vx_f, vy_f;

    // Acceleration - Newtons Second Law
    double ax = fx/m, ay=fy/m;

    // Kinematics Equations
    // Velocity
    vx_f = vx_i + ax*delta_t;
    vy_f = vy_i + ay*delta_t;
    body->vel_x = vx_f;
    body->vel_y = vy_f;

    // Change in Position
    delta_x = (vx_f+vx_i)/2.0 * delta_t;
    delta_y = (vy_f+vy_i)/2.0 * delta_t;

    body->x = xi + delta_x;
    body->y = yi + delta_y;
}

void CompMinMaxPosition(struct Body** bodies, int n, double *min_ptr, double *max_ptr){
    double min_val = DBL_MAX;
    double max_val = -DBL_MAX;
    for (int i = 0; i<n; i++){
//        bodies[i]->x
        // Min Val
        if (bodies[i]->x < min_val){
            min_val = bodies[i]->x;
        }
        if (bodies[i]->y < min_val){
            min_val = bodies[i]->y;
        }

        // Max Val
        if (bodies[i]->x > max_val){
            max_val = bodies[i]->x;
        }
        if (bodies[i]->y > max_val){
            max_val = bodies[i]->y;
        }
    }

    *min_ptr = min_val;
    *max_ptr = max_val;
}

void HardCopy(struct Body* body1, struct Body* body2){
  body1->x = body2->x;
  body1->y = body2->y;
  body1->vel_x= body2->vel_x;
  body1->vel_y= body2-> vel_y;
  body1->mass= body2->mass;
  body1->force_x = body2->force_x;
  body1->force_y = body2->force_y;
}
