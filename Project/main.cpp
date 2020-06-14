#include "math.h"
#include <iostream>
#include "time.h"
#include <iomanip>

#include "polygon.h"

using namespace std ; 

int main(int argc, char *argv[]) {
   
    // time check start
    clock_t start, end; 
    start = clock(); 
    
    
    // time check end and print
    end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC ; 
    std::cout << "Image generated in : " << fixed << time_taken << setprecision(10) ; 
    std::cout << " sec " << endl ; 

    return 0;
}

//clang-Xpreprocessor -fopenmp -lomp main.cpp scene.cpp sphere.cpp -o main.exe
//g++ -fopenmp -O3 main.cpp scene.cpp sphere.cpp -o main

//clang++ -Xpreprocessor -fopenmp main.cpp scene.cpp sphere.cpp -o main -lomp 