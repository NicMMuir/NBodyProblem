#include "Node.h"

#define NumberofBodies 10
int main(){
    srand(time(NULL));
    struct Node Bodies[NumberofBodies];
    for(int k =0;k<NumberofBodies;k++){

      struct Node new_Node = create_Node(k,100);

      Bodies[k] = new_Node;
    }
    for(int k =0;k<NumberofBodies;k++){
        Print_Node(Bodies[k]);
    }


}

// void build_tree(){
//
//
//
// }
