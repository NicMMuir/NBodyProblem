#include <stdio.h>
#include "header.h"

int main() {
    // Remember to uncomment
    //srand( (unsigned)time( NULL ) );

//    struct Node* tmp = InitNode(0,0,0,0);
//    free(tmp);
//    tmp->centre_x = 1;

//    struct Node* node = InitNode(0,1,1,1);
    double size = 100;

    //struct Node* head_node = InitTree(size);

    int n = 25; // 5
    struct Body** bodies = CreateRandBodies(n, 0, 100, 0, 2, 1, 5);

    printf("########################\n");
    printf("#        BEFORE        #\n");
    printf("########################\n\n");
    PrintAllBodies(bodies, n);


    CompNBody(bodies, n, 100, 0.1);

    printf("########################\n");
    printf("#         AFTER        #\n");
    printf("########################\n\n");
    PrintAllBodies(bodies, n);


//    printf("\n\n\n");

//    for (int i = 0; i<n; i++){
//        InsertBody(head_node, bodies[i]);
//    }

//    bodies[0]->x = 1;
//    bodies[0]->y = 1;
//    bodies[0]->mass = 2;
//    PrintBody(bodies[0]);
//
//    bodies[1]->x = 2;
//    bodies[1]->y = 2;
//    bodies[0]->mass = 1;
//    PrintBody(bodies[1]);
//
//    UpdateForceOnBodyByBody(bodies[0], bodies[1]);
//    printf("\nForce: (%lf,%lf)\n", bodies[0]->force_x, bodies[0]->force_y);

//    PrintTree(head_node, 0, -1);
//    CompCentreOfMasses(head_node);
//
//    for (int i = 0; i<n; i++){
//        CompForce(bodies[i], head_node);
//    }

//    printf("##################\n");
//    printf("#     FORCES     #\n");
//    printf("##################\n");
//    for (int i = 0; i<n; i++){
//        printf("Body %d -> Force: (%lf, %lf)\n", bodies[i]->id, bodies[i]->force_x, bodies[i]->force_y);
//    }
//
//
//
//
//    FILE* fp = fopen("/home/simon/Documents/HPC/Project/NBody_Alt/dot_files/1.dot", "w+");
//    if (fp != NULL) {
//        TreeToDotFile(head_node, fp);
//        fclose(fp);
//    } else {
//        printf("FILE NOT FOUND\n");
//    }
    FreeBodies(bodies, n);
    //ResetTree(head_node);

//    GetQuadrant(head_node, body);
//    free(head_node);
//    free(body);
    return 0;
}
