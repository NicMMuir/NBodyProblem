#include "header.h"
#define NumNodes 8


MPI_Datatype mpi_body_type;

//slave node arrays
struct Body slavebodies[1000];




void CompNBody(struct Body **bodies, int n, int no_time_step, double time_step){
    int size = 100000; // Should be computed from bodies along with centre -> probs?
    const char *file_name = "data/points.txt";
    int totElements , n_elements_Process , nodecounter;
    struct Body slavebodiesret[100];
    MPI_Status status;
    struct Body **sbodies = malloc(n * sizeof(struct Body*));

//////////////////////////////////////////////////////////////

    // Clear contents
    FILE* fp = fopen(file_name, "w+");
    fprintf(fp, "");
    fclose(fp);
    fp = fopen(file_name, "a");
////////////////////////////////////////////////////////////////

MPI_Init(NULL, NULL);
int mpisize, mpirank;
MPI_Comm_size(MPI_COMM_WORLD, &mpisize);
MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);
CreateMPIType();
  for (int t = 1; t<=no_time_step; t++){

    double min_pos, max_pos;
    CompMinMaxPosition(bodies, n, &min_pos, &max_pos);

    struct Node* head_node = InitTree(min_pos, max_pos);

    // Create Tree Stage
    for (int i = 0; i<n; i++){
        InsertBody(head_node, bodies[i]);
    }

    // Compute Centre of Masses
    CompCentreOfMasses(head_node);




    //Global bodies for braudcasting
    struct Body Globalbodies[n];
    //create array of bodies (not array of body pointers)
    for(int k = 0;k<n;k++){
      Globalbodies[k] = *bodies[k];
    }





if(mpirank == 0){
    int elementsperslave = n/NumNodes;
  //send to all slave nodes

  for(int i = 1;i<mpisize;i++){
    MPI_Send(&n,1, MPI_INT, i, 0,MPI_COMM_WORLD);
    MPI_Send(&elementsperslave,1, MPI_INT, i, 0,MPI_COMM_WORLD);
    MPI_Send(&i,1, MPI_INT, i, 0,MPI_COMM_WORLD);
    MPI_Send(&Globalbodies,n,mpi_body_type,i,0,MPI_COMM_WORLD);
  }

    for (int i = 0; i<n_elements_Process; i++){
        CompForce(bodies[i], head_node);
    }

  for (int i = 1; i < mpisize; i++) {

            MPI_Recv(&slavebodiesret, 100, mpi_body_type,MPI_ANY_SOURCE, 0,MPI_COMM_WORLD,&status);
            //copy form slave to bodies array
            int sender = status.MPI_SOURCE;
            for(int z = sender*elementsperslave ;z < sender*elementsperslave+elementsperslave;z++){
              HardCopy(bodies[z],&slavebodiesret[z]);
            }

        }


  } else {

        MPI_Recv(&totElements,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        MPI_Recv(&n_elements_Process,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        MPI_Recv(&nodecounter,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        MPI_Recv(&slavebodies,totElements,mpi_body_type,0,0,MPI_COMM_WORLD,&status);

        //Construct new **Sbody pointer array
        for(int l = 0;l<totElements;l++){
          sbodies[l] =  &slavebodies[l];
        }

        double min_pos, max_pos;
        CompMinMaxPosition(sbodies, totElements, &min_pos, &max_pos);

        struct Node* head_node = InitTree(min_pos, max_pos);

        // Create Tree Stage
        for (int i = 0; i<totElements; i++){
            InsertBody(head_node, sbodies[i]);
        }

        // Compute Centre of Masses
        CompCentreOfMasses(head_node);



        // Compute Forces on Each Body Stage
        for (int i = nodecounter*n_elements_Process; i<nodecounter*n_elements_Process+n_elements_Process; i++){
            CompForce(sbodies[i], head_node);
        }

        MPI_Send(&slavebodies,totElements,mpi_body_type,0,0,MPI_COMM_WORLD);

      }



        for (int i = 0; i<n; i++){
            UpdatePosAndVel(bodies[i], time_step);
        }
        ResetTree(head_node);



        // Compute New Velocities and New Positions Stage


        SaveBodiesToFile(fp,bodies,n,t);
    }
    MPI_Type_free(&mpi_body_type);
    MPI_Finalize();

    fclose(fp);
}


void CreateMPIType(){
  const int nitems = 8;
	int blocklengths[8] = {1,1,1,1,1,1,1,1};
	MPI_Datatype types[8] = {MPI_INT,MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE};
	MPI_Aint offsets[8];
	offsets[0] = offsetof(struct Body , id);
	offsets[1] = offsetof(struct Body , x);
	offsets[2] = offsetof(struct Body , y);
	offsets[3] = offsetof(struct Body , mass);
	offsets[4] = offsetof(struct Body , vel_x);
	offsets[5] = offsetof(struct Body , vel_y);
	offsets[6] = offsetof(struct Body , force_x);
	offsets[7] = offsetof(struct Body , force_y);
	MPI_Type_create_struct(nitems,blocklengths,offsets,types, &mpi_body_type);
	MPI_Type_commit(&mpi_body_type);
}

// TODO
double GetMaxBound(struct Body **bodies, int n){
    //
}
