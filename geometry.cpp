////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This file contains:
// Matrix class -> determinant calculus
// Mesh class
// Polygon class
// Triangle class
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "glutWindow.h"

#include "geometry.h"
#include "color.h"
#include "geometric_algorithms.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Matrix22::get2x2From3x3(const Matrix33 &mat33,int shadowLin, int shadowCol) {
    int l=0;
    for (int lig=0; lig<3; lig++) {
        if (lig!=shadowLin) {
            int c=0;
            for (int col=0; col<3; col++) {
                if (col!=shadowCol) {
                    m[l][c] = mat33.m[lig][col];
                    c++;
                }
            }
            l++;
        }
    }
}

void Matrix33::get3x3From4x4(const Matrix44 &mat44,int shadowLin, int shadowCol) {
    int l=0;
    for (int lig=0; lig<4; lig++) {
        if (lig!=shadowLin) {
            int c=0;
            for (int col=0; col<4; col++) {
                if (col!=shadowCol) {
                    m[l][c] = mat44.m[lig][col];
                    c++;
                }
            }
            l++;
        }
    }
}

float Matrix33::determinant() {
    Matrix22 mat22;
    float det=0;

    float sign=1;
    for (int i=0; i<3; i++) {
        mat22.get2x2From3x3(*this,i,0);
        det += sign*m[i][0]*mat22.determinant();
        sign = -sign;
    }
    return det;
}


