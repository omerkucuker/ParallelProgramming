#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define TAG 777
#define COMM MPI_COMM_WORLD
#define N 1000

int main(void)
{

    MPI_Init(NULL, NULL);

    int rank, size;

    MPI_Comm_rank(COMM, &rank);
    MPI_Comm_size(COMM, &size);

    MPI_Status *stat;

  //Only for 2 processes
  double *dizi = (double *)calloc(N, sizeof(double));
   
   if(rank == 0){
       MPI_Send( dizi , N , MPI_DOUBLE , 1 , TAG , COMM);

       //eksik
   }else{

       MPI_Recv( dizi , N , MPI_DOUBLE , 0, TAG, COMM, stat);
       //eksik
   }

    MPI_Finalize();
}
