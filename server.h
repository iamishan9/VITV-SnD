#ifndef SERVERS_AND_DRONES_SERVER_H
#define SERVERS_AND_DRONES_SERVER_H

#include <ostream>

#include "glutWindow.h"

#include "vector2d.h"

class Server {
public:
    Vector2D position;
    string name;
    string color;

    int size = 48;
    GLuint id = GlutWindow::loadTGATexture("../assets/antenna.tga", size, size);

    Server();
    Server(Vector2D position, std:: string name, std::string color);
    ~Server();
    void onDraw();
    //static void load_texture();
    friend std::ostream& operator << (std::ostream &out, const Server &s);
};



#endif //SERVERS_AND_DRONES_SERVER_H
