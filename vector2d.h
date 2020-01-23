#ifndef SERVERS_AND_DRONES_VECTOR2D_H
#define SERVERS_AND_DRONES_VECTOR2D_H

#include <ostream>

class Vector2D {

public:
    float x;
    float y;

    Vector2D(float X, float Y);


    Vector2D();

    float length();

    Vector2D unit();

    float magnitude(Vector2D v);

    Vector2D operator+(const Vector2D &v) const;
    Vector2D operator-(const Vector2D &v) const;
    Vector2D operator * (const float &v) const;

    bool operator == (const Vector2D &v) const;
    friend std::ostream& operator << (std::ostream &out, const Vector2D &v);
};


#endif //SERVERS_AND_DRONES_VECTOR2D_H
