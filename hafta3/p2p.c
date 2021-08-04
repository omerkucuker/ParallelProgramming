#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define TAG 777
#define COMM MPI_COMM_WORLD

int main(void){

MPI_Init(NULL,NULL);

int rank, size;

MPI_Comm_rank(COMM, &rank);
MPI_Comm_size(COMM, &size);

//int x = -1;

MPI_Status *stat;
int x;

if(rank== MASTER)
    x=100;
else if (rank == 1)
    x = 300;
else
    x=300;


if(rank== MASTER){
    MPI_Send(&x, 1, MPI_INT,1,TAG,COMM);
    MPI_Send(&x, 1, MPI_INT,2,TAG+1,COMM); //farklı tag id den göndermemiz gerekiyor
}
else{
    //MPI_Recv(&x, 1, MPI_INT,MASTER,TAG,COMM,stat); //MPI_ANY_TAG tag aynı olmaması gerekiyor 1. ile 2. nin
    MPI_Recv(&x, 1, MPI_INT,MASTER,MPI_ANY_TAG,COMM,stat);
}

printf("Rank = %d: \t my x = %d \t adress = %p \n", rank, x, &x);

MPI_Finalize();


}
