//
// Created by tomde on 19/12/2019.
//
#ifndef VITV_SND_MAINWINDOW_H
#define VITV_SND_MAINWINDOW_H

#include <vector>

#include "../glutWindow.h"
#include "Vector2.h"
#include "Drone.h"
#include "Server.h"

#include "../voronoi/Voronoi.h"

class MainWindow: public GlutWindow {
public:

    double w = 10000;
    vor::Voronoi* v;
    vor::Vertices * ver;
    vor::Vertices * dir;
    vor::Edges * edg;

    int maxServers = 12;

    vector<Drone*> drones;
    vector<Server*> servers;

    GLuint droneId  = 0;
    GLuint serverId = 0;

    const static unsigned int windowX = 1000;
    const static unsigned int windowY = 800;

    Vector2 mousePos       = Vector2();
    Vector2 createServerAt = Vector2();

    MainWindow(const string &title, int argc, char **argv):
            GlutWindow(argc, argv, title, windowX, windowY, FIXED) {
    };

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

    void drawVoronoi();

    float avoidDronesRange = 125;
    float avoidForce       = 200;

    /*
     * Computes the force that should be applied in order
     * to avoid all drones in the avoidDronesRange
     */
    Vector2 avoidingForceForDrone(Drone* d);


    float padding = 25;

    /*
     * Prevents the user from placing a server outside the screen boundaries
     */
    Vector2 clampToScreenDimensions(Vector2 v);

    string input = "";
    bool inputWindowEnabled = false;
    int tick = 0; // Used to blink the cursor ; Not to be used for anything else

    /*
     * Draw the input window
     */
    void drawInputWindow();

    float cx(float v);
    float cy(float v);

    void addServer(Vector2 pos, string name);

    void addServer(Vector2 pos, string name, string color);
};

#endif //VITV_SND_MAINWINDOW_H