#include <stdio.h>
#include "header.h"

int main() {

    double size = 100;



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

    FreeBodies(bodies, n);

    return 0;
}
