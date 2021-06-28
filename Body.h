//Body.h

#include <stdio.h>
#include <stdlib.h>

#define minchild 4



typedef struct Body{
// Body ID
 int ID;
//Position X,Y
  int x;
  int y;
//Force in Newtons
  float Force;
  float Mass; // Mass of Body
//Quadrant

}Body;


 Body *create_Body(int ID,int size){

   Body * new_Body = malloc (sizeof (Body));;
   new_Body->ID = ID;
   new_Body->x = rand() % size;;
   new_Body->y = rand() % size;


   new_Body->Mass= (rand() % size)*100;
   return new_Body;
}



void Print_Body(Body * n){
  printf( "Body ID : %d\n", n->ID);
  printf( "X Position : %d\n", n->x);
  printf( "Y Position : %d\n", n->y);
  printf( "Force : %f\n", n->Force);
  printf("Mass : %f\n", n->Mass);
}



