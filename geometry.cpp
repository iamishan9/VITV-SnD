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

    //    Let P = {P 0 , ..., P N −1 } be a set of points of R 2 . Using previous tools, we want to propose an
    //    complete algorithm which allows to construct Delaunay mesh linking every points.

    std::vector<Vector2D> P;

    for (const auto &point : points) {
        vertices.push_back(point);
        P.push_back(point);
        //P.insert(P.begin(), point);
    }

    //    Our algorithm will follow the steps:
    //    1. Calculate the convex hull of E = CH(P ), made of m points.

    std::vector<Vector2D> E = graham(P);
    std::vector<Vector2D> E_tmp = graham(P);

    //    2. Create an initial mesh.
    //    (a) First step: Define a mesh made of m−2 triangles T i−1 = (E 0 , E i , E i+1 )|i ∈ [1..m−1].
    int m = E.size();
    Vector2D *ptr[3];
    for (int i = 1; i < m-1; i++) {
        //std::cout << "p1: " << E[0] << " p2: " << E[i] << " p3: " << E[i+1] << std::endl;
        ptr[0] = new Vector2D(E[0]);
        ptr[1] = new Vector2D(E[i]);
        ptr[2] = new Vector2D(E[i+1]);
        //triangles.push_back( Triangle(ptr[0], ptr[1], ptr[2]) );
        triangles.emplace_back(ptr[0], ptr[1], ptr[2] );
    }

    std::cout << "nb triangles: " << triangles.size() << std::endl;
    std::cout << "m: " << m << std::endl;

    //  (b) Second step: Add interior points (P − E), in replacing the every triangles T (A, B, C)
    //  that contains a point P i by the three triangles (A, B, P i ), (B, C, P i ) and (C, A, P i ).
    //  (c) Repeat (2) while there exists interior points.
    //   3. Apply the algorithm of Triangulation of Delaunay


    std::vector<Vector2D> P_E;
    std::sort(P.begin(), P.end());
    std::sort(E_tmp.begin(), E_tmp.end());
    std::set_difference(P.begin(), P.end(), E_tmp.begin(), E_tmp.end(),
                        std::inserter(P_E, P_E.begin()));


    //P_E.resize(P.size() - E.size());

    std::cout << "All points:" << std::endl;
    for (auto p : P) {
        std::cout << p << "  ";
    }
    std::cout << "\nConvex hull points:" << std::endl;
    for (auto p : E) {
        std::cout << p << "  ";
    }
    std::cout << "\nInterior points:" << std::endl;
    for (auto p : P_E) {
        std::cout << p << "  ";
    }

    // (2) replacing the every triangles T (A, B, C)
    //  that contains a point P i by the three triangles (A, B, P i ), (B, C, P i ) and (C, A, P i ).
    //  (c) Repeat (2) while there exists interior points.

    while (!P_E.empty()) {
        for (auto &point : P_E) {
            for (auto &triangle : triangles) {
                if (triangle.isInside(point)) {
                    std::cout << "Point " << point << " is inside T" << std::endl;
                    ptr[0] = new Vector2D(*triangle.ptr[0]);
                    ptr[1] = new Vector2D(*triangle.ptr[1]);
                    ptr[2] = new Vector2D(*triangle.ptr[2]);
                    triangle.updateVertices(ptr[0], ptr[1], new Vector2D(point));
                    triangles.emplace_back(ptr[1], ptr[2], new Vector2D(point));
                    triangles.emplace_back(ptr[2], ptr[0], new Vector2D(point));
                    P_E.pop_back();
                }
            }
        }
    }

    std::cout << "\nTriangles generated:" << std::endl;
    for (const auto& triangle : triangles) {
        std::cout << "p1: " << *triangle.ptr[0] << " p2: " << *triangle.ptr[1] << " p3: " << *triangle.ptr[2] << std::endl;
    }

    checkDelaunay();
}

Triangle* Mesh::neighborInside(Triangle* current) {

    auto t = triangles.begin();
    while (t != triangles.end()) {

        bool isInside = false;
        int commonPoints = 0;

        for(int i=0; i < 3; i++){
            if(current->isInsideCircle(*t->ptr[i]))
                isInside = true;

            for(int j=0; j<3; j++){
                if(*t->ptr[i] == *current->ptr[j])
                    commonPoints++;
            }
        }
        if(commonPoints == 2){
            if(isInside)
                return &(*t);
        }

        t++;
    }
    return nullptr;
}

