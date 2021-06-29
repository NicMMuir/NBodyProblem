#include "header.h"

void CompNBody(struct Body **bodies, int n, int no_time_step, double time_step){
    int size = 100000; // Should be computed from bodies along with centre -> probs?
    const char *file_name = "/home/simon/Documents/HPC/Project/NBody_Alt/data/points.txt";

    // Clear contents
    FILE* fp = fopen(file_name, "w+");
    fprintf(fp, "");
    fclose(fp);

    fp = fopen(file_name, "a");

//    if (fp != NULL) {
//        TreeToDotFile(head_node, fp);
//        fclose(fp);
//    } else {
//        printf("FILE NOT FOUND\n");
//    }

    for (int t = 1; t<=no_time_step; t++){
        double min_pos, max_pos;
        CompMinMaxPosition(bodies, n, &min_pos, &max_pos);

        struct Node* head_node = InitTree(min_pos, max_pos);

        // Create Tree Stage
        for (int i = 0; i<n; i++){
            InsertBody(head_node, bodies[i]);
        }

        // Compute Centre of Masses
        CompCentreOfMasses(head_node);

        // Compute Forces on Each Body Stage
        for (int i = 0; i<n; i++){
            CompForce(bodies[i], head_node);
        }

        // Compute New Velocities and New Positions Stage
        for (int i = 0; i<n; i++){
//            PrintBody(bodies[i]);
            UpdatePosAndVel(bodies[i], time_step);
        }
        ResetTree(head_node);

        SaveBodiesToFile(fp,bodies,n,t);
    }

    fclose(fp);
}

// TODO
double GetMaxBound(struct Body **bodies, int n){
    //
}