//Node.h
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
  struct Node * parent;// Parent Node (Possibly to move up tree if needs be)
  struct Node * child; // Child Node

};

struct Node create_Node(int ID,int size){
   time_t t;
   srand((unsigned) time(&t));
   struct Node new_Node;
   new_Node.ID = ID;
   new_Node.x = rand() % size;
   new_Node.y = rand() % size;
   new_Node.z = rand() % size;
   new_Node.mx = rand() % size;
   new_Node.my = rand() % size;
   new_Node.mz = rand() % size;
   new_Node.Mass= (rand() % size)*100;
   new_Node.parent=NULL;
   new_Node.child=NULL;
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
