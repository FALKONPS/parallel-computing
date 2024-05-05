#include <iostream>
#include <cmath>
#include <sys/time.h>
#include <mpi.h>

using namespace std;
int isprime(unsigned long long int n){
    for (unsigned long long int i = 2; i <= int(sqrt(n)); i++)
    {
       if(n%i==0)
       {
        return 0;
       }
    }
    return 1;
}
int main(int argc, char **argv) {
    double t1, t2; 
    if (argc != 2) {
        MPI_Finalize();
        return 1;
    }
    MPI_Init(&argc, &argv);
    int rank;
    int size;
    MPI_Status status;
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned long long int begin=3;
    unsigned long long int stop;
    stop=stoul(argv[1]);

    int block_test=stop/size;

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            int b=(i*block_test);
            int s=(i*block_test+block_test);
            MPI_Send(&b, 1, MPI_LONG_LONG_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&s, 1, MPI_LONG_LONG_INT, i, 0, MPI_COMM_WORLD);//start 
        }
        begin=3;
        stop=block_test;
    } else {
        MPI_Recv(&begin, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&stop, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);//End 
    }
    t1 = MPI_Wtime(); 

    cout<<"process "<<rank<<": ";
    while (begin < stop)
    {
        if(isprime(begin))
        {
            cout<<begin<<" ";
        }
        begin++;

    }
    t2 = MPI_Wtime(); 

    MPI_Finalize();
    cout << " time = " << t2 - t1 << endl;

}