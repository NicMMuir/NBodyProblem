#include <stdio.h>
#include "header.h"
#include <time.h>

int main() {

    double size = 100;
    clock_t t1, t2;
    double timerun;

    int n = 100; // 5
    struct Body** bodies = CreateRandBodies(n, 0, 100, 0, 2, 1, 100);
    printf("100 Bodies on 2 Nodes 100 steps\n");
    printf("########################\n");
    printf("#        BEFORE        #\n");
    printf("########################\n\n");
    PrintBody(bodies[0]);

    t1 = clock();
    CompNBody(bodies, n, 100, 0.1);
    t2 = clock();
    timerun = ((double)(t2-t1))/CLOCKS_PER_SEC;

    printf("########################\n");
    printf("#         AFTER        #\n");
    printf("########################\n\n");
    PrintBody(bodies[0]);
    printf("\n########################\n");
    printf( "Elapsed time is %f\n", timerun );

    FreeBodies(bodies, n);


    return 0;
}
