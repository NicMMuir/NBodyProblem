#include "Body.h"
#include "Node.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define NumberofBodies 10
#define area 100


void Insert_Body(Node * n ,Body *b){
  n->b = b;
  n->empty = false;
}


void insert(Node *n, Body body){

  int current_quad = 0;
  if(n->parent == true){
    current_quad = Get_current_quad(n,body);
    insert(get_quad_Node(n,current_quad), body);
    printf("%s\n", "here");
  }else if(n->empty){
    Insert_Body(n,&body);
      n->empty = true;
  }else{
    split_Node(n);
    current_quad = Get_current_quad(n,body);
    insert(get_quad_Node(n,current_quad ) , body);
    current_quad = Get_current_quad(n,*n->b);
    insert(get_quad_Node(n,current_quad ) , *n->b);

  }

    Print_Node(*n);
    Print_Body(n->b);
}





int main(){
    srand(time(NULL));
    Body *Bodies[NumberofBodies];
    for(int k =0;k<NumberofBodies;k++){

      Bodies[k] = create_Body(k,area);
    }
    // for(int k =0;k<NumberofBodies;k++){
    //     Print_Body(Bodies[k]);
    // }


    Node TreeRoot = init_tree(area);

    // Print_Node(TreeRoot);

    for(int k =0;k<NumberofBodies;k++){
        insert(&TreeRoot, *Bodies[k]);
    }


    printf("complete %s\n","");

}
