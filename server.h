#ifndef SERVERS_AND_DRONES_SERVER_H
#define SERVERS_AND_DRONES_SERVER_H

#include <ostream>

#include "glutWindow.h"

#include "vector2d.h"
#include "geometry.h"



class Server {
public:
    Vector2D position;
    std::string name;
    std::string color;
    Polygon field;

    int size = 48;
    GLuint id = GlutWindow::loadTGATexture("../assets/antenna.tga", size, size);

    Server();
    //Server(const Server &other);
    Server(Vector2D position, std::string name, std::string color);
    ~Server();

    //Server& operator=(const Server &other);

    void onDraw();
    //void initField();
    friend std::ostream& operator<<(std::ostream &out, const Server &s);
};



#endif //SERVERS_AND_DRONES_SERVER_H
