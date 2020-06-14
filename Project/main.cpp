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
    
    std::vector<Vector> poly_v = {Vector(0.5, 0.8, 0), Vector(0.8, 0.4, 0), Vector(0.5, 0.2, 0), Vector(0.7, 0.5, 0)} ;
    Polygon poly(poly_v) ;

    std::vector<Vector> q_v = {{Vector(0,0,0),Vector(0,1,0),Vector(1,1,0),Vector(1,0,0)}} ;
    Polygon q(q_v) ;

    save_svg_voronoi(polygon_clipping(poly, q), poly, "v_1000.svg") ;
 
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