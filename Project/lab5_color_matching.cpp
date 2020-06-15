
#include "math.h"
#include <iostream>
#include "time.h"
#include <iomanip>
#include <random>


#include "vector.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

static std::default_random_engine engine(10); 
static std::uniform_real_distribution<double> uniform(0, 1);

Vector random_dir() {
    double r1 = uniform(engine) ;
    double r2 = uniform(engine) ;
    double x = cos(2 * M_PI * r1) * sqrt(r2 * (1 - r2)) ;
    double y = sin(2 * M_PI * r1) * sqrt(r2 * (1 - r2)) ;
    double z = 1 - 2 * r2 ;
    Vector v(x, y, z) ;
    return v ;
}

void color_match(unsigned char* I, unsigned char* M, int n) {
    std::vector<std::pair<double, int>> projI(n) ;
    std::vector<std::pair<double, int>> projM(n) ;

    for (int iter = 0; iter < 2; iter++) {
        Vector v = random_dir() ;
        int c = 0 ;
        for (int i = 0; i < 3 * n; i += 3) { // looping over pixels
            auto pI = std::make_pair(dot(Vector(I[i], I[i+1], I[i+2]), v), i) ;
            projI[c] = pI ;
            auto pM = std::make_pair(dot(Vector(M[i], M[i+1], M[i+2]), v), i) ;
            projM[c] = pM ;
            c++;
        }

        sort(projI.begin(), projI.end());
        sort(projM.begin(), projM.end());

        for (int i = 0; i < n; i++) {
            Vector pc = (projM[i].first - projI[i].first) * v ;
            I[projI[i].second]     += pc[0] ;
            I[projI[i].second + 1] += pc[1] ;
            I[projI[i].second + 2] += pc[2] ;
        }
    }
}