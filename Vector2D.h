#ifndef VITV_SND_VECTOR2D_H
#define VITV_SND_VECTOR2D_H

class Vector2D {

public:

    float x;
    float y;

    /*
     * Creates a Vector2 instance with the given X Y components
     */
    Vector2D(float X, float Y);

    /*
     * Creates a zero vector
     */
    Vector2D();

    /*
     * Returns the length of the vector
     */
    float length();

    /*
     * Returns a normalized vector (length = 1)
     */
    Vector2D unit();

    /*
     * Returns the magnitude (distance) between the two vectors
     */
    float magnitude(Vector2D v);

    Vector2D operator+(const Vector2D &v);
    Vector2D operator-(const Vector2D &v);
    Vector2D operator * (const float &v);

    bool operator == (const Vector2D &v);
};

#endif //VITV_SND_VECTOR2D_H
