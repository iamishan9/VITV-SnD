#ifndef VITV_SND_DRONE_H
#define VITV_SND_DRONE_H


#include <glutWindow.h>
#include "Vector2D.h"

class Drone {
public:

    GLuint id; // TODO: Should be static

    float size = 30;
    float maxSpeed = 15;

    bool isDestroyed = false;

    Vector2D position;
    Vector2D target;
    Vector2D velocity     = Vector2D();
    Vector2D acceleration = Vector2D();

    /*
     * Creates a drone at pos
     */
    Drone(Vector2D pos, GLuint textureId);

    /*
     * Called at each frame to render the drone
     */
    void onDraw();

    /*
     * Called at each frame to update drone movement
     */
    void onUpdate(Vector2D avoidForce);

    /*
     * Return true if the drone collide with the other given drone
     */
    bool willCollideWith(Drone* d);

    /*
     * Called when the drone did collide with another drone
     */
    void didCollide();
};

#endif //VITV_SND_DRONE_H
