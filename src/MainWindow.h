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

    const static unsigned int windowX = 800;
    const static unsigned int windowY = 500;

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

    float avoidDronesRange = 125; // The detection radius around a drone for other drones
    float avoidForce       = 200; // A base multiplier for the avoidForce

    /**
     * Computes the force that should be applied in order
     * to avoid all drones in the avoidDronesRange
     * @param d : The drone the avoidForce is computed for
     * @returns the avoided force
     */
    Vector2 avoidingForceForDrone(Drone* d);

    /**
     * Prevents the user from placing a server outside the screen boundaries
     * @param v : The raw value
     * @returns the clamped value
     */
    Vector2 clampToScreenDimensions(Vector2 v);

    float padding = 25; // The clamp padding, should be half a server width

    //draw patate
    void patate(float x, float y);
    Vector2 convert(float x, float y);

    /**
     * Render the input window
     */
    void drawInputWindow();

    string input = "";
    bool inputWindowEnabled = false;
    int tick = 0; // Used to blink the cursor ; Not to be used for anything else


    /**
     * To be removed
     */
    float cx(float v);
    float cy(float v);

    /**
     * Creates a server instance in the workspace
     * @param : pos Position
     * @param : name Name
     */
    void addServer(Vector2 pos, string name);

    /**
     * Creates a server instance in the workspace
     * @param : pos Position
     * @param : name Name
     * @param : color Color
     */
    void addServer(Vector2 pos, string name, string color);
};

#endif //VITV_SND_MAINWINDOW_H