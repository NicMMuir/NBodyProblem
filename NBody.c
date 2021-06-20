#include "Body.h"

#define NumberofBodies 10
int main(){
    srand(time(NULL));
    struct Body Bodies[NumberofBodies];
    for(int k =0;k<NumberofBodies;k++){

      struct Body new_Body = create_Body(k,100);

      Bodies[k] = new_Body;
    }
    for(int k =0;k<NumberofBodies;k++){
        Print_Body(Bodies[k]);
    }


}

// void build_tree(){
//
//
//
// }
