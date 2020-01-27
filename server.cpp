#include "server.h"

#include <fstream>
#include <ostream>

#include "server.h"
#include "color.h"

Server::Server()
    : position(Vector2D())
    , name("")
    , color("BLANK")
    , field(Polygon())
{}

//Server::Server(const Server &other)
//    : position(other.position)
//    , name(other.name)
//    , color(other.color)
//    , field(other.field)
//{}

Server::Server(Vector2D position_, string name_, string color_)
    : position(position_)
    , name(name_)
    , color(color_)
    , field(Polygon())
{}

Server::~Server() {
    delete this;
}

//Server& Server::operator=(const Server &other) {
//    position = other.position;
//    name = other.name;
//    color = other.color;
//    field = other.field;
//    return *this;
//}

void Server::onDraw() {
    const float *fcolor = stringToColor(color);
    field.onDraw(fcolor);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, id);
    glPushMatrix();
    glTranslatef(position.x - (size / 2), position.y - (size / 2), 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(size,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(size, size);
    glTexCoord2f(0.0,1.0);
    glVertex2f(0.0, size);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glColor3f(0.0f,0.0f,0.0f);
    GlutWindow::drawText(
            position.x,
            position.y - (size + 5),
            name,
            GlutWindow::ALIGN_CENTER
    );
}

std::ostream& operator<<(std::ostream &out, const Server &s) {
    out << "Name: " << s.name << " | " << s.position << "|" << s.color;
    return out;
}
