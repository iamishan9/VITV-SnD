//
// Created by tomde on 19/12/2019.
//
#include "MainWindow.h"
#include "HelperFile.h"

#define MB_LEFTCLICK 0
#define MB_RIGHTCLICK 2

#define KB_DEL 127
#define KB_BACKSPACE 8
#define KB_RETURN 13

bool isCloseButtonHovered(Vector2 mousePos, float windowX, float windowY) {
    return (
            (mousePos.x > (windowX * .5) + 165 - 30)
            && (mousePos.x < (windowX * .5) + 165)
            && (mousePos.y > (windowY * .5) + 80 - 30 + 1)
            && ((mousePos.y < (windowY * .5) + 80 + 1) )
    );
}

bool isDoneButtonHovered(Vector2 mousePos, float windowX, float windowY) {
    return (
            (mousePos.x > (windowX * .5) - 36)
            && (mousePos.x < (windowX * .5) + 36)
            && (mousePos.y < (windowY * .5) - 29)
            && (mousePos.y > (windowY * .5) - 70)
    );
}

bool isInputCorrect(const string& input) {
    return !input.empty();
}

void MainWindow::onMouseDown(int button, double x, double y) {
    if (button == MB_LEFTCLICK) {

        if (!inputWindowEnabled) {

            /* Don't prompt a server name if the user click on a server */
            for (Server* server : servers) {
                if (mousePos.magnitude(server->position) < (server->size + 10)) {
                    return;
                }
            }
            inputWindowEnabled = true;
            createServerAt = mousePos;
            return;
        }

        // Close button
        if (inputWindowEnabled && isCloseButtonHovered(mousePos, windowX, windowY)) {
            inputWindowEnabled = false;
            return;
        }

        // Done button
        if (inputWindowEnabled && isInputCorrect(input) && isDoneButtonHovered(mousePos, windowX, windowY)) {
            if (servers.size() < maxServers) {
                addServer(clampToScreenDimensions(createServerAt), input);
                input = "Server";
            }
            inputWindowEnabled = false;
        }
    }

    if (button == MB_RIGHTCLICK) {
    }
}

void MainWindow::onMouseUp(int button, double x, double y) {
    selectedServer = nullptr;
}

void MainWindow::onMouseMove(double x, double y) {
    mousePos = Vector2(x, y);
    if (inputWindowEnabled) return;
    for (Drone* drone : drones) {
        // drone->target = mousePos;
    }
}

void MainWindow::onMouseDrag(double x, double y) {
    onMouseMove(x, y);
    if (inputWindowEnabled) return;
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
        selectedServer->vp->x = cx(selectedServer->position.x);
        selectedServer->vp->y = cy(selectedServer->position.y);
    }
}

void MainWindow::onKeyPressed(unsigned char c, double x, double y) {
    if (inputWindowEnabled) {
        // TODO: Fix special characters like é à è not rendering properly
        if ((c != KB_BACKSPACE) && (c != KB_RETURN)) {
            // Make sure text fits
            if (glutBitmapLength( GLUT_BITMAP_HELVETICA_18, (unsigned char *) (input + char(int(c))).c_str()) < 290) {
                input = input + char(int(c));
            }
        }
        switch (c) {
            case KB_BACKSPACE:
                input = input.substr(0, input.size()-1);
                tick = 31; // Resets blink
                break;

            case KB_RETURN:
                if (!isInputCorrect(input)) return;
                if (servers.size() < maxServers) {

                    addServer(clampToScreenDimensions(createServerAt), input);
                    input = "Server";
                }
                inputWindowEnabled = false;
                break;

            default:
                break;
        }
        return;
    }
    switch (c) {
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
                            for (auto & i : *ver) {
                                if (i == mserver->vp) {
                                    ver->remove(i);
                                    break;
                                }
                            }
                            delete mserver->vp;
                        }
                    }
                    servers = tmp;

                    break;
                }
            }
            break;

        case 's': // Save the configuration in the file
            saveConfig(MyFile::csv_file, servers);
            break;

        case '1':
            for (Server* server : servers) {
                if (mousePos.magnitude(server->position) < (server->size + 10)) {
                    server->color = "red";
                }
            }
            break;

        case '2':
            for (Server* server : servers) {
                if (mousePos.magnitude(server->position) < (server->size + 10)) {
                    server->color = "orange";
                }
            }
            break;

        case '3':
            for (Server* server : servers) {
                if (mousePos.magnitude(server->position) < (server->size + 10)) {
                    server->color = "yellow";
                }
            }
            break;

        case '4':
            for (Server* server : servers) {
                if (mousePos.magnitude(server->position) < (server->size + 10)) {
                    server->color = "green";
                }
            }
            break;

        case '5':
            for (Server* server : servers) {
                if (mousePos.magnitude(server->position) < (server->size + 10)) {
                    server->color = "cyan";
                }
            }
            break;

        case '6':
            for (Server* server : servers) {
                if (mousePos.magnitude(server->position) < (server->size + 10)) {
                    server->color = "blue";
                }
            }
            break;

        case '7':
            for (Server* server : servers) {
                if (mousePos.magnitude(server->position) < (server->size + 10)) {
                    server->color = "pink";
                }
            }
            break;

        case '8':
            for (Server* server : servers) {
                if (mousePos.magnitude(server->position) < (server->size + 10)) {
                    server->color = "purple";
                }
            }
            break;

        case '9':
            for (Server* server : servers) {
                if (mousePos.magnitude(server->position) < (server->size + 10)) {
                    server->color = "magenta";
                }
            }
            break;

        case '0':
            for (Server* server : servers) {
                if (mousePos.magnitude(server->position) < (server->size + 10)) {
                    server->color = "grey";
                }
            }
            break;

        case '+':
            for (Server* server : servers) {
                if (mousePos.magnitude(server->position) < (server->size + 10)) {
                    server->color = "brown";
                }
            }
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

