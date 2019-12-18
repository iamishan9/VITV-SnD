//
// Created by tomde on 18/12/2019.
//
#include "Drone.h"

float dampering = .95;

Drone::Drone(Vector2 pos, GLuint textureId) {
    position = pos;
    target = pos;
    id = textureId;
}

void Drone::didCollide() {
    cout << "Collided!" << endl;
    isDestroyed = true;
}

bool Drone::willCollideWith(Drone* d) {
    if (this == d) { return false; }
    return (position.magnitude(d->position) < size);
}

void Drone::onUpdate(Vector2 avoidForce) {

    // Check if current velocity exceeds the drone's maximum speed
    if (Vector2().magnitude(velocity) > maxSpeed) {
        // If so, reduce it to the maximum
        velocity = velocity.unit() * maxSpeed;
    }

    // Updates the velocity
    velocity = velocity + acceleration;

    // Moves the drone in it's direction
    position = position - velocity;

    velocity = velocity * dampering;

    // Computes the acceleration
    if (position == target) {
        acceleration = Vector2();
    } else {
        Vector2 dirVector = (position - target).unit();
        acceleration = dirVector;
    }

    acceleration = acceleration + avoidForce;
}

void Drone::onDraw() {
    if (isDestroyed) {
        // Don't render a destroyed drone
        return;
    }
    glBindTexture(GL_TEXTURE_2D, id);
    glPushMatrix();
    glTranslatef(position.x - (size / 2), position.y - (size / 2), 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(size,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(size, size);
    glTexCoord2f(0.0,1.0);
    glVertex2f(0.0, size);
    glEnd();
    glPopMatrix();
}
