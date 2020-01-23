////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This file contains:
// Polygon class
// Triangle class
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "glutWindow.h"

#include "geometry.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Polygon::Polygon()
    : n_edges(0)
{
    vertices = std::vector<Vector2D>();
}

Polygon::Polygon(const std::vector<Vector2D> &vertices_) {
    for (auto vertex : vertices_) {
        vertices.push_back(vertex);
    }
    n_edges = vertices.size();

}

Polygon::~Polygon() {
    vertices.clear();
}

void Polygon::onDraw() {

    // Draw the interior of the polygon.
    glColor3ub(255, 255, 0);

    glBegin(GL_POLYGON);
    for (auto vertex : vertices) {
        glVertex2f(vertex.x, vertex.y);
    }
    glEnd();

    // Draw the borders of the polygon.
    glColor3b(0, 0, 255);

    glBegin(GL_LINE_LOOP);
    for (auto vertex : vertices) {
        glVertex2f(vertex.x, vertex.y);
    }
    glEnd();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
