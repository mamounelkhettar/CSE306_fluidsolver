#include "math.h"
#include <iostream>
#include "time.h"
#include <iomanip>
#include <random>

#include "polygon.h"

using namespace std ; 

static std::default_random_engine engine(time(0)) ; 
static std::uniform_real_distribution<double> uniform(0, 1) ;

int main(int argc, char *argv[]) {
   
    // time check start
    clock_t start, end; 
    start = clock(); 
    
    // TD5 color matching : td5_color_matching.cpp

    // Project
    std::vector<Vector> poly_v ;
    std::vector<double>  radius ;
    double x, y ;
    for (int i = 0; i < 1000; i++) {
        x = uniform(engine) ;
        y = uniform(engine) ;
        poly_v.push_back(Vector(x, y, 0)) ;
        radius.push_back(uniform(engine)) ;
    }

    Polygon poly(poly_v, radius) ;

    std::vector<Vector> q_v = {{Vector(0,0,0),Vector(0,1,0),Vector(1,1,0),Vector(1,0,0)}} ;
    Polygon q(q_v) ;

    save_svg_voronoi(polygon_clipping(poly, q), poly, "v_test.svg") ;
 
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