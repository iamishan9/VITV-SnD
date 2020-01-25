////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SERVERS_AND_DRONES_GEOMETRY_H
#define SERVERS_AND_DRONES_GEOMETRY_H


#include <vector>
#include <list>

#include "vector2d.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Matrix22;
class Matrix33;
class Matrix44;
class Mesh;
class Polygon;
class Triangle;
//class Vector2D;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



class Matrix22 {
public:
    float m[2][2];

    void get2x2From3x3(const Matrix33 &mat33, int shadowLin, int shadowCol);
    inline float determinant() {
        return m[0][0]*m[1][1]-m[0][1]*m[1][0];
    }
};

class Matrix33 {
public:
    float m[3][3];

    void get3x3From4x4(const Matrix44 &mat44, int shadowLin, int shadowCol);
    float determinant();
};

class Matrix44 {
public:
    float m[4][4];

    float determinant();
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Mesh {
public:
    std::vector<Vector2D> vertices;
    std::vector<Triangle> triangles;

    std::vector<Vector2D> P;
    std::vector<Vector2D> P_E;

    Mesh();
    Mesh(const std::vector<Vector2D> &P);
    ~Mesh();

    void init_triangles(const std::vector<Vector2D> &points);
    void checkDelaunay();
    void solveDelaunay();
    void onDraw();
    void onKeyPressed(unsigned char c, double x, double y);
    void addInteriorPoints();
    void flip(Triangle* curr, Triangle* neighbor);
    Triangle* neighborInside(Triangle* currentTriangle);
    Vector2D* getNextPoint(Triangle *t, Vector2D *v);
    void makeVoronoi();
};

class Polygon {
public:
    int n_edges;
    std::vector<Vector2D> vertices;

    Polygon();
    Polygon(const std::vector<Vector2D> &vertices);
    ~Polygon();

    void onDraw();
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Triangle {
public:
    Vector2D *ptr[3];
    bool isDelaunay;
    bool isHighlighted;
    Vector2D circumCenter;
    float circumRadius;

    Triangle();
    Triangle(Vector2D *ptr1, Vector2D *ptr2, Vector2D *ptr3);
    void updateVertices(Vector2D *ptr1,Vector2D *ptr2,Vector2D *ptr3);
    void calculateCircle();
    bool checkDelaunay(const std::vector<Vector2D> &points);
    bool isOnTheLeft(const Vector2D *P, const Vector2D *P1, const Vector2D *P2);
    bool isEmpty(const vector<Vector2D*> &tmp, int n);
    bool isInside(const Vector2D &P);
    void onDraw();
    void drawCircle();
    void onMouseMove(const Vector2D& pos);
    bool isInsideCircle(const Vector2D &P) const;

    Vector2D* getUniquePoint(Triangle *triangle);
    Vector2D* getNextPoint(Vector2D *vector);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* // TODO put Vector2D here!
class Vector2D {

};
*/

#endif //SERVERS_AND_DRONES_GEOMETRY_H
