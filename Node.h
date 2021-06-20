//Node.h
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define minquaddepth 10
#define minchild 4

struct Node{
// Node ID
 int ID;
//Position X,Y,Z
  int x;
  int y;
  int z;
//Momentum X,Y,Z
  float mx;
  float my;
  float mz;
  float Mass; // Mass of Node
  //Quadrant
  struct Node Child[minchild]
  int Quadrant[minquaddepth]; //stores depth of quadrant ie (1,1,3,4) means in 4th quad of third quad of first quad of first quad
};

struct Node create_Node(int ID,int size){
   struct Node new_Node;
   new_Node.ID = ID;
   new_Node.x = rand() % size;
   new_Node.y = rand() % size;
   new_Node.z = rand() % size;
   new_Node.mx = rand() % size;
   new_Node.my = rand() % size;
   new_Node.mz = rand() % size;
   new_Node.Mass= (rand() % size)*100;
   return new_Node;
}


void Print_Node(struct Node n){
  printf( "Node ID : %d\n", n.ID);
  printf( "X Position : %d\n", n.x);
  printf( "Y Position : %d\n", n.y);
  printf( "Z Position : %d\n", n.z);
  printf( "X Momentum : %f\n", n.mx);
  printf( "X Momentum : %f\n", n.my);
  printf( "X Momentum : %f\n", n.mz);
  printf("Mass : %f\n", n.Mass);
}


float dist(struct Node n1 , struct Node n2){
  return(sqrt(pow(n1.x-n2.x,2)+pow(n1.y-n2.y,2)+pow(n1.z-n2.y,2)));
}

float force(struct Node n1 , struct Node n2){
    float d = dist(n1,n2);
    return ((n1.x - n2.x) + (n1.y-n2.y) + (n1.z-n2.z)) * (n1.Mass * n2.Mass / pow(d,3));
}
