#include "server.h"

#include <fstream>
#include <ostream>

#include "server.h"

Server::Server()
    : position(Vector2D())
    , name("")
    , color("WHITE")
{}

Server::Server(Vector2D position_, string name_, string color_)
    : position(position_)
    , name(name_)
    , color(color_)
{}

Server::~Server() {
    delete this;
}

void Server::onDraw() {
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
    glEnable(GL_TEXTURE_2D);
}

std::ostream& operator << (std::ostream &out, const Server &s) {
    out << "Name: " << s.name << " | " << s.position << ")" << s.color;
    return out;
}
