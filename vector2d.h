#ifndef SERVERS_AND_DRONES_VECTOR2D_H
#define SERVERS_AND_DRONES_VECTOR2D_H

#include <ostream>

class Vector2D {

public:
    float x;
    float y;

    Vector2D();
    Vector2D(float X, float Y);
    Vector2D(const Vector2D &other);
    Vector2D(Vector2D &other);


    Vector2D& operator=(const Vector2D& other);
    float length();
    float norm() const;
    Vector2D ortho();
    Vector2D getRightOrtho();
    Vector2D unit();

    float magnitude(Vector2D v);

    Vector2D operator+(const Vector2D &v) const;
    Vector2D operator-(const Vector2D &v) const;
    Vector2D operator*(const float &v) const;
    float operator*(const Vector2D &op2) const;
    bool operator<(const Vector2D &v) const;
    bool operator==(const Vector2D &v) const;
    friend Vector2D operator*(float a, const Vector2D &v);
    friend std::ostream& operator<<(std::ostream &out, const Vector2D &v);
};


#endif //SERVERS_AND_DRONES_VECTOR2D_H
