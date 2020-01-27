////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SERVERS_AND_DRONES_GEOMETRY_H
#define SERVERS_AND_DRONES_GEOMETRY_H

#include <list>
#include <vector>

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

    Mesh();
    Mesh(const std::vector<Vector2D> &P);
    ~Mesh();

    //void init_triangles(const std::vector<Vector2D> &points);

    Triangle* neighborInside(Triangle *triangle);
    void flip(Triangle *current, Triangle *neighbor);

    void solveDelaunay();
    bool checkDelaunay();

    Vector2D* getNextPoint(Triangle *t, const Vector2D *v) const;
    Vector2D* getPrevPoint(Triangle *t, const Vector2D *v) const;
    Triangle rightNeighbor(Triangle &t, std::list<Triangle> &triangles) const;
    void solveVoronoi();
    Vector2D intersectionWithBorders(Vector2D H, Vector2D u, float xx, float yy, float x, float y) const;

    void onDraw();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Polygon {
public:
    int n_edges;
    std::vector<Vector2D> vertices;

    Polygon();
    Polygon(const Polygon &polygon);
    Polygon(Polygon &polygon);
    Polygon(const std::vector<Vector2D> &vertices);

    ~Polygon();

    Polygon& operator=(const Polygon& other);

    void addPoint(const Vector2D &point);
    void addCornerPoints();
    void addCornerPoints(float w, float h);

    void onDraw();
    void onDraw(const float *color);
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
    void updateVertices(Vector2D *ptr1, Vector2D *ptr2, Vector2D *ptr3);
    void calculateCircle();
    bool checkDelaunay(const std::vector<Vector2D> &points);
    bool isOnTheLeft(const Vector2D *P, const Vector2D *P1, const Vector2D *P2);
    bool isEmpty(const std::vector<Vector2D*> &tmp, int n);
    bool isInside(const Vector2D &P);
    void onDraw();
    void drawCircle();
    void onMouseMove(const Vector2D& pos);
    bool isInsideCircle(const Vector2D &P) const;
    Vector2D* getUniquePoint(Triangle *t);
    bool containsPoint(const Vector2D *point) const;
    friend std::ostream& operator << (std::ostream &out, const Triangle &triangle);
    bool operator == (const Triangle& s) const;
    bool operator != (const Triangle& s) const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //SERVERS_AND_DRONES_GEOMETRY_H
