//Node.h
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define minquaddepth 10
#define minchild 4

struct Node{
  int x;
  int y;
  int z;

  float side;

  struct Node NE;
  struct Node SE;
  struct Node NW;
  struct Node SW;
  bool div;
  struct Body *b;

};

struct Node create_Node(){
   struct Node new_Node;
   new_Node.ID = ID;
   new_Node.x = 0;
   new_Node.y = 0;
   new_Node.z = 0;
   new_Node.side = 1;
   return new_Node;
}


void Print_Node(struct Node n){
  printf( "Node ID : %d\n", n.ID);
  printf( "X Position : %d\n", n.x);
  printf( "Y Position : %d\n", n.y);
  printf( "Z Position : %d\n", n.z);
  printf("Size length : %f\n", n.side);
}


float dist(struct Node n1 , struct Node n2){
  return(sqrt(pow(n1.x-n2.x,2)+pow(n1.y-n2.y,2)+pow(n1.z-n2.y,2)));
}

float force(struct Node n1 , struct Node n2){
    float d = dist(n1,n2);
    return ((n1.x - n2.x) + (n1.y-n2.y) + (n1.z-n2.z)) * (n1.Mass * n2.Mass / pow(d,3));
}