void MainWindow::drawInputWindow() {

    glPushMatrix();

    // Window's background
    glColor3f(.6,.6,.6);
    box(
            (windowX * .5) - 166,
            (windowY * .5) - 81,
            166 * 2,
            81 * 2
    );
    glColor3f(.8,.8,.8);
    box(
            (windowX * .5) - 165,
            (windowY * .5) - 80,
            165 * 2,
            80 * 2
    );

    // Top bar
    glColor3f(.5,.5,.8);
    box(
            (windowX * .5) - 165,
            (windowY * .5) + 80 - 30,
            165 * 2,
            30
    );
    glColor3f(1,1,1);
    GlutWindow::drawText(
            (windowX * .5) - 160,
            (windowY * .5) + 80 - 22,
            "Enter a name",
            GlutWindow::ALIGN_LEFT
    );

    // Close button
    if (isCloseButtonHovered(mousePos, windowX, windowY)) {
        glColor3f(1,.1,.1);
    } else {
        glColor3f(.9,.0,.0);
    }
    box(
            (windowX * .5) + 165 - 30,
            (windowY * .5) + 80 - 30 + 1,
            30,
            29
    );
    glColor3f(1,1,1);
    GlutWindow::drawText(
            (windowX * .5) + 165 - 15,
            (windowY * .5) + 80 - 22,
            "X",
            GlutWindow::ALIGN_CENTER
    );

    // Textfield
    glColor3f(.6,.6,.6);
    box(
            (windowX * .5) - 151,
            (windowY * .5) - 10,
            151 * 2,
            42
    );
    glColor3f(1,1,1);
    box(
            (windowX * .5) - 150,
            (windowY * .5) - 10,
            150 * 2,
            40
    );
    glColor3f(.0,.0,.0);
    GlutWindow::drawText(
            (windowX * .5) - 145,
            (windowY * .5),
            input,
            GlutWindow::ALIGN_LEFT,
            GLUT_BITMAP_HELVETICA_18
    );

    if ((tick % 60) > 30) { // Blink effect
        GlutWindow::drawText(
                (windowX * .5) - 144 + glutBitmapLength( GLUT_BITMAP_HELVETICA_18, (unsigned char *) input.c_str()),
                (windowY * .5) + 2,
                "|",
                GlutWindow::ALIGN_LEFT
        );
    }

    if (isInputCorrect(input)) {
        // Done button
        glColor3f(.6,.6,.6);
        box(
                (windowX * .5) - 36,
                (windowY * .5) - 66,
                36 * 2,
                37
        );
        if (isDoneButtonHovered(mousePos, windowX, windowY)) {
            glColor3f(.9,.9,.9);
        } else {
            glColor3f(.75,.75,.75);
        }

        box(
                (windowX * .5) - 35,
                (windowY * .5) - 65,
                35 * 2,
                35
        );
        glColor3f(.0,.0,.0);
        GlutWindow::drawText(
                (windowX * .5),
                (windowY * .5) - 55,
                "Done",
                GlutWindow::ALIGN_CENTER
        );
    }
    glPopMatrix();
}