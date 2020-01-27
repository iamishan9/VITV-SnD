#ifndef SERVERS_AND_DRONES_GEOMETRIC_ALGORITHMS_H
#define SERVERS_AND_DRONES_GEOMETRIC_ALGORITHMS_H

#include <algorithm>

#include "vector2d.h"
#include "geometry.h"


std::vector<Vector2D> graham(const std::vector<Vector2D> &points);
void delaunay(Mesh *mesh);
std::vector<Polygon> voronoi(const Mesh &delaunay_mesh);

bool is_left_turn(const Vector2D *p, const Vector2D *p1, const Vector2D *p2);
bool polar_comparison(Vector2D p1, Vector2D p2);



#endif //SERVERS_AND_DRONES_GEOMETRIC_ALGORITHMS_H
