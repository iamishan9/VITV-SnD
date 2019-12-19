#pragma once
#include <vector>

#include "glutWindow.h"
#include "src/Vector2D.h"
#include "src/Drone.h"
#include "src/Server.h"

class MainWindow: public GlutWindow {
public:

    vector<Drone*> drones;
    vector<Server*> servers;

    GLuint droneId  = 0;
    GLuint serverId = 0;

    const static unsigned int windowX = 800;
    const static unsigned int windowY = 600;

    Vector2D mousePos = Vector2D();

    MainWindow(const string &title, int argc, char **argv):
            GlutWindow(argc, argv, title, windowX, windowY, FIXED) {
    };

    bool MB_DOWN = false;
    Server* selectedServer = nullptr;

    void onStart() override;
    void onDraw() override;
    void onQuit() override;
    void onMouseDown(int button, double x, double y) override;
    void onMouseUp(int button, double x, double y) override;
    void onMouseDrag(double x, double y) override;
    void onMouseMove(double x, double y) override;
    void onKeyPressed(unsigned char c, double x, double y) override;
    void onReshape(int x, int y) override;
    void onUpdate(double dt) override;

    float avoidDronesRange = 125;
    float avoidForce       = 200;

    /*
     * Computes the force that should be applied in order
     * to avoid all drones in the avoidDroneRange
     */
    Vector2D avoidingForceForDrone(Drone* d) {
        Vector2D avg = Vector2D();
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

    float padding = 15;

    /*
     * Prevents the user from placing a server outside the screen boundaries
     */
    Vector2D clampToScreenDimensions(Vector2D v) {
        if (v.y > 10000) v.y = -1;
        float x = v.x;
        float y = v.y;
        if (x < (padding)) x = padding;
        if (x > (windowX - padding)) x = (windowX - padding);
        if (y < (padding)) y = padding;
        if (y > (windowY - padding)) y = (windowY - padding);
        return {x, y};
    }
};

void MainWindow::onStart() {

    // Load the assets
    droneId  = GlutWindow::loadTGATexture("../assets/drone.tga", 50, 50);
    serverId = GlutWindow::loadTGATexture("../assets/antenna.tga", 64, 64);

    // Creates a new drone
    drones.push_back(new Drone(Vector2D(10, 10), droneId));

    // Creates servers
    servers.push_back(new Server(Vector2D(250, 250), "Demo 1", serverId));
    servers.push_back(new Server(Vector2D(650, 250), "Demo 2", serverId));

    glClearColor(1.0,1.0,1.0,1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MainWindow::onDraw() {
    Server* hoveredServer = selectedServer;
    if (!hoveredServer) {
        for (Server* server : servers) {
            if (mousePos.magnitude(server->position) < (server->size + 10)) {
                hoveredServer = server;
            }
        }
    }
    if (hoveredServer) {
        glColor3f(.75, .75,.95);
        glPushMatrix();
        fillEllipse(
                hoveredServer->position.x,
                hoveredServer->position.y - 10,
                hoveredServer->size + 10,
                hoveredServer->size + 10,
                60
        );
        glPopMatrix();
    }

    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f,1.0f,1.0f);

    for (Server* server : servers) {
        glPushMatrix();
        server->onDraw();
        glPopMatrix();
    }

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
        servers.push_back(new Server(Vector2D(x, y), "Demo", serverId));
    }
}

void MainWindow::onMouseUp(int button, double x, double y) {
    selectedServer = nullptr;
}

void MainWindow::onMouseMove(double x, double y) {
    mousePos = Vector2D(x, y);
    for (Drone* drone : drones) {
        drone->target = mousePos;
    }
}

void MainWindow::onMouseDrag(double x, double y) {
    onMouseMove(x, y);
    if (!selectedServer) {
        for (Server* server : servers) {
            if (mousePos.magnitude(server->position) < (server->size + 10)) {
                selectedServer = server;
                break;
            }
        }
    }
    if (selectedServer) {
        selectedServer->position = clampToScreenDimensions(mousePos);
    }
}

#define KB_DEL 127
#define KB_BACKSPACE 8
void MainWindow::onKeyPressed(unsigned char c, double x, double y) {
    switch(c) {
        case 'd': // Add a drone to the window
            drones.push_back(new Drone(Vector2D(10, 10), droneId));
            break;

            case KB_DEL: case KB_BACKSPACE:
            for (Server* server : servers) {
                if (mousePos.magnitude(server->position) < (server->size + 10)) {
                    // TODO: Eventually do this better
                    vector<Server*> tmp;
                    for (Server* mserver : servers) {
                        if (mserver != server) {
                            tmp.push_back(mserver);
                        } else {
                            cout << "Removing server" << endl;
                        }
                    }
                    servers = tmp;
                    break;
                }
            }
            break;

        case 's': // Save the configuration in the file
            for (auto server:servers){
                cout << server->returnStringForSave() << endl;
            }
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

void MainWindow::onReshape(int x, int y) {
    // Locks screen dimensions
    glutReshapeWindow( windowX, windowY);
}

void MainWindow::onQuit() {}

int main(int argc, char **argv) {
    MainWindow("Drones", argc, argv).start();
    return 0;
}