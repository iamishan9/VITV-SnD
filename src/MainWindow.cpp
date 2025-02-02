//
// Created by tomde on 19/12/2019.
//
#include <climits>
#include "MainWindow.h"
#include "HelperFile.h"
#include "Colors.h"

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

    vector<Server*> servers_loaded = loadConfig(MyFile::csv_file);
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

Vector2 MainWindow::convert(float x, float y) {
    return Vector2(
            (-1 + 2 * (x / w)) * windowX,
            (-1 + 2 * (y / w)) * windowY);
}

Server* MainWindow::getClosestServerFromPoint(Vector2 p) {
    Server* closest = nullptr;
    float min = 99999;
    for (Server* serv : servers) {
        if (serv->position.magnitude(p) < min) {
            min = serv->position.magnitude(p);
            closest = serv;
        }
    }
    return closest;
}

void MainWindow::drawVoronoi() {

    if (!ver->empty()) {

        edg = v->GetEdges(ver, w, w);

        Server* closestToTopRight = getClosestServerFromPoint(Vector2(windowX, windowY));
        Server* closestToTopLeft = getClosestServerFromPoint(Vector2(0, windowY));
        Server* closestToBottomLeft = getClosestServerFromPoint(Vector2(0, 0));
        Server* closestToBottomRight = getClosestServerFromPoint(Vector2(windowX, 0));

        if (true) {
            VPoint *serverPlace;
            Server *monServeur;
            for (auto i : *ver) {
                serverPlace = i;
                for (Server *s : servers) {
                    if (s->vp->isEqual(*i)) {
                        //cout << s->name << endl;
                        monServeur = s;
                        vector<Vector2> serverPolygonPoints;
                        for (auto &i : *edg) {
                            if (i->left == serverPlace) {
                                serverPolygonPoints.push_back(
                                        convert(i->start->x, i->start->y)
                                );
                                serverPolygonPoints.push_back(
                                        convert(i->end->x, i->end->y)
                                );
                            }
                            if (i->right == serverPlace) {
                                serverPolygonPoints.push_back(
                                        convert(i->start->x, i->start->y)
                                );
                                serverPolygonPoints.push_back(
                                        convert(i->end->x, i->end->y)
                                );
                            }
                        }

                        if (s == closestToTopRight) {
                            serverPolygonPoints.push_back(Vector2(windowX, windowY));
                        }

                        if (s == closestToTopLeft) {
                            serverPolygonPoints.push_back(Vector2(0, windowY));
                        }

                        if (s == closestToBottomLeft) {
                            serverPolygonPoints.push_back(Vector2(0, 0));
                        }

                        if (s == closestToBottomRight) {
                            serverPolygonPoints.push_back(Vector2(windowX, 0));
                        }

                        auto color = Colors::getColorByString(monServeur->color);
                        glColor3f(color[0] / 255.0, color[1] / 255.0, color[2] / 255.0);
                        for (int i = 0; i < serverPolygonPoints.size(); i++) {
                            for (int j = 0; j < serverPolygonPoints.size(); j++) {
                                for (int k = 0; k < serverPolygonPoints.size(); k++) {
                                    glBegin(GL_TRIANGLES);
                                    glVertex2f(
                                            serverPolygonPoints[i].x,
                                            serverPolygonPoints[i].y
                                    );
                                    glVertex2f(
                                            serverPolygonPoints[j].x,
                                            serverPolygonPoints[j].y
                                    );
                                    glVertex2f(
                                            serverPolygonPoints[k].x,
                                            serverPolygonPoints[k].y
                                    );
                                    glEnd();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for (auto & i : *edg) {
        glBegin(GL_LINES);
        glColor3f(0, 0,0);
        line(
                (-1 + 2 * (i->start->x / w)) * windowX,
                (-1 + 2 * (i->start->y / w)) * windowY,
                (-1 + 2 * (i->end->x / w)) * windowX,
                (-1 + 2 * (i->end->y / w)) * windowY
        );
        glEnd();
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

    for (Server* server : servers) {
        server->dronesConnected = 0;
    }
    for (Drone* drone : drones) {
        if (drone->server) {
            drone->server->dronesConnected++;
        }
    }

    double desiredAmountOfDronesPerServer = 1.0 * drones.size() / (servers.size() + .00001);
    //cout << (desiredAmountOfDronesPerServer) << endl;

    for (Drone* drone : drones) {

        // Update the drones positions
        drone->onUpdate(avoidingForceForDrone(drone));

        min = (float) INT_MAX;
        closest = nullptr;
        for (Server* server : servers) {
            current = drone->position.magnitude(server->position);
            if (current < min) {
                if ((server->dronesConnected * 1.0) <= desiredAmountOfDronesPerServer) {
                    min = current;
                    closest = server;
                }
            }
        }
        if (closest) {
            drone->server = closest;
            drone->target = closest->position;
        }
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