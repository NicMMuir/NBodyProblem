//Node.h
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>


#define minquaddepth 10
#define minchild 4

typedef struct Node{
  int x;
  int y;
  int cmx;
  int cmy;
  float Mass;
  float side;
  bool parent;
  bool empty;
  struct Node *NE;
  struct Node *SE;
  struct Node *NW;
  struct Node *SW;
  struct Body *b;

}Node;

Node init_tree(int area){
  Node * new_Node = malloc (sizeof (Node));
  new_Node->x = area/2;
  new_Node->y = area/2;
  new_Node->side = area;
  new_Node->empty = true;
  new_Node->parent = false;
  return  *new_Node;
}


Node *Create_Node(int x , int y ,float side,bool parent ){
   Node * new_Node = malloc (sizeof (Node));
   new_Node->x = x;
   new_Node->y = y;
   new_Node->side = side;
   new_Node->parent = parent;
   new_Node->empty=true;
   return new_Node;
}

void split_Node(Node * n){
 int tmp = n->side *0.5;
 n->parent = true;
 n->NE = Create_Node(n->x+tmp*0.5,n->y+tmp*0.5,tmp,false);
 n->SE = Create_Node(n->x+tmp*0.5,n->y-tmp*0.5,tmp,false);
 n->NW = Create_Node(n->x-tmp*0.5,n->y+tmp*0.5,tmp,false);
 n->SW = Create_Node(n->x-tmp*0.5,n->y-tmp*0.5,tmp,false);
}

void Print_Node( Node  n){
  printf( "X Position : %d\n", n.x);
  printf( "Y Position : %d\n", n.y);
  printf( "is Empty  : %d\n", n.empty);
  printf("Size length : %f\n", n.side);

}

int Get_current_quad(Node * n,Body b){
  if(b.x>n->x && b.y>n->y){ //NE
    return(1);
  }else if(b.x<n->x && b.y>n->y){ //NW
    return(2);
  }else if(b.x>n->x && b.y<n->y){//SE
    return(3);
  }else if(b.x<n->x && b.y<n->y){//SW
    return(4);
  }
}

Node * get_quad_Node(Node * n , int Quad){
  if(Quad == 1){ //NE
    return(n->NE);
  }else if(Quad == 2){ //NW
    return(n->NW);
  }else if(Quad == 3){//SE
    return(n->SE);
  }else if(Quad == 4){//SW
    return(n->SW);
  }

}
