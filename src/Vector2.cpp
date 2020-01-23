//
// Created by tomde on 18/12/2019.
//
#include "Vector2.h"
#include <cmath>

Vector2::Vector2(float X, float Y) {
    this->x = X;
    this->y = Y;
}

Vector2::Vector2() {
    this->x = 0;
    this->y = 0;
}

float Vector2::length() {
    return std::sqrt((x * x) + (y * y));
}

Vector2 Vector2::unit() {
    float l = length();
    return {x/l, y/l};
}

float Vector2::magnitude(Vector2 v) {
    return sqrt(((v.x - x) * (v.x - x)) + ((v.y - y) * (v.y - y)));
}

Vector2 Vector2::operator * (const float &v) {
    return {x * v, y * v};
}

bool Vector2::operator == (const Vector2 &v) {
    return (x == v.x) && (y == v.y);
}

Vector2 Vector2::operator+(const Vector2 &v) {
    return {x + v.x, y + v.y};
}

Vector2 Vector2::operator-(const Vector2 &v) {
    return {x - v.x, y - v.y};
}