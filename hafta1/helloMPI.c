#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(void)
{
    int size, rank;

    MPI_Init(NULL,NULL);

    //num. of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("\nhello world from process %d of %d\n", rank, size);

    MPI_Finalize();
}
