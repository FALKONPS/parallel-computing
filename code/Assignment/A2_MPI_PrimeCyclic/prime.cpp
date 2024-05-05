#include <iostream>
#include <cmath>
#include <sys/time.h>

using namespace std;


int isprime(unsigned long int n){
    for (int i = 2; i <= int(sqrt(n)); i++)
    {
       if(n%i==0)
       {
        return 0;
       }
    }
    return 1;
}

void primenum(unsigned long int _N){
    for (int n = 2; n < _N;n++)
    {
        if(isprime(n)){
            cout<<n<<" ";
        }
    }
}
int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    int begin;
    int n;
    n=stoul(argv[1]);
    primenum(n);
}
