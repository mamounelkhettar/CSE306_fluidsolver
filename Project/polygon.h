#include "math.h"
#include <iostream>
#include "time.h"
#include <iomanip>
#include <string>
#include <cstdio>
#include "vector"

#include "vector.h"

class Polygon {  
public:
    std::vector<Vector> vertices ;

    Polygon() {} ;

    Polygon(std::vector<Vector> vertices){
        this->vertices = vertices;
    }
};  

Vector intersect(Vector prevVertex, Vector curVertex, Polygon clipPolygon, int i, int j) ;
bool inside(Vector P, Polygon clipPolygon, int i, int j) ;
std::vector<Polygon> polygon_clipping(Polygon poly, Polygon q) ;

// saves a static svg file. The polygon vertices are supposed to be in the range [0..1], and a canvas of size 1000x1000 is created
void save_svg(const std::vector<Polygon> &polygons, std::string filename, std::string fillcol = "none") ;
void save_svg_voronoi(const std::vector<Polygon> &polygons, const Polygon &vectors, std::string filename, std::string fillcol = "none") ;

// Adds one frame of an animated svg file. frameid is the frame number (between 0 and nbframes-1).
// polygons is a list of polygons, describing the current frame.
// The polygon vertices are supposed to be in the range [0..1], and a canvas of size 1000x1000 is created
void save_svg_animated(const std::vector<Polygon> &polygons, std::string filename, int frameid, int nbframes) ;