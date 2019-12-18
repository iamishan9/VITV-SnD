#pragma once
#include <vector>

#include "glutWindow.h"
#include "src/Vector2.h"
#include "src/Drone.h"

class MainWindow: public GlutWindow {
public:

    vector<Drone*> drones;

    GLuint droneId = 0;

    MainWindow(const string &title, int argc, char **argv):
            GlutWindow(argc, argv, title,1000,500,FIXED) {
    };

    void onStart() override;
    void onDraw() override;
    void onQuit() override;
    void onMouseDown(int button, double x, double y) override;
    void onMouseMove(double x, double y) override;
    void onUpdate(double dt) override;

    float avoidDronesRange = 125;
    float avoidForce       = 200;

    /*
     * Computes the force that should be applied in order
     * to avoid all drones in the avoidDroneRange
     */
    Vector2 avoidingForceForDrone(Drone* d) {
        Vector2 avg = Vector2();
        float magnitude = 0;
        for (Drone* drone : drones) {
            if (d == drone) continue;
            magnitude = d->position.magnitude(drone->position);
            if (magnitude < avoidDronesRange) {
                avg = avg - ((d->position - drone->position).unit() * (avoidForce / magnitude));
            }
        }
        return avg;
    }
};

void MainWindow::onStart() {

    // Load the drone texture
    droneId = GlutWindow::loadTGATexture("../assets/drone.tga", 50, 50);

    // Creates a new drone
    drones.push_back(new Drone(Vector2(10, 10), droneId));

    glClearColor(1.0,1.0,1.0,1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MainWindow::onDraw() {
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f,1.0f,1.0f);

    for (Drone* drone : drones) {
        if (drone) {
            glPushMatrix();
            drone->onDraw();
            glPopMatrix();
        }
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void MainWindow::onUpdate(double dt) {

    // Remove the destroyed drones
    vector<Drone*> tmp;
    for (Drone* drone : drones) {
        if (!drone->isDestroyed) {
            tmp.push_back(drone);
        } else {
            cout << "Removing drone" << endl;
        }
    }
    drones = tmp;

    // Update the drones positions
    for (Drone* drone : drones) { drone->onUpdate(avoidingForceForDrone(drone)); }

    // Compute the collisions
    Drone* droneA;
    Drone* droneB;
    for (int i = 0; i < drones.size(); i++) {
        droneA = drones[i];
        for (int j = i; j < drones.size(); j++) {
            droneB = drones[j];
            if (droneA->willCollideWith(droneB)) {
                droneA->didCollide();
                droneB->didCollide();
            }
        }
    }
}


#define MB_LEFTCLICK 0
#define MB_RIGHTCLICK 2
void MainWindow::onMouseDown(int button, double x, double y) {
    if (button == MB_LEFTCLICK) {

    }
    if (button == MB_RIGHTCLICK) {
        drones.push_back(new Drone(Vector2(10, 10), droneId));
    }
}

void MainWindow::onMouseMove(double x, double y) {
    for (Drone* drone : drones) {
        drone->target = Vector2(x, y);
    }
}

void MainWindow::onQuit() {}

int main(int argc, char **argv) {
    MainWindow("Drones", argc, argv).start();
    return 0;
}