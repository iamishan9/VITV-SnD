#pragma once
#include "src/MainWindow.h"

int main(int argc, char **argv) {
    MainWindow("Drones", argc, argv).start();
    return 0;
}