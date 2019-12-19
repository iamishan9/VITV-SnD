//
// Created by tomde on 18/12/2019.
//
#ifndef VITV_SND_SERVER_H
#define VITV_SND_SERVER_H

#include "../glutWindow.h"
#include "Vector2D.h"

class Server {
public:

    GLuint id; // TODO: Should be static
    float size = 30;
    Vector2D position;
    string name;
    // TODO : Add a color to the server

    /**
     * Creates a server at the pos
     * @param pos : position of the click
     * @param label : Name of the server
     * @param textureId : ID of the texture for the drag and drop
     */
    Server(Vector2D pos, string label, GLuint textureId);


    /**
     * Deletion of a server
     */
    ~Server();


    /**
     * Called at each frame to render the server
     */
    void onDraw();


    /**
     * Return the informations of the server in string
     * @return string containing the values to write in the configuration file
     */
     // TODO: Add the color to the return
    string returnStringForSave();
};

#endif //VITV_SND_SERVER_H