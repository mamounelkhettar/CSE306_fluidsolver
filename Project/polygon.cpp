#include "polygon.h"



Vector intersect(Vector prevVertex, Vector curVertex, Polygon clipPolygon, int i) {
    Vector c1 = clipPolygon.v[i] ; 
    Vector c2 = clipPolygon.v[(i>0)?(i-1):clipPolygon.v.size()-1] ; 
    Vector N = Vector(c2[1] - c1[1], c1[0]-c2[0], 0) ;
    double t = dot((c1-prevVertex), N) / dot((curVertex-prevVertex), N) ;
    if (t < 0 || t>1){
        std::cout << "T IS WRONG?" << std::endl;
    }
    P = prevVertex + t*(curVertex - prevVertex);
    return P;
}

Polygon polygon_clipping(Polygon subjectPolygon, Polygon clipPolygon) {

    for(std::vector<Vector>::size_type i = 0; i != clipPolygon.v.size(); i++) {
        Polygon outPolygon() ;

        for(std::vector<Vector>::size_type i = 0; i != subjectPolygon.v.size(); i++) {
            Vector curVertex = subjectPolygon.v[i] ;
            Vector prevVertex = subjectPolygon.v[(i>0)?(i-1):subjectPolygon.v.size()-1] ; 
            Vector intersection = intersect(prevVertex, curVertex, clipPolygon, i) ;
        }
    }

}