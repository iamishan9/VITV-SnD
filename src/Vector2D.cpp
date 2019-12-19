//
// Created by tomde on 18/12/2019.
//
#include "Vector2D.h"
#include <cmath>

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

Vector2D Vector2D::operator * (const float &v) {
    return {x * v, y * v};
}

bool Vector2D::operator == (const Vector2D &v) {
    return (x == v.x) && (y == v.y);
}

Vector2D Vector2D::operator+(const Vector2D &v) {
    return {x + v.x, y + v.y};
}

Vector2D Vector2D::operator-(const Vector2D &v) {
    return {x - v.x, y - v.y};
}