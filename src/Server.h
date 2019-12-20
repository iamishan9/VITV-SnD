//
// Created by tomde on 18/12/2019.
//
#ifndef VITV_SND_SERVER_H
#define VITV_SND_SERVER_H

#include "../glutWindow.h"
#include "Vector2.h"

#include "../voronoi/Voronoi.h"

class Server {
public:

    GLuint id; // TODO: Should be static

    float size = 30;

    Vector2 position;
    string name;

    VPoint* vp;

    /*
     * Creates a server at pos
     */
    Server(Vector2 pos, string label, GLuint textureId);

    /*
     * Called at each frame to render the server
     */
    void onDraw();
};

#endif //VITV_SND_SERVER_H