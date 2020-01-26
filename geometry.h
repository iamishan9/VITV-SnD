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
    vector<Vector2D> vertices;
    vector<Triangle> triangles;
    vector<Polygon*> vorPolygons;

    vector<Vector2D> P;
    vector<Vector2D> P_E;

    bool vorCreated=false;

    Mesh();
    Mesh(const std::vector<Vector2D> &P);
    ~Mesh();

    void init_triangles(const std::vector<Vector2D> &points);
    void checkDelaunay();
    void solveDelaunay();
    void onDraw();
    void onKeyPressed(unsigned char c, double x, double y);
    void flip(Triangle* curr, Triangle* neighbor);
    Triangle* neighborInside(Triangle* currentTriangle);
    Vector2D* getNextPoint(Triangle *t, Vector2D *v);
    Vector2D* getPrevPoint(Triangle *t, Vector2D *v);
    Triangle rightNeighbor(Triangle &t, list<Triangle> &triangles);
    void makeVoronoi();
    Vector2D intersectionWithBorders(Vector2D H, Vector2D u, float xx, float yy, float x, float y);
};

class Polygon {
public:
    int n_max;
    int n_edges;


    std::vector<Vector2D> vertices;
    Vector2D *pPoints;

    Polygon();
    Polygon(int p_max);
    Polygon(const std::vector<Vector2D> &vertices);
    ~Polygon();

    void onDraw();
    void draw();
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
//    bool operator==(const Triangle& lhs);

    bool operator == (const Triangle& s) const { return ptr[0] == s.ptr[0] && ptr[1] == s.ptr[1] && ptr[2] == s.ptr[2]; }
    bool operator != (const Triangle& s) const { return !operator==(s); }
    Vector2D* getUniquePoint(Triangle *triangle);
    bool containsPoint(Vector2D *point);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* // TODO put Vector2D here!
class Vector2D {

};
*/

#endif //SERVERS_AND_DRONES_GEOMETRY_H
