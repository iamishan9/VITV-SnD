//
// Created by tomde on 18/12/2019.
//
#ifndef VITV_SND_VECTOR2_H
#define VITV_SND_VECTOR2_H

class Vector2D {
public:

    float x;
    float y;

    /**
     * Creates a Vector2D instance with the given X Y components
     * @param X : Abscissa of the point
     * @param Y
     */
    Vector2D(float X, float Y);


    /**
     * Creates a zero vector
     */
    Vector2D();


    /**
     * Returns the length of the vector
     * @return length of the vector
     */
    float length();


    /**
     * @return a normalized vector (length = 1)
     */
    Vector2D unit();


    /**
     * Calculate the magnitude of a vector
     * @param v : The vector to calculate the magnitude
     * @return magnitude (distance) between the two vectors
     */
    float magnitude(Vector2D v);


    /**
     * Operation between vector
     * @param v : The vector to be added
     * @return the vector with the added value
     */
    Vector2D operator+(const Vector2D &v);


    /**
     * Operation between vector
     * @param v : The vector value to substract to the other vector
     * @return the vector with the substracted value
     */
    Vector2D operator-(const Vector2D &v);


    /**
     * Operation between vector
     * @param v : The vector to be multiplied to the other vector
     * @return the vector with the multiplied value
     */
    Vector2D operator * (const float &v);


    /**
     * Test if a vector is equal to another
     * @param v : The vector which need to be tested
     * @return true if they are equal
     */
    bool operator == (const Vector2D &v);
};

#endif //VITV_SND_VECTOR2_H