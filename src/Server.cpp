//
// Created by tomde on 18/12/2019.
//
#include "Server.h"
#include <utility>
#include "../glutWindow.h"

Server::Server(){}

Server::Server(Vector2 pos, string label, GLuint textureId) {
    position = pos;
    id = textureId;
    name = std::move(label);
    color = "blank";
    nb_drones_max = 2; // To delete
    current_nb_drones = 0;
}

Server::Server(Vector2 pos, string label, GLuint textureId, string color_name) {
    position = pos;
    id = textureId;
    name = std::move(label);
    color = color_name;
    nb_drones_max = 2; // To delete
    current_nb_drones = 0;
}

Server::Server(Vector2 pos, string label, string color_name) {
    position = pos;
    name = std::move(label);
    color = color_name;
    nb_drones_max = 2; // To delete
    current_nb_drones = 0;
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

    // TODO : Delete this
    GlutWindow::line(position.x + 100, position.y + 100, position.x - 100, position.y + 100);
    GlutWindow::line(position.x + 100, position.y + 100, position.x + 100, position.y - 100);
    GlutWindow::line(position.x + 100, position.y - 100, position.x - 100, position.y - 100);
    GlutWindow::line(position.x - 100, position.y - 100, position.x - 100, position.y + 100);

    glEnable(GL_TEXTURE_2D);
}


string Server::returnStringForSave() {
    return this->name + ";(" + to_string(int(this->position.x)) + "," + to_string(int(this->position.y)) + ");" + this->color;
}


Server::~Server() {
    delete this;
}


void Server::setNumberOfDrones(double field_area, double zone_area, int total_drones){
    nb_drones_max = (int) ((field_area / zone_area) * total_drones);
}

void onDraw() {

}
