//
// Created by tomde on 19/12/2019.
//
#include "MainWindow.h"

// Define keys and buttons
#define MB_LEFTCLICK 0
#define MB_RIGHTCLICK 2
#define KB_DEL 127
#define KB_BACKSPACE 8

void MainWindow::onMouseDown(int button, double x, double y) {
    if (button == MB_LEFTCLICK) {

    }
    if (button == MB_RIGHTCLICK) {
        if (servers.size() < maxServers) {
            servers.push_back(new Server(clampToScreenDimensions(mousePos), "Demo", serverId));
        }
    }
}

void MainWindow::onMouseUp(int button, double x, double y) {
    selectedServer = nullptr;
}

void MainWindow::onMouseMove(double x, double y) {
    mousePos = Vector2(x, y);
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

void MainWindow::onKeyPressed(unsigned char c, double x, double y) {
    switch(c) {
        case 'd':
            drones.push_back(new Drone(Vector2(10, 10), droneId));
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

        default:
            break;
    }
    glutPostRedisplay();
}

void MainWindow::drawInputWindow() {

}