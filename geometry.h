#ifndef SERVERS_AND_DRONES_GEOMETRY_H
#define SERVERS_AND_DRONES_GEOMETRY_H


#include <vector>

#include "vector2d.h"

class Polygon {
public:
    int n_edges;
    std::vector<Vector2D> vertices;

    Polygon();
    Polygon(const std::vector<Vector2D> &vertices);
    ~Polygon();

    void onDraw();
};

class Triangle {

};

/*
class Vector2D {

};
*/

#endif //SERVERS_AND_DRONES_GEOMETRY_H
