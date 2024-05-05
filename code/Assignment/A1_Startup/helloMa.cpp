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
    //Add code, so that processes with even rank say hello from rank, while processes with odd ranks
    //say hi from rank. Like, 
    if(rank==0)
    {
        cout << "hello from " <<rank<<" out of "<<size<<" ["<< name <<"]"<<endl;
        
    }

    else if(rank%2==0)
    {
        cout << "hello world from " <<rank<<" out of "<<size<<" ["<< name <<"]"<<endl;
    }

    else if(rank%2==1)
    {
        cout << "hi from " <<rank<<" out of "<<size<<" ["<< name <<"]"<<endl;
    }
    MPI_Finalize();
return 0;
}