float  Matrix44::determinant() {
    Matrix33 mat33;
    float det=0;

    float sign=1;
    for (int i=0; i<4; i++) {
        mat33.get3x3From4x4(*this,i,0);
        det += sign*m[i][0]*mat33.determinant();
        sign = -sign;
    }
    return det;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Mesh::Mesh() {
    vertices = std::vector<Vector2D>();
    triangles = std::vector<Triangle>();
}

Mesh::Mesh(const std::vector<Vector2D> &points) {
    for (auto point : points) {
        vertices.push_back(point);
    }
    Polygon convex_hull(graham(points));
    triangles = convex_hull.triangulation();
}

void Mesh::add_triangle(const Triangle &triangle) {
    triangles.push_back(triangle);
}

Mesh::~Mesh() {
    vertices.clear();
    triangles.clear();
}

void Mesh::onDraw() {
    for (auto triangle : triangles) {
        triangle.onDraw();
    }
}

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

std::vector<Triangle> Polygon::triangulation() {
    std::vector<Triangle> triangles;
    std::vector<Vector2D*> tmp;

//    for (int i = 0; i < n_edges; i++) {
//        //tmp.push_back(&(tab_pts_[i]));
//    }

    for (auto vertex : vertices) {
        tmp.push_back(&vertex);
    }

    int n = n_edges;

    while (n > 2) {
        int i = 0;
        auto p = tmp.begin();
        bool test;

        Triangle T(*p, *(p + 1), *(p + 2));

        do {
            test = !T.isEmpty(tmp, i + 3);
            if (test) {
                i++;
                p++;
                T = Triangle(*p, *(p + 1), *(p + 2));
            }
        } while (i < n - 2 && test);

        assert(i < n - 2);

        //arr_triangle_.push_back(T);
        triangles.push_back(T);
        tmp.erase(p + 1); // remove point(p + 1) from tmp.
        n--; // or n = tmp.size().
    }
    return triangles;
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

Triangle::Triangle(Vector2D *ptr1,Vector2D *ptr2,Vector2D *ptr3) {
    ptr[0] = ptr1;
    ptr[1] = ptr2;
    ptr[2] = ptr3;
    isHighlighted = false;
    calculateCircle();

}

void Triangle::updateVertices(Vector2D *ptr1,Vector2D *ptr2,Vector2D *ptr3) {
    ptr[0] = ptr1;
    ptr[1] = ptr2;
    ptr[2] = ptr3;
    isHighlighted = false;
    calculateCircle();
}

void Triangle::calculateCircle() {
    Vector2D AB = *ptr[1] - *ptr[0];
    Vector2D AC = *ptr[2] - *ptr[0];

    Vector2D VAC = AC.ortho();
    float AB2 = AB * AB;
    float k = (AB2 - AC*AB) / (2*(VAC*AB));

    circumCenter = 0.5f * AC + k * VAC + *ptr[0] ; // O
    circumRadius = (circumCenter - *ptr[0]).norm(); // R
}

void Triangle::onMouseMove(const Vector2D& pos) {
    isHighlighted = isInside(pos);
}

bool Triangle::isOnTheLeft(const Vector2D *P, const Vector2D *P1, const Vector2D *P2) {
    Vector2D AB = *P2-*P1,
            AP = *P-*P1;

    return (AB.x*AP.y - AB.y*AP.x)>=0;
}

bool Triangle::isEmpty(const vector<Vector2D*> &tmp, int n) {
    auto p=tmp.begin()+n;
    while (p!=tmp.end() && (!isOnTheLeft(*p,ptr[0],ptr[1]) || !isOnTheLeft(*p,ptr[1],ptr[2]) || !isOnTheLeft(*p,ptr[2],ptr[0]))) {
        p++;
    }
    return p==tmp.end();
}

bool Triangle::isInside(const Vector2D &P) {
    return isOnTheLeft(&P,ptr[0],ptr[1]) && isOnTheLeft(&P,ptr[1],ptr[2]) && isOnTheLeft(&P,ptr[2],ptr[0]);
}

void Triangle::onDraw() {
    glColor3fv(isDelaunay?(isHighlighted?GREEN:GREY):(isHighlighted?ORANGE:YELLOW));

    glBegin(GL_TRIANGLES);
    glVertex2f(ptr[0]->x,ptr[0]->y);
    glVertex2f(ptr[1]->x,ptr[1]->y);
    glVertex2f(ptr[2]->x,ptr[2]->y);
    glEnd();
    glColor3fv(BLACK);
    glBegin(GL_LINE_LOOP);
    glVertex2f(ptr[0]->x,ptr[0]->y);
    glVertex2f(ptr[1]->x,ptr[1]->y);
    glVertex2f(ptr[2]->x,ptr[2]->y);
    glEnd();
}

void Triangle::drawCircle() {
    // draw circle
    if (isHighlighted) {
        glColor3fv(RED);
        glPushMatrix();
        glTranslatef(circumCenter.x,circumCenter.y,0);
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        float a=0.0;
        for (int i=0; i<40; i++) {
            glVertex2f(circumRadius*cos(a),circumRadius*sin(a));
            a+=(float)(M_PI/20.0);
        }
        glEnd();
        glLineWidth(1);
        glPopMatrix();
    }
}

bool Triangle::isInsideCircle(const Vector2D &P) const{
    Matrix33 mat33;
    mat33.m[0][0] = ptr[0]->x-P.x; mat33.m[0][1] = ptr[0]->y-P.y; mat33.m[0][2] = ((ptr[0]->x)*(ptr[0]->x) - (P.x * P.x)) + ((ptr[0]->y * ptr[0]->y)-(P.y * P.y));
    mat33.m[1][0] = ptr[1]->x-P.x; mat33.m[1][1] = ptr[1]->y-P.y; mat33.m[1][2] = ((ptr[1]->x)*(ptr[1]->x) - (P.x * P.x)) + ((ptr[1]->y * ptr[1]->y)-(P.y * P.y));
    mat33.m[2][0] = ptr[2]->x-P.x; mat33.m[2][1] = ptr[2]->y-P.y; mat33.m[2][2] = ((ptr[2]->x)*(ptr[2]->x) - (P.x * P.x)) + ((ptr[2]->y * ptr[2]->y)-(P.y * P.y));

    return mat33.determinant() > 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
