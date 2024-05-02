#include <iostream>
#include <mpi.h>

using namespace std;
int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rank;
    int size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char data[20]="i am data zero";
    if(rank == 0)
    {
        MPI_Send(&data,20,MPI_CHAR,1,0,MPI_COMM_WORLD);
        MPI_Recv(&data,20,MPI_CHAR,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        cout<<"Process "<<rank<<" "<<data<<endl;
    }
    else{
        char data[20]="i am data one";
        MPI_Send(&data,20,MPI_CHAR,0,0,MPI_COMM_WORLD);
        MPI_Recv(&data,20,MPI_CHAR,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        cout<<"Process "<<rank<<" "<<data<<endl;
    }
    
    MPI_Finalize();
}