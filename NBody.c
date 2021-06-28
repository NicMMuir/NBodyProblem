#include "Body.h"
#include "Node.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define NumberofBodies 100
#define area 100
#define Theta 10
#define Gravity 0.1




float distance_calc(Node *n, Body body){
  return(sqrt(pow(n->x-body.x,2)+pow(n->y-body.y,2)));
}
float distance_calc2(Body *n, Body body){
    return(sqrt(pow(n->x-body.x,2)+pow(n->y-body.y,2)));
}
float calculate_Force(Node *n, Body body){
  float distance = distance_calc(n,body);
  return((Gravity*n->Mass*body.Mass)/pow(distance,2));
}
float calc_force2(Body *body1,Body body){
  float distance = distance_calc2(body1,body);
  return((Gravity*body1->Mass*body.Mass)/pow(distance,2));
}


void insert(Node *n, Body * body){

  int current_quad = 0;
  if(n->parent == true){
    current_quad = Get_current_quad(n,&body);
    insert(get_quad_Node(n,current_quad), body);
  }else if(n->empty == true){
    Insert_Body(n,*body);
  }else{
    split_Node(n);
    current_quad = Get_current_quad(n, body);
    insert(get_quad_Node(n,current_quad) , body);
    current_quad = Get_current_quad(n,n->b);
    insert(get_quad_Node(n,current_quad ) , n->b);
  }
}


float Force_Calc(Node *n, Body body){

  if((n->side)/distance_calc(n,body) < Theta){
    return( calculate_Force(n,body));
  }else if(n->parent == true){
    float force = 0;
    if(n->NE->empty == false){
      force = force+ Force_Calc(n->NE,body);
    }
    if(n->SE->empty == false){
      force = force+ Force_Calc(n->SE,body);
    }
    if(n->NW->empty == false){
      force = force+ Force_Calc(n->NW,body);
    }
    if(n->SW->empty == false){
      force = force+ Force_Calc(n->SW,body);
    }
    return(force);

  }else if(n->empty == true){
    printf("this is why %s\n","");
    return(0);
  }else{
    return(calc_force2(n->b,body));
  }

  }







int main(){
    srand(time(NULL));
    Body *Bodies[NumberofBodies];
    for(int k =0;k<NumberofBodies;k++){
      Bodies[k] = create_Body(k,area);
    }

//     for(int k =0;k<NumberofBodies;k++){
//         Print_Body(Bodies[k]);
//     }


    Node TreeRoot = init_tree(area);

    // Print_Node(TreeRoot);
    //Build tree
    for(int k =0;k<NumberofBodies;k++){
        insert(&TreeRoot, Bodies[k]);
    }
    // Force calc
    for(int k =0;k<NumberofBodies;k++){
        float Force = Force_Calc(&TreeRoot,*Bodies[k]);
        Bodies[k]->Force = Force;
        printf("force on this Bitch : %s %d %s %f\n","Body ID:",k, ":" ,Force );
        Print_Body(Bodies[k]);
    }



    printf("complete %s\n","");

}