//void Mesh::flip(Triangle *current, Triangle *neighbor) {
//    // ABC -> APC   // if AB shared edge
//    // ABP -> CBP
//
//    // ABC -> ABP   // if BC shared edge
//    // PBC -> PAC
//
//    // CAB -> PAB   // if CA shared edge
//    // CAP -> CBP
//
////    if ( (*current->ptr[0] == *neighbor->ptr[0] && *current->ptr[1] == *neighbor->ptr[1])
////        || (*current->ptr[1] == *neighbor->ptr[0] && *current->ptr[0] == *neighbor->ptr[1])
////        || (*current->ptr[0] == *neighbor->ptr[1] && *current->ptr[1] == *neighbor->ptr[0])) { // AB shared edge // 0-1
////        current->ptr[1] = new Vector2D(*neighbor->ptr[2]);
////        neighbor->ptr[0] = new Vector2D(*current->ptr[2]);
////
////    }
////    if ((*current->ptr[1] == *neighbor->ptr[1] && *current->ptr[2] == *neighbor->ptr[2])
////        || (*current->ptr[1] == *neighbor->ptr[2] && *current->ptr[2] == *neighbor->ptr[1])
////        || (*current->ptr[2] == *neighbor->ptr[1] && *current->ptr[1] == *neighbor->ptr[2])) { // BC shared edge // 1-2
////        current->ptr[2] = new Vector2D(*neighbor->ptr[1]);
////        neighbor->ptr[1] = new Vector2D(*current->ptr[0]);
////    }
////    if ((*current->ptr[0] == *neighbor->ptr[0] && *current->ptr[2] == *neighbor->ptr[2])
////        || (*current->ptr[0] == *neighbor->ptr[2] && *current->ptr[2] == *neighbor->ptr[0])
////        || (*current->ptr[2] == *neighbor->ptr[0] && *current->ptr[0] == *neighbor->ptr[2])){ // CA shared edge // 0-2
////        current->ptr[2] = new Vector2D(*neighbor->ptr[2]);
////        neighbor->ptr[0] = new Vector2D(*current->ptr[1]);
////    }
//    if (*current->ptr[0] == *neighbor->ptr[0] && *current->ptr[2] == *neighbor->ptr[1]) {
//        current->ptr[2] = new Vector2D(*neighbor->ptr[2]);
//        neighbor->ptr[0] = new Vector2D(*current->ptr[1]);
//    }
//}

void Mesh::flip(Triangle* curr, Triangle* neighbor) {


    Vector2D *PC = curr->getUniquePoint(neighbor);
    Vector2D *PN = neighbor->getUniquePoint(curr);

    Vector2D *PCN = getNextPoint(curr, PC);
    Vector2D *PNN = getNextPoint(neighbor, PN);


    curr->updateVertices(PC,PCN,PN);
    neighbor->updateVertices(PN,PNN,PC);
}

Vector2D* Mesh::getNextPoint(Triangle *t, Vector2D *v){
    for(int i=0; i<3; i++) {
        if(t->ptr[i]->x == v->x && t->ptr[i]->y == v->y){
            i++;
            if (i > 2 )
                return t->ptr[0];
            else
                return (t->ptr[i]);
        }
    }
}



//Mesh::Mesh(const std::vector<Vector2D> &points) {
//    for (auto point : points) {
//        vertices.push_back(point);
//    }
//    init_triangles(vertices);
//}

//void Mesh::init_triangles(const std::vector<Vector2D> &points) {
//
//    if (points.size() < 3) {
//        // Can't init
//    }
//}

bool Mesh::checkDelaunay() {
    bool isDelaunay = true;
    for(auto &triangle : triangles) {
        isDelaunay = triangle.checkDelaunay(vertices) && isDelaunay;
    }
    return isDelaunay;
}

void Mesh::solveDelaunay() {
    delaunay(this);
}

Mesh::~Mesh() {
    vertices.clear();
    triangles.clear();
}

void Mesh::onDraw() {

    if (vertices.size() < 3) {
        glPushMatrix();
        glBegin(GL_LINE_LOOP);
        for (auto &vertex : vertices) {
            glVertex2f(vertex.x, vertex.y);
        }
        glEnd();
        glPopMatrix();
    }
    else {
        for (auto triangle : triangles) {
            triangle.onDraw();
        }
        for (auto triangle : triangles) {
            triangle.drawCircle();
        }
    }


}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Polygon::Polygon()
    : n_edges(0)
{
    vertices = std::vector<Vector2D>();
}

