//
// Created by tomde on 18/12/2019.
//
#ifndef VITV_SND_DRONE_H
#define VITV_SND_DRONE_H

#include "../glutWindow.h"
#include "Vector2.h"
#include "Server.h"

class Drone {
public:

    GLuint id; // TODO: Should be static

    float size = 30;
    float maxSpeed = 15;

    bool isDestroyed = false;

    Vector2 position;
    Vector2 target;
    Vector2 velocity     = Vector2();
    Vector2 acceleration = Vector2();

    Server* server;

    /*
     * Creates a drone at pos
     */
    Drone(Vector2 pos, GLuint textureId);

    /*
     * Called at each frame to render the drone
     */
    void onDraw();

    /*
     * Called at each frame to update drone movement
     */
    void onUpdate(Vector2 avoidForce);

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