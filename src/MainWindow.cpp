//
// Created by tomde on 19/12/2019.
//
#include "MainWindow.h"
#include "HelperFile.h"
#include <climits>


float MainWindow::cx(float v) {
    return 5000 + ((v / windowX) * 5000);
}

float MainWindow::cy(float v) {
    return 5000 + ((v / windowY) * 5000);
}

void MainWindow::addServer(Vector2 pos, string name) {
    auto server = new Server(pos, name, serverId);
    servers.push_back(server);
    auto vp = new VPoint(cx(pos.x), cy(pos.y));
    server->vp = vp;
    ver->push_back(vp);
    edg = v->GetEdges(ver, w, w);
}

void MainWindow::addServer(Vector2 pos, string name, string color) {
    auto server = new Server(pos, name, serverId, color);
    servers.push_back(server);
    auto vp = new VPoint(cx(pos.x), cy(pos.y));
    server->vp = vp;
    ver->push_back(vp);
    edg = v->GetEdges(ver, w, w);
}

void MainWindow::onStart() {

    // Load the assets
    droneId  = GlutWindow::loadTGATexture("../assets/drone.tga", 50, 50);
    serverId = GlutWindow::loadTGATexture("../assets/antenna.tga", 64, 64);

    // Creates a new drone
    drones.push_back(new Drone(Vector2(10, 10), droneId));

    v = new vor::Voronoi();
    ver = new vor::Vertices();

    vector<Server*> servers_loaded = loadConfig("../config_files/default_config.csv");
    if(!servers_loaded.empty()){
        for (auto server:servers_loaded){
            addServer(Vector2(server->position.x, server->position.y), server->name, server->color);
        }
    }else{
        addServer(Vector2(150, 250), "Server 1");
        addServer(Vector2(355, 255), "Server 2");
        addServer(Vector2(125, 400), "Server 3");
    }

    input = "Server";

    glClearColor(1.0,1.0,1.0,1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MainWindow::drawVoronoi()
{

    if (!ver->empty()) {

        edg = v->GetEdges(ver, w, w);

        /*for (auto & i : *ver) {
            glBegin(GL_QUADS);
            glColor3f(.75, .75,.95);
            glVertex2f( (-1 + 2*i->x/w - 0.01) * windowX,  (-1+2*i->y/w - 0.01) * windowY);
            glVertex2f( (-1 + 2*i->x/w + 0.01) * windowX,  (-1+2*i->y/w - 0.01) * windowY);
            glVertex2f( (-1 + 2*i->x/w + 0.01) * windowX,  (-1+2*i->y/w + 0.01) * windowY);
            glVertex2f( (-1 + 2*i->x/w - 0.01) * windowX,  (-1+2*i->y/w + 0.01) * windowY);
            glEnd();
        }*/

        for (auto & i : *edg) {
            glBegin(GL_LINES);
            glColor3f(.75, .75,.95);
            line(
                    (-1 + 2 * (i->start->x / w)) * windowX,
                    (-1 + 2 * (i->start->y / w)) * windowY,
                    (-1 + 2 * (i->end->x / w)) * windowX,
                    (-1 + 2 * (i->end->y / w)) * windowY
            );
            glEnd();
        }
    }

    glColor3f(0, 0,0);
    drawText(10, 10, "Vertices: " + to_string(ver->size()));
    drawText(10, 45, "Edges: " + to_string(edg->size()));

}

void MainWindow::onDraw() {

    drawVoronoi();

    glColor3f(1, .5,.5);
    for (Drone* drone : drones) {
        if (drone->server) {
            glPushMatrix();
            line(
                    drone->position.x,
                    drone->position.y,
                    drone->server->position.x,
                    drone->server->position.y
            );
            glPopMatrix();
        }
    }

    Server* hoveredServer = selectedServer;
    if (!hoveredServer) {
        for (Server* server : servers) {
            if (mousePos.magnitude(server->position) < (server->size + 10)) {
                hoveredServer = server;
            }
        }
    }
    if ((!inputWindowEnabled) && hoveredServer) {
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

    if (inputWindowEnabled) {
        drawInputWindow();
    }
}

void MainWindow::onUpdate(double dt) {

    tick++;

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

    float min;
    float current;
    Server* closest;
    for (Drone* drone : drones) {

        // Update the drones positions
        drone->onUpdate(avoidingForceForDrone(drone));

        min = (float) INT_MAX;
        closest = nullptr;
        for (Server* server : servers) {
            current = drone->position.magnitude(server->position);
            if (current < min) {
                min = current;
                closest = server;
            }
        }
        drone->server = closest;
    }

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

void MainWindow::onReshape(int x, int y) {
    // Locks screen dimensions
    glutReshapeWindow(windowX, windowY);
}


Vector2 MainWindow::avoidingForceForDrone(Drone* d) {
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

Vector2 MainWindow::clampToScreenDimensions(Vector2 v) {
    if (v.y > 10000) v.y = -1;
    float x = v.x;
    float y = v.y;
    if (x < (padding)) x = padding;
    if (x > (windowX - padding)) x = (windowX - padding);
    if (y < (padding)) y = padding;
    if (y > (windowY - padding)) y = (windowY - padding);
    return {x, y};
}

void MainWindow::onQuit() {}