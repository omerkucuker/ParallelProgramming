#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

#define COMM MPI_COMM_WORLD
#define N 100
#define PI acos(-1)

double f(double x) { return 4 / (1 + x * x ); }
double appPI = 0.0;

int main(void){
double PI25DT = 3.141592653589793238462643;
double pi;
MPI_Init(NULL,NULL);

int rank, size, i;
MPI_Comm_rank(COMM,&rank);
MPI_Comm_size(COMM,&size);

int chunk = N / size;
double x;
double sum = 0.0;

for (i=0; i < chunk; i++){
    x = ( rank * chunk + i ) / (double)N;
    sum += f(x);
}
sum /= N;

printf("Rank %d: %f \n", rank, sum);

appPI += sum;
//MPI_Reduce(void* send_data, void* recv_data,int count,MPI_Datatype datatype, MPI_Op op,int root,MPI_Comm communicator)

MPI_Reduce(&appPI, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,COMM);
    
	if (rank == 0)
	    printf("Pi is approximately %.16f, Error is %.16f\n", pi, fabs(pi - PI25DT));
MPI_Finalize();


}
