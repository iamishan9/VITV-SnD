#include <fstream>
#include "Server.h"

Server::Server(Vector2D pos, string label, GLuint textureId) {
    position = pos;
    id = textureId;
    name = std::move(label);
}

// name;(x,y);colorname
/*Server::Server(std::ifstream &file, const std::string &delim) {

    if ( file.is_open() ) {
        std::string line;
        std::cout << "File successfully opened!" << std::endl;
        while ( getline(file, line) ) {
            //std::cout << line << std::endl;

            size_t pos = 0;
            string sName, sVector, sColorname;

            pos = line.find(delim);
            sName = line.substr(0, pos);
            line.erase(0, pos + delim.length());

            pos = line.find(delim);
            sVector = line.substr(0, pos);
            line.erase(0, pos + delim.length());

            sColorname = line.substr(0, line.length() - 1);

            //std::cout << sName << " | " << sVector << " | " << sColorname << std::endl;

            //insert(new Server(sName, Vector2D(x,y), sColorname));
        }
        file.close();
    }
    else {
        std::cerr << "Error while reading file!" << std::endl;
    }
}*/

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