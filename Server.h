//
// Created by Victor NAGY on 19/12/2019.
//

#ifndef VITV_SND_SERVER_H
#define VITV_SND_SERVER_H

#include <glutWindow.h>
#include "Vector2D.h"

class Server {
public:

    GLuint id; // TODO: Should be static

    float size = 30;

    Vector2D position;
    string name;

    /*
     * Creates a server at pos
     */
    Server(Vector2D pos, string label, GLuint textureId);

    /*
     * Called at each frame to render the server
     */
    void onDraw();
};


#endif //VITV_SND_SERVER_H
