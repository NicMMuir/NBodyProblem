//Node.h
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include<stdbool.h>

#define minquaddepth 10
#define minchild 4

struct Node{
  int x;
  int y;
  float side;
  bool parent;
  struct Node *NE;
  struct Node *SE;
  struct Node *NW;
  struct Node *SW;
  bool div;
  struct Body *b;

};


struct Node half_Node(int x , int y , float side,bool parent){
   struct Node new_Node;
   new_Node.x = x;
   new_Node.y = y;

   new_Node.side = side;
   new_Node.parent = parent;
   return new_Node;
}

struct Node create_Node(int x , int y ,int z, float side,bool parent){
   struct Node new_Node;
   new_Node.x = x;
   new_Node.y = y;

   new_Node.side = side;
   new_Node.parent = parent;
   return new_Node;
}

struct Node split_Node(struct Node n ){
  int tmp = n.side *0.5;
 struct Node NE = half_Node(n.x+tmp*0.5,n.y+tmp*0.5,tmp,false);
 struct Node SE = half_Node(n.x+tmp*0.5,n.y-tmp*0.5,tmp,false);
 struct Node NW = half_Node(n.x-tmp*0.5,n.y+tmp*0.5,tmp,false);
 struct Node SW = half_Node(n.x-tmp*0.5,n.y-tmp*0.5,tmp,false);

 n.NE = &NE;
 n.SE = &SE;
 n.NW = &NW;
 n.SW = &NE;

 return n;
}


void next_quad(struct Node currnode){
  struct Node newnode;


}


void Print_Node(struct Node n){
  printf( "X Position : %d\n", n.x);
  printf( "Y Position : %d\n", n.y);
  printf("Size length : %f\n", n.side);
}


float Ndist(struct Node n1 , struct Node n2){
  return(sqrt(pow(n1.x-n2.x,2)+pow(n1.y-n2.y,2)));
}
