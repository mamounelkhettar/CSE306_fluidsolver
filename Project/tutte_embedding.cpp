
#include "math.h"
#include <iostream>
#include "time.h"
#include <iomanip>
#include <random>


#include "vector.h"


std::vector<Vector> tutte_embedding(std::vector<int> b, std::vector<Vector> v) {
    int n = v.size() ;
    int M = b.size() ;
    double cs = 0 ;
    double s = 0 ;
    std::vector<Vector> v0 = v ;
    std::vector<Vector> v1 = v ;

    for(int i = 0; i < M; i ++) {
        s += norm((v[b[(i + 1)]] - v[b[i]])) ;
        double t = 2 * M_PI * cs / s ;
        v0[b[i]] = Vector(cos(t), sin(t)) ;
        cs += norm((v[b[(i + 1)]] - v[b[i]])) ;
    }

    for(int t = 0; t < 200; t ++) {
        for(int i = 0; i < 200; i ++) {
        }
    }
    return v0 ;
}

