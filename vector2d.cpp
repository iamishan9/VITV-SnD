#include <cmath>
#include <ostream>

#include "vector2d.h"


Vector2D::Vector2D(float X, float Y) {
    this->x = X;
    this->y = Y;
}

Vector2D::Vector2D() {
    this->x = 0;
    this->y = 0;
}

float Vector2D::length() {
    return std::sqrt((x * x) + (y * y));
}

Vector2D Vector2D::unit() {
    float l = length();
    return {x/l, y/l};
}

float Vector2D::magnitude(Vector2D v) {
    return sqrt(((v.x - x)*(v.x - x)) + ((v.y - y)*(v.y - y)));
}

Vector2D Vector2D::operator * (const float &v) const {
    return {x * v, y * v};
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
//
//void Vector2D::operator<<(const Vector2D &v) const {
//
//}

std::ostream& operator << (std::ostream &out, const Vector2D &v) {
    out << "(" << v.x<< ", " << v.y<< ")";
    return out;
}