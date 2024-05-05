#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>

using namespace std;
static int OFFSET = 2; // X and Y
// One byte for each of the RPG colors (red, blue, and green)
// grayscale 1 byte 256 max value

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

vector<double> *Convolution(vector<double> *image, vector<double> *_kernel, string output_name)
{
    struct timespec begin, end;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &begin);

    std::ofstream _output(output_name);

    vector<double> *output = new vector<double>();
    int image_x = image->at(1);
    int image_y = image->at(0);

    _output << image_x << " ";
    _output << image_y << " ";
    int orgin = 0;
    //
    //
    // multpulcation
    int scoutss = 0;
    for (int i = OFFSET; i < image->size(); i++)
    {
        double sum = 0;
        // Filter
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                int loc = (OFFSET + (j * image_x) + i + k) % image->size();
                sum += image->at(loc) * _kernel->at(OFFSET + (3 * j) + k);
            }
        }

        if (i % image_x == 0) // new line
        {
            _output << endl;
        }
        int int_sum = (int)sum;
        _output << int_sum << " ";
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    //
    cout << " Time " << diff(begin, end).tv_nsec * 1e-6 << "ms" << endl;

    return output;
}

vector<double> *ImageToVecotr(string pathName)
{
    vector<double> *vecotrIamge;
    vecotrIamge = new vector<double>;
    string buffer;
    ifstream textImage(pathName);
    int i = 0;
    while (textImage)
    {
        if (textImage.is_open())
        {

            textImage >> buffer;
            vecotrIamge->push_back(std::stod(buffer));
        }
    }
    return vecotrIamge;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cerr << argv[0] << " iamgeFile kernelFile outputFile" << endl;
        return 1;
    }
    string iamgeFileName = argv[1];
    string kernelFileName = argv[2];
    string outputFileName = argv[3];

    vector<double> *pVIamge;
    vector<double> *pVKernel;
    vector<double> *output;
    pVIamge = ImageToVecotr(iamgeFileName);
    pVKernel = ImageToVecotr(kernelFileName);
    int x = pVIamge->at(0);
    int y = pVIamge->at(1);
    cout << "X :" << x << endl;
    cout << "Y :" << y << endl;
    output = Convolution(pVIamge, pVKernel, outputFileName);
    return 0;
}
