#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rank=0;
    int size=0;
    int len=0;
    char name[300]="";
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(name, &len);
    //hello world from process 0 / 2
    cout << "hello world from process " <<rank<<" / "<< size<<endl;
    MPI_Finalize();
return 0;
}
