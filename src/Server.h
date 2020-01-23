//
// Created by tomde on 18/12/2019.
//
#ifndef VITV_SND_SERVER_H
#define VITV_SND_SERVER_H

#include <vector>
#include "../glutWindow.h"
#include "Vector2.h"

#include "../voronoi/Voronoi.h"
#include "Drone.h"

class Server {
public:

    GLuint id; // TODO: Should be static

    float size = 30;

    Vector2 position;
    string name;

    VPoint* vp;

    string color;

    int nb_drones_max; // TODO : change the value of nb_drones in the constructors
    int current_nb_drones;
    std::vector<Drone*> drones;


    /**
     * Default constructor for a server
     */
    Server();


    /**
     * Creates a server at the pos ; Basic color of the server is blank
     * @param pos : position of the click
     * @param label : Name of the server
     * @param textureId : ID of the texture for the drag and drop
     */
    Server(Vector2 pos, string label, GLuint textureId);


    /**
     * Creates a server at the pos
     * @param pos : position of the server
     * @param label : Name of the server
     * @param color : color of the server
     */
    Server(Vector2 pos, string label, string color);


    /**
     * Creates a server at the pos with a color
     * @param pos : position of the server
     * @param label : Name of the server
     * @param textureId: ID of the texture for the drag and drop
     * @param color : color of the area of the server
     */
    Server(Vector2 pos, string label, GLuint textureId, string color);


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
    string returnStringForSave();


    /**
     * Set the number of drones giving by the field_area of the window and the zone area of the server
     * @param field_area : The area field of the window
     * @param zone_area : The area calculated for the server zone
     * @param total_drones : Total number of drones on the area
     */
    void setNumberOfDrones(double field_area, double zone_area, int total_drones);
};

#endif //VITV_SND_SERVER_H