Polygon::Polygon(const std::vector<Vector2D> &vertices_) {
    for (const auto &vertex : vertices_) {
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

    glPushMatrix();

    glBegin(GL_POLYGON);
    for (auto &vertex : vertices) {
        glVertex2f(vertex.x, vertex.y);
    }
    glVertex2f(vertices[0].x, vertices[0].y);
    glEnd();

    // Draw the borders of the polygon.
    glColor3b(0, 0, 255);

    glBegin(GL_LINE_LOOP);
    for (auto vertex : vertices) {
        glVertex2f(vertex.x, vertex.y);
    }
    glVertex2f(vertices[0].x, vertices[0].y);
    glEnd();

    glPopMatrix();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Triangle::Triangle() {
    ptr[0] = new Vector2D();
    ptr[1] = new Vector2D();
    ptr[2] = new Vector2D();
    isHighlighted = false;
    calculateCircle();
}


Triangle::Triangle(Vector2D *ptr1, Vector2D *ptr2, Vector2D *ptr3) {
    ptr[0] = ptr1;
    ptr[1] = ptr2;
    ptr[2] = ptr3;
    isHighlighted = false;
    calculateCircle();

}

void Triangle::updateVertices(Vector2D *ptr1, Vector2D *ptr2, Vector2D *ptr3) {
    ptr[0] = ptr1;
    ptr[1] = ptr2;
    ptr[2] = ptr3;
//    ptr[0] = new Vector2D(*ptr1);
//    ptr[1] = new Vector2D(*ptr2);
//    ptr[2] = new Vector2D(*ptr3);
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

void Triangle::onMouseMove(const Vector2D &pos) {
    isHighlighted = isInside(pos);

    if (isHighlighted) {
        std::cout << "is inside a triangle" << std::endl;
    }
}

bool Triangle::isOnTheLeft(const Vector2D *P, const Vector2D *P1, const Vector2D *P2) {
    Vector2D AB = *P2 - *P1,
            AP = *P - *P1;

    return (AB.x * AP.y - AB.y * AP.x) >= 0;
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

    glPushMatrix();

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

    glPopMatrix();
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

bool Triangle::checkDelaunay(const std::vector<Vector2D> &points) {
    auto p = points.begin();
    while(p != points.end() && !isInsideCircle(*p)) {
        p++;
    }
    isDelaunay = (p==points.end());
    return isDelaunay;
}

Vector2D* Triangle::getUniquePoint(Triangle *t) {
    bool b0, b1, b2;

    for(int i=0; i<3; i++) {
        b0 = (ptr[i]->x != t->ptr[0]->x) && (ptr[i]->y != t->ptr[0]->y);
        b1 = (ptr[i]->x != t->ptr[1]->x) && (ptr[i]->y != t->ptr[1]->y);
        b2 = (ptr[i]->x != t->ptr[2]->x) && (ptr[i]->y != t->ptr[2]->y);
        if(b0 && b1 && b2)
            return ptr[i];
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//void flip( Triangle *curr,  Triangle *neighbor){
//    for(int a=0;a<3;a++){
//        cout<<"BEFORE curr  "<<curr->ptr[a]<<"and neighbor "<<neighbor->ptr[a]<<endl;
//    }
//
//    list<Vector2D *> points;
//    for(int i=0;i<3;i++){
//        if(find(points.begin(), points.end(), curr->ptr[i]) != points.end()) {
//            cout<<"The point is already contained ====>"<<curr->ptr[i] <<endl;
//        }else{
//            points.push_back(curr->ptr[i]);
//        }
//    }
//
//    for(int j=0; j<3; j++){
//        if(find(points.begin(), points.end(), neighbor->ptr[j]) != points.end()) {
//            cout<<"The point is already contained ====>"<<neighbor->ptr[j] <<endl;
//        }else{
//            points.push_back(neighbor->ptr[j]);
//        }
//    }
//
//    list<Vector2D *> copyPoints = points;
//    points.pop_front();
//    Vector2D *lastPoint = points.back();
//    copyPoints.pop_back();
//    copyPoints.pop_back();
//    copyPoints.push_front(lastPoint);
//
//    for(int k=0; k<3;k++){
//        curr->ptr[k] = points.front();
//        neighbor->ptr[k] = copyPoints.front();
//        points.pop_front();
//        copyPoints.pop_front();
//    }
//
//    for(int a=0;a<3;a++){
//        cout<<"AFTER curr  "<<curr->ptr[a]<<"and neighbor "<<neighbor->ptr[a]<<endl;
//    }
//
//}