//Body.h
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


#define minquaddepth 10
#define minchild 4



struct Body{
// Body ID
 int ID;
//Position X,Y,Z
  int x;
  int y;

//Momentum X,Y,Z
  float mx;
  float my;
  float Mass; // Mass of Body
  //Quadrant
  int Quadrant[minquaddepth]; //stores depth of quadrant ie (1,1,3,4) means in 4th quad of third quad of first quad of first quad
};


struct Body create_Body(int ID,int size){

   struct Body new_Body;
   new_Body.ID = ID;
   new_Body.x = rand() % size;
   new_Body.y = rand() % size;

   new_Body.mx = rand() % size;
   new_Body.my = rand() % size;

   new_Body.Mass= (rand() % size)*100;
   return new_Body;
}



void Print_Body(struct Body n){
  printf( "Body ID : %d\n", n.ID);
  printf( "X Position : %d\n", n.x);
  printf( "Y Position : %d\n", n.y);
  printf( "X Momentum : %f\n", n.mx);
  printf( "X Momentum : %f\n", n.my);
  printf("Mass : %f\n", n.Mass);
}


float Bdist(struct Body n1 , struct Body n2){
  return(sqrt(pow(n1.x-n2.x,2)+pow(n1.y-n2.y,2)));
}

float Bforce(struct Body n1 , struct Body n2){
    float d = Bdist(n1,n2);
    return ((n1.x - n2.x) + (n1.y-n2.y)) * (n1.Mass * n2.Mass / pow(d,3));
}
