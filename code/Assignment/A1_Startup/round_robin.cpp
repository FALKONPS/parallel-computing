#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rank;
    int size;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int value = 0;
    //If the process is zero (rank == 0 ), then send to process one 0+1=1 ;) the input value.
    if (rank == 0) {
        cout << "User Input ";
        cin >> value;
        MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        //wait the final result
        MPI_Recv(&value, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, &status);
        cout << "Final Result: " << value << " From Process "<<rank<<endl;

    } else {
        //Each process (rank) receives value from the previous process (rank-1) and sends it to the next process (rank+1).
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);

        if (rank % 2 == 0) {
            value = value * 3;
        } else {
            value = value * 2;
        }
        //note if the rank become as same as size that mean we at last proccess and most send the result to proccess zero
        MPI_Send(&value, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

    }

    MPI_Finalize();
    return 0;
}
