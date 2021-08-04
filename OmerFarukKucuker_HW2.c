#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define TAG 777
#define COMM MPI_COMM_WORLD

int myReduce(int *array, int size, int rank, MPI_Status *stat)
{
    int sum = 0;
    sum += array[rank];
    for (int i = 1; i < size; i *= 2) // 2 nin kuvveti kadar size olduğundan 2^n n tane seviye olucak
    {
        for (int j = 0; j < size; j = j + 2 * i) // her seviyede gidilecek adım sayısı 2-4-8 şeklinde
        {
            if (rank == j) //ikilinin solundaki recieve yapıyor
            {
                
                MPI_Recv(&array[rank], 1, MPI_INT, rank + i, TAG + rank + i, COMM, stat);
                sum += array[rank]; //aldığını arrayin kendi indeksine ekliyor
                array[rank] = sum;
            }
            else if (rank == j + i)
            {
                MPI_Send(&array[rank], 1, MPI_INT, rank - i, TAG + rank, COMM);
            }
            
        }
    }
    return sum;
}

void printArray(int *a, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    puts("");
}

int main(void)
{

    MPI_Init(NULL, NULL);

    double startTime = MPI_Wtime();

    int rank, size, i;

    MPI_Comm_rank(COMM, &rank);
    MPI_Comm_size(COMM, &size);

    MPI_Status *stat;
    MPI_Request request;
    

    //int *array;
    int *array = (int *)malloc(size * sizeof(int));

    for (i = 0; i < size; i++)
    {
        array[i] = i;
    }

    //myReduce kısmı

    // 1. seviye 0-1 2-3 4-5 6-7
    // 2. seviye 0-2 4-6
    // 3. seviye 0-4  // sonuç Master'ın 0. elemanında ve sum değişkeninde tutuluyor.

    
    //int result = myReduce(array, size, rank, stat); // hata verdiği için functionlı kısımda yapmadım

    int sum = 0;
    sum += array[rank];
    for (int i = 1; i < size; i *= 2) // 2 nin kuvveti kadar size olduğundan 2^n n tane seviye olucak
    {
        for (int j = 0; j < size; j = j + 2 * i) // her seviyede gidilecek adım sayısı 2-4-8 şeklinde
        {
            if (rank == j) //ikilinin solundaki recieve yapıyor
            {
                
                MPI_Recv(&array[rank], 1, MPI_INT, rank + i, TAG + rank + i, COMM, stat);
                sum += array[rank]; //aldığını arrayin kendi indeksine ekliyor
                array[rank] = sum;
            }
            else if (rank == j + i)
            {
                MPI_Send(&array[rank], 1, MPI_INT, rank - i, TAG + rank, COMM);
            }
            
        }
    }
  
    double finishTime = MPI_Wtime();
    if (MASTER == rank)
    {
        //printArray(array, size);
         //myreduce functiondan sonra MPI_Wtime yazınca hata veriyor. MPI_Reduce'de hata vermedi.
        printf("Result: %d %f sn. \n",sum, finishTime-startTime);
    } 

    //MPI_Reduce kısmı

    /*int sumReduce = array[rank];
    int globalSum=0;
    MPI_Reduce(&sumReduce, &globalSum, 1, MPI_INT, MPI_SUM, MASTER,COMM);
    double finishTime = MPI_Wtime();
     if (MASTER == rank)
    {
        //printArray(array, size);
        
        printf("Result2: %d  %f sn.\n",globalSum, finishTime-startTime);
    }*/

    MPI_Finalize();
}
