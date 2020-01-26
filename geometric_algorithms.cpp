////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This file contains:
// Graham
// Delaunay
// Voronoi
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <iostream>
#include <list>
#include <stack>
#include <vector>



#include "geometric_algorithms.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool is_left_turn(const Vector2D *p, const Vector2D *p1, const Vector2D *p2) {
    Vector2D AB = *p2 - *p1,
            AP = *p - *p1;

    return (AB.x * AP.y - AB.y * AP.x)>=0;
}

bool polar_comparison(Vector2D p1, Vector2D p2) {
    double a1 = asin(p1.y / sqrt(p1.x * p1.x + p1.y * p1.y));
    if (p1.x < 0.0)
        a1 = M_PI - a1;

    double a2 = asin(p2.y / sqrt(p2.x * p2.x + p2.y * p2.y));
    if (p2.x < 0.0)
        a2 = M_PI - a2;

    return a1 < a2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<Vector2D> graham(const std::vector<Vector2D> &points_) {
    std::vector<Vector2D> points;
    points.reserve(points_.size());
    for (const auto& point : points_) {
        points.push_back(point);
    }

    if (points_.size() < 4) {
        return points;
    }

    std::vector<Vector2D> result;

    float y_min = points[0].y;
    float y;
    int min = 0, i = 0;
    for (const auto& point : points) {
        y = point.y;
        if ((y < y_min) || (y_min == y && point.x < point.x)) {
            y_min = point.y;
            min = i;
        }
        i++;
    }

    std::swap(points[0], points[min]);

    Vector2D origin(points[0]);

    std::vector<Vector2D> points_relative;
    points_relative.reserve(points.size());
    for (auto &point : points) {
        points_relative.emplace_back(point.x - origin.x, point.y - origin.y );
    }

    sort(points_relative.begin()+1, points_relative.end(), polar_comparison);

    std::stack<Vector2D*> stack;
    Vector2D *top_1, *top;
    stack.push(&points_relative[0]);
    stack.push(&points_relative[1]);
    stack.push(&points_relative[2]);

    auto p_it = points_relative.begin() + 3;

    while (p_it != points_relative.end()) {
        top = stack.top();
        stack.pop();
        top_1 = stack.top();
        stack.push(top);
        while ( !is_left_turn( &(*p_it), top_1, top ) ) {
            stack.pop();
            top = stack.top();
            stack.pop();
            top_1 = stack.top();
            stack.push(top);
        }
        stack.push(&(*p_it));
        p_it++;
    }

    while (!stack.empty()) {
        result.insert(result.begin(), *(stack.top()) + origin);
        //result.push_back(*(stack.top()) + origin);
        stack.pop();
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void delaunay(Mesh *mesh) {

    std::list<Triangle*> processList;
    for (auto &triangle : mesh->triangles) {
        processList.push_back(&triangle);
    }

    while (processList.size()>1) { // while a triangle is in the list
        Triangle *current = processList.front(); // pop current
        processList.pop_front();
        if (!current->isDelaunay) { // if current is not Delaunay
            Triangle *Tneighbor = mesh->neighborInside(current);
            if (Tneighbor != nullptr) { // and if a neighbor is available
                mesh->flip(current, Tneighbor); // flip the common edge
                // remove Tneighbor form the list
                auto tr=processList.begin();
                while (tr != processList.end() && (*tr) != Tneighbor) tr++;
                if (tr!=processList.end()) processList.erase(tr);
            } else {
                processList.push_back(current); // postpone the treatment
            }
        }
    }
    if (! mesh->checkDelaunay()) {
        delaunay(mesh);
    }
}

