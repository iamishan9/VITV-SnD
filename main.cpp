#include <iostream>
#include <vector>

#include "glutWindow.h"

#include "color.h"
#include "config_manager.h"
#include "server.h"
#include "vector2d.h"
#include "geometric_algorithms.h"
#include "geometry.h"

class MainWindow: public GlutWindow {
public:
    const static unsigned int WINDOW_X = 1000;
    const static unsigned int WINDOW_Y = 800;



    vector<Server*> servers;
    Polygon convex_hull;
    Mesh mesh;

    MainWindow(const string &title, int argc, char **argv):
            GlutWindow(argc, argv, title, WINDOW_X, WINDOW_Y, FIXED) {
    };

    void onStart() override;
    void onDraw() override;
    void onQuit() override;
    void onMouseDown(int button, double x, double y) override;
    void onMouseUp(int button, double x, double y) override;
    void onMouseDrag(double x, double y) override;
    void onMouseMove(double x, double y) override;
    void onKeyPressed(unsigned char c, double x, double y) override;
    void onReshape(int x, int y) override;
    void onUpdate(double dt) override;

};

void MainWindow::onStart() {
    std::cout << "onStart: begin" << std::endl;
    servers = load_config(DEFAULT_CONFIG);

    std::vector<Vector2D> points;

    for(auto server : servers) {
        points.push_back(server->position);
    }

    std::cout << "onStart: config read" << std::endl;

    // Graham

    std::vector<Vector2D> test;
    test.emplace_back(Vector2D(221, 128));
    test.emplace_back(Vector2D(141, 652));
    test.emplace_back(Vector2D(414, 406));
    test.emplace_back(Vector2D(876, 569));
    test.emplace_back(Vector2D(532, 756));
    test.emplace_back(Vector2D(690, 210));

    //convex_hull = Polygon(graham(test));
    convex_hull = Polygon(graham(points));

//    for (auto v : convex_hull.vertices) {
//        std:cout << v << endl;
//    }

//    std::cout << " Nb of sv: " << convex_hull.n_edges << endl;

    // Delaunay

    mesh = Mesh(points);

    for (auto triangle : mesh.triangles) {
        std::cout << "p1: " << *(triangle.ptr[0]) << "p2: " << triangle.ptr[1] << "p3: " << triangle.ptr[2] << std::endl;
    }



    // Voronoi

    glClearColor(1.0,1.0,1.0,1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::cout << "onStart: end" << std::endl;
}

void MainWindow::onDraw() {
    //std::cout << "onDraw begin" << std::endl;

    glPushMatrix();
    glTranslatef(10,10,0);
    glColor3fv(RED);
    glBegin(GL_QUADS);
    glVertex2f(0.0,-2.0);
    glVertex2f(100.0,-2.0);
    glVertex2f(100.0,2.0);
    glVertex2f(0.0,2.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(110.0,0.0);
    glVertex2f(90.0,-10.0);
    glVertex2f(90.0,10.0);
    glEnd();
    glColor3fv(GREEN);
    glBegin(GL_QUADS);
    glVertex2f(-2.0,0.0);
    glVertex2f(2.0,0.0);
    glVertex2f(2.0,100.0);
    glVertex2f(-2.0,100.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0,110.0);
    glVertex2f(-10.0,90.0);
    glVertex2f(10.0,90.0);
    glEnd();
    glPopMatrix();



/*    glPushMatrix();
    convex_hull.onDraw();
    glPopMatrix();*/

    glPushMatrix();
    mesh.onDraw();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f,1.0f,1.0f);
    for (Server* server : servers) {
        glPushMatrix();
        server->onDraw();
        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);

    //std::cout << "onDraw: end" << std::endl;
}

void MainWindow::onReshape(int x, int y) {
    // Locks screen dimensions
    glutReshapeWindow(WINDOW_X, WINDOW_Y);
}

void MainWindow::onMouseDown(int button, double x, double y){}
void MainWindow::onMouseUp(int button, double x, double y){}
void MainWindow::onMouseDrag(double x, double y){}
void MainWindow::onMouseMove(double x, double y){}
void MainWindow::onKeyPressed(unsigned char c, double x, double y){}
void MainWindow::onUpdate(double dt){}

void MainWindow::onQuit() {}

int main(int argc, char **argv) {
    std::cout << "Hello, World!" << std::endl;
    MainWindow("Drones", argc, argv).start();
    std::cout << "Good bye, World!" << std::endl;
    return 0;
}