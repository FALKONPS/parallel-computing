#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
using namespace std;
// time

int image_y = 0;
int image_x = 0;

int kernel_y = 0;
int kernel_x = 0;
// mutex and Sync
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int flag_Sync;

// data share
static int MAX_THREAD = 32;
long thread_size;
// data heap share
vector<double> *_image;
vector<double> *_kernel;
ofstream output_file;

// One byte for each of the RPG colors (red, blue, and green)
// grayscale 1 byte 256 max value
int currentThread = 0;
sem_t semaphore;

void *Convolution(void *);
timespec diff(timespec start, timespec end)
{
    timespec temp;

    if ((end.tv_nsec - start.tv_nsec) < 0)
    {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else
    {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}
void *Convolution(void *rank)
{
    struct timespec begin, end;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &begin);
    long my_rank = (long)rank;

    // dis
    int data = ((image_x * image_y) / thread_size);
    int start = my_rank * data;
    int stop = my_rank * data + data;
    vector<double> buffer;
    // multpulcation
    for (int i = start; i < stop; i++)
    {
        double sum = 0;
        // Filter
        int loc_image = 0;
        int loc_kernel = 0;
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                loc_image = ((j * image_x) + i + k) % _image->size();
                loc_kernel = (3 * j) + k;
                sum += _image->at(loc_image) * _kernel->at(loc_kernel);
            }
        }
        int int_sum = (int)sum;
        buffer.push_back(int_sum);

        clock_gettime(CLOCK_MONOTONIC, &end);
        //
    }
    cout << "Rank " << my_rank << " Start " << start << "\\" << stop << " Time " << diff(begin, end).tv_nsec * 1e-6 << "ms" << endl;
    // cout << diff(begin, end).tv_nsec * 1e-6 << endl;
    // while (flag_Sync != my_rank)
    //     ;
    // pthread_mutex_lock(&mutex);
    sem_wait(&semaphore);
    while (my_rank != currentThread)
    {
        sem_post(&semaphore);
        sem_wait(&semaphore);
    }
    for (long i = 0; i < data; i++)
    {
        int value = (int)buffer[i];
        output_file << buffer[i] << " ";
        if ((start + i) % image_x == 0) // new line
        {
            output_file << endl;
        }
    }
    currentThread = (currentThread + 1) % thread_size;
    sem_post(&semaphore);
    // pthread_mutex_unlock(&mutex);
    //
    return NULL;
}

vector<double> *ImageToVecotr(string pathName)
{
    vector<double> *vecotrIamge;
    vecotrIamge = new vector<double>;
    string buffer;
    ifstream textImage(pathName);

    textImage >> buffer; // ignore x and y
    textImage >> buffer;
    int i = 0;
    while (textImage)
    {
        if (textImage.is_open())
        {

            textImage >> buffer;
            vecotrIamge->push_back(stod(buffer));
        }
    }
    textImage.close();
    return vecotrIamge;
}

int main(int argc, char *argv[])
{
    sem_init(&semaphore, 0, 1); // Initial value of semaphore is set to 1

    pthread_t threads[MAX_THREAD] = {0};
    ;
    void *return_addrs[MAX_THREAD];
    vector<double> *_output;
    // Check if there are three command line arguments
    if (argc != 5)
    {
        cerr << argv[0] << " iamgeFile kernelFile outputFile" << endl;
        return 1;
    }
    string imageFileName = argv[1];
    string kernelFileName = argv[2];
    string outputFileName = argv[3];
    cout << "image File Name  :" << imageFileName << endl;
    cout << "kernel File Name :" << kernelFileName << endl;
    cout << "output File Name :" << outputFileName << endl;
    output_file.open(outputFileName);
    thread_size = stoul(argv[4]);
    flag_Sync = 0;
    cout << "Number of Thread :" << thread_size << endl;
    long input_thread;

    _image = ImageToVecotr(imageFileName);
    _kernel = ImageToVecotr(kernelFileName);
    // open file image
    ifstream I(imageFileName);

    I >> image_y; // ignore x and y
    I >> image_x;
    I.close();
    //
    ifstream K(imageFileName);

    K >> kernel_y; // ignore x and y
    K >> kernel_x;
    K.close();

    //

    output_file << image_y << " ";
    output_file << image_x << " ";
    output_file << endl;
    for (long rank = 0; rank < thread_size; rank++)
    {
        int status = pthread_create(&threads[rank], NULL, &Convolution, (void *)rank);

        if (status)
        {
            std::cerr << "Error creating thread; return code from pthread_create() is " << endl;
            return -1;
        }
    }

    // addrs=Convolution((void*)5);
    // _output=(vector<double>*)addrs;
    for (long t = 0; t < thread_size; t++)
    {
        pthread_join(threads[t], NULL);
    }
    cout << "Clean and Free Data\n";
    // Free Data
    output_file.close();
    delete _image;
    delete _kernel;
    pthread_mutex_destroy(&mutex);
    cout << "Job Done :D\n";

    return 0;
}
