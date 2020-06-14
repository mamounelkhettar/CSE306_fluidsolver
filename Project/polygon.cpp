#include "polygon.h"

Vector intersect(Vector prevVertex, Vector curVertex, Polygon clipPolygon, int i, int j) {
    Vector c1 = clipPolygon.vertices[i] ; 
    Vector c2 = clipPolygon.vertices[j] ; 
    Vector N = (c1 + c2) / 2 ;
    double t = dot((N - prevVertex), (c1 - c2)) / dot((curVertex - prevVertex), (c1 - c2)) ;
    Vector P = prevVertex + t * (curVertex - prevVertex) ;
    return P ;
}

bool inside(Vector P, Polygon clipPolygon, int i, int j) {
    Vector c1 = clipPolygon.vertices[i] ; 
    Vector c2 = clipPolygon.vertices[j] ; 
    Vector N = (c1 + c2) / 2 ;

    double t = dot((P - N), (c2 - c1)) ;
    if (t > 0) { return false ; }
    return true ;
}

std::vector<Polygon> polygon_clipping(Polygon poly, Polygon q) {
    std::vector<Polygon> Voronoi ; 

    for(std::vector<Vector>::size_type i = 0; i != poly.vertices.size(); i++) {
        Polygon subjectPolygon =  q ;
        for(std::vector<Vector>::size_type j = 0; j != poly.vertices.size(); j++) {
            if ( i != j ) {
                Polygon outPolygon ;
                for(std::vector<Vector>::size_type k = 0; k != subjectPolygon.vertices.size(); k++) {
                    Vector curVertex = subjectPolygon.vertices[k] ;
                    Vector prevVertex = subjectPolygon.vertices[(k>0)?(k-1):subjectPolygon.vertices.size()-1] ; 
                    Vector intersection = intersect(prevVertex, curVertex, poly, i, j) ;

                    if (inside(curVertex, poly, i, j)) {
                        if (!inside(prevVertex, poly, i, j)) {
                            outPolygon.vertices.push_back(intersection) ;
                        }
                        outPolygon.vertices.push_back(curVertex);
                    } else if (inside(prevVertex, poly, i, j)) {
                        outPolygon.vertices.push_back(intersection) ;
                    }
                }
                subjectPolygon = outPolygon ;
            }
        }
        Voronoi.push_back(subjectPolygon) ;
    }
    return Voronoi ; 
}


// saves a static svg file. The polygon vertices are supposed to be in the range [0..1], and a canvas of size 1000x1000 is created
void save_svg(const std::vector<Polygon> &polygons, std::string filename, std::string fillcol ) {
    FILE* f = fopen(filename.c_str(), "w+");
    fprintf(f, "<svg xmlns = \"http://www.w3.org/2000/svg\" width = \"1000\" height = \"1000\">\n");
    for (int i=0; i<polygons.size(); i++) {
        fprintf(f, "<g>\n");
        fprintf(f, "<polygon points = \"");
        for (int j = 0; j < polygons[i].vertices.size(); j++) {
            fprintf(f, "%3.3f, %3.3f ", (polygons[i].vertices[j][0] * 1000), (1000 - polygons[i].vertices[j][1] * 1000));
        }
        fprintf(f, "\"\nfill = \"%s\" stroke = \"black\"/>\n", fillcol.c_str());
        fprintf(f, "</g>\n");
    }
    fprintf(f, "</svg>\n");
    fclose(f);
}
 
 
// Adds one frame of an animated svg file. frameid is the frame number (between 0 and nbframes-1).
// polygons is a list of polygons, describing the current frame.
// The polygon vertices are supposed to be in the range [0..1], and a canvas of size 1000x1000 is created
void save_svg_animated(const std::vector<Polygon> &polygons, std::string filename, int frameid, int nbframes) {
    FILE* f;
    if (frameid == 0) {
        f = fopen(filename.c_str(), "w+");
        fprintf(f, "<svg xmlns = \"http://www.w3.org/2000/svg\" width = \"1000\" height = \"1000\">\n");
        fprintf(f, "<g>\n");
    } else {
        f = fopen(filename.c_str(), "a+");
    }
    fprintf(f, "<g>\n");
    for (int i = 0; i < polygons.size(); i++) {
        fprintf(f, "<polygon points = \"");
        for (int j = 0; j < polygons[i].vertices.size(); j++) {
            fprintf(f, "%3.3f, %3.3f ", (polygons[i].vertices[j][0] * 1000), (1000-polygons[i].vertices[j][1] * 1000));
        }
        fprintf(f, "\"\nfill = \"none\" stroke = \"black\"/>\n");
    }
    fprintf(f, "<animate\n");
    fprintf(f, "    id = \"frame%u\"\n", frameid);
    fprintf(f, "    attributeName = \"display\"\n");
    fprintf(f, "    values = \"");
    for (int j = 0; j < nbframes; j++) {
        if (frameid == j) {
            fprintf(f, "inline");
        } else {
            fprintf(f, "none");
        }
        fprintf(f, ";");
    }
    fprintf(f, "none\"\n    keyTimes = \"");
    for (int j = 0; j < nbframes; j++) {
        fprintf(f, "%2.3f", j / (double)(nbframes));
        fprintf(f, ";");
    }
    fprintf(f, "1\"\n   dur = \"5s\"\n");
    fprintf(f, "    begin = \"0s\"\n");
    fprintf(f, "    repeatCount = \"indefinite\"/>\n");
    fprintf(f, "</g>\n");
    if (frameid == nbframes - 1) {
        fprintf(f, "</g>\n");
        fprintf(f, "</svg>\n");
    }
    fclose(f);
}

void save_svg_voronoi(const std::vector<Polygon> &polygons, const Polygon &vectors, std::string filename, std::string fillcol ) {
    FILE* f = fopen(filename.c_str(), "w+");
    fprintf(f, "<svg xmlns = \"http://www.w3.org/2000/svg\" width = \"1000\" height = \"1000\">\n");
    
    for (int i=0; i<vectors.vertices.size(); i++){
        fprintf(f, "<g>\n");
        fprintf(f, "<circle cx = \"%3.3f\" cy = \"%3.3f\" r=\"5\"/>", vectors.vertices[i][0] * 1000, 1000 - vectors.vertices[i][1] * 1000);
        fprintf(f, "</g>\n");
    }

    for (int i=0; i<polygons.size(); i++) {
        //std::cout << polygons[i].vertices.size() ;
        fprintf(f, "<g>\n");
        fprintf(f, "<polygon points = \"");
        for (int j = 0; j < polygons[i].vertices.size(); j++) {
            fprintf(f, "%3.3f, %3.3f ", (polygons[i].vertices[j][0] * 1000), (1000 - polygons[i].vertices[j][1] * 1000));
        }
        fprintf(f, "\"\nfill = \"%s\" stroke = \"black\"/>\n", fillcol.c_str());
        fprintf(f, "</g>\n");
    }

    fprintf(f, "</svg>\n");
    fclose(f);
}
