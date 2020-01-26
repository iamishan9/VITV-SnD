#include <cmath>
#include <ostream>

#include "vector2d.h"


Vector2D::Vector2D(float X, float Y) {
    this->x = X;
    this->y = Y;
}

Vector2D::Vector2D(const Vector2D &v) {
    x = v.x;
    y = v.y;
}

Vector2D::Vector2D() {
    this->x = 0;
    this->y = 0;
}

float Vector2D::length() {
    return std::sqrt((x * x) + (y * y));
}

float Vector2D::norm() const {
    return std::sqrt(x * x + y * y );
}

Vector2D Vector2D::ortho() {
    return Vector2D(-y,x);
}

Vector2D Vector2D::getRightOrtho(){
    return Vector2D(y,-x);
}

Vector2D Vector2D::unit() {
    float l = length();
    return {x/l, y/l};
}

float Vector2D::magnitude(Vector2D v) {
    return sqrt(((v.x - x)*(v.x - x)) + ((v.y - y)*(v.y - y)));
}

Vector2D Vector2D::operator*(const float &v) const {
    return {x * v, y * v};
}

Vector2D operator*(float a, const Vector2D &v) {
    return Vector2D(a*v.x,a*v.y);
}

float Vector2D::operator*(const Vector2D &op2) const {
    return x * op2.x + y * op2.y;
}

bool Vector2D::operator == (const Vector2D &v) const {
    return (x == v.x) && (y == v.y);
}

Vector2D Vector2D::operator+(const Vector2D &v) const {
    return {x + v.x, y + v.y};
}

Vector2D Vector2D::operator-(const Vector2D &v) const {
    return {x - v.x, y - v.y};
}

bool Vector2D::operator<(const Vector2D &v) const {
    return (this->x == v.x) ? (this->y < v.y) : (this->x < v.x);

//    double a1 = asin(this->y / sqrt(this->x * this->x + this->y * this->y));
//    if (this->x < 0.0)
//        a1 = M_PI - a1;
//
//    double a2 = asin(v.y / sqrt(v.x * v.x + v.y * v.y));
//    if (v.x < 0.0)
//        a2 = M_PI - a2;
//
//    return a1 < a2;
}

std::ostream& operator << (std::ostream &out, const Vector2D &v) {
    out << "(" << v.x<< ", " << v.y<< ")";
    return out;
}

