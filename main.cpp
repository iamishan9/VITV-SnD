#include <iostream>
#include <vector>

#include "glutWindow.h"
#include "color.h"
#include "config_manager.h"
#include "geometric_algorithms.h"
#include "geometry.h"
#include "server.h"
#include "vector2d.h"


class MainWindow: public GlutWindow {
public:
    const static unsigned int WINDOW_X = 1000;
    const static unsigned int WINDOW_Y = 800;

    std::vector<Server*> servers;
    Mesh mesh;
    Polygon convex_hull;
    Server *server;
    std::vector<Polygon> voronoi_polygons;

    std::vector<Vector2D> points;

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
    std::cout << "\nonStart: begin\n" << std::endl;
    //servers = load_config(DEFAULT_CONFIG);
    servers = load_config("../config/config_1.csv");


    for(auto &server : servers) {
        points.push_back(server->position);
    }

    // Graham

    convex_hull = Polygon(graham(points));

    // Delaunay

    mesh = Mesh(points); // mesh initialization with server position

    delaunay(&mesh);   // OR // mesh.solveDelaunay();

    // Voronoi

    voronoi_polygons = voronoi(mesh);



    //////////////////////////////////////////////////////////////////////////////

    // SOME TESTS

//    server = new Server(Vector2D(400,400), "HELLO", "GREEN");
//    server->field = Polygon(convex_hull);


    //////////////////////////////////////////////////////////////////////////////


    glClearColor(1.0,1.0,1.0,1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::cout << "\nonStart: end\n" << std::endl;
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

    //convex_hull.onDraw();
    //convex_hull.onDraw(PURPLE);
    //mesh.onDraw();

    //server->onDraw();

    for (auto &polygon : voronoi_polygons) {
        polygon.onDraw();
    }


    glColor3f(1.0f,1.0f,1.0f);

    for (const auto &server : servers) {
        server->onDraw();
    }

//    for (const auto &drone : drones) {
//        drone->onDraw();
//    }

} // end MainWindow::onDraw()

void MainWindow::onReshape(int x, int y) {
    // Locks screen dimensions
    glutReshapeWindow(WINDOW_X, WINDOW_Y);
}

void MainWindow::onMouseDown(int button, double x, double y){}
void MainWindow::onMouseUp(int button, double x, double y){}
void MainWindow::onMouseDrag(double x, double y){}

void MainWindow::onMouseMove(double x, double y){
    Vector2D v((float)x,(float)y);

    for (auto &triangle : mesh.triangles) {
        triangle.onMouseMove(v);
    }
}

void MainWindow::onKeyPressed(unsigned char c, double x, double y){}
void MainWindow::onUpdate(double dt){}

void MainWindow::onQuit() {}

int main(int argc, char **argv) {
    std::cout << "Hello, World!" << std::endl;
    MainWindow("Drones", argc, argv).start();
    std::cout << "Good bye, World!" << std::endl;
    return 0;
}