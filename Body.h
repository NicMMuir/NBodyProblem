//Body.h



#define minchild 4



typedef struct Body{
// Body ID
 int ID;
//Position X,Y
  int x;
  int y;
//Momentum X,Y
  float mx;
  float my;
  float Mass; // Mass of Body
//Quadrant

}Body;


 Body *create_Body(int ID,int size){

   Body * new_Body = malloc (sizeof (Body));;
   new_Body->ID = ID;
   new_Body->x = rand() % size;
   new_Body->y = rand() % size;

   new_Body->mx = rand() % size;
   new_Body->my = rand() % size;

   new_Body->Mass= (rand() % size)*100;
   return new_Body;
}



void Print_Body(Body * n){
  printf( "Body ID : %d\n", n->ID);
  printf( "X Position : %d\n", n->x);
  printf( "Y Position : %d\n", n->y);
  printf( "X Momentum : %f\n", n->mx);
  printf( "X Momentum : %f\n", n->my);
  printf("Mass : %f\n", n->Mass);
}



