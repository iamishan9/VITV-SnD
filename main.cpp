#pragma once
#include <vector>

#include "glutWindow.h"
#include "src/Vector2.h"

class MainWindow: public GlutWindow {
public:

    MainWindow(const string &title,int argc,char **argv):
            GlutWindow(argc,argv,title,1000,500,FIXED) {
    };

    void onStart() override;
    void onDraw() override;
    void onQuit() override;
    void onMouseDown(int button, double x, double y) override;
    void onMouseMove(double x, double y) override;
    void onUpdate(double dt) override;
};

void MainWindow::onStart() {
    glClearColor(1.0,1.0,1.0,1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MainWindow::onUpdate(double dt) {}

void MainWindow::onDraw() {
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f,1.0f,1.0f);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

#define MB_LEFTCLICK 0
#define MB_RIGHTCLICK 2
void MainWindow::onMouseDown(int button, double x, double y) {
    if (button == MB_LEFTCLICK) {

    }
    if (button == MB_RIGHTCLICK) {

    }
}

void MainWindow::onMouseMove(double x, double y) {}

void MainWindow::onQuit() {}

int main(int argc, char **argv) {

    Vector2* myVector = new Vector2(1, 2);

    MainWindow win("Drones", argc, argv);
    win.start();
    return 0;
}