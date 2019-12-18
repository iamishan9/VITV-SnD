//
// Created by tomde on 18/12/2019.
//
#ifndef VITV_SND_VECTOR2_H
#define VITV_SND_VECTOR2_H

class Vector2 {
public:

    float x;
    float y;

    /*
     * Creates a Vector2 instance with the given X Y components
     */
    Vector2(float X, float Y);

    /*
     * Creates a zero vector
     */
    Vector2();

    /*
     * Returns the length of the vector
     */
    float length();

    /*
     * Returns a normalized vector (length = 1)
     */
    Vector2 unit();

    /*
     * Returns the magnitude (distance) between the two vectors
     */
    float magnitude(Vector2 v);


    Vector2 operator+(const Vector2 &v);

    Vector2 operator-(const Vector2 &v);

    Vector2 operator * (const float &v);

    bool operator == (const Vector2 &v);
};

#endif //VITV_SND_VECTOR2_H