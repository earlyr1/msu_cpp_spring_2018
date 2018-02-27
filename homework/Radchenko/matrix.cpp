
#include <chrono>
#include <iostream>
#include <fstream>

using namespace std;

const int SIZE = 10000;
const int N_LAUNCHES = 5;

class Timer
{
public:
    Timer()
        : start_(std::chrono::high_resolution_clock::now())
    {
    }

    ~Timer()
    {
        const auto finish = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() / (N_LAUNCHES + 0.0) << " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};

int main(int argc, char const *argv[])
{
    int **arr;
    arr = new int*[SIZE];
    volatile int sum = 0;
    for(int i = 0; i < SIZE; i++) {
        arr[i] = new int[SIZE];
        for(int j = 0; j < SIZE; j++) {
            arr[i][j] = ++sum;
        }
    }

    {	
    	Timer timer;
	    for(int i = 0; i < N_LAUNCHES; i++) {
		    sum = 0;
		    for(int i = 0; i < SIZE; i++) {
		        for(int j = 0; j < SIZE; j++) {
		            sum += arr[i][j];
		        }
		    }
		}
	}

	{	
		Timer timer;
		for(int i = 0; i < N_LAUNCHES; i++){
		    sum = 0;
		    for(int i = 0; i < SIZE; i++) {
		        for(int j = 0; j < SIZE; j++) {
		            sum += arr[j][i];
		        }
		    }
		}
	}
	for(int i = 0; i < SIZE; i++) {
        delete [] arr[i];
    }
    delete [] arr;
}

 