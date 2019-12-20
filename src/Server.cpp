//
// Created by tomde on 18/12/2019.
//
#include "Server.h"
#include <utility>

Server::Server(Vector2 pos, string label, GLuint textureId) {
    position = pos;
    id = textureId;
    name = std::move(label);
    color = "blank";
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


string Server::returnStringForSave() {
    return this->name + " ; (" + to_string(int(this->position.x)) + "," + to_string(int(this->position.y)) + ") ; " + this->color;
}

Server::~Server() {
    delete this;
}