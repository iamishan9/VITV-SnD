#pragma once
#include "src/MainWindow.h"
#include "src/HelperFile.h"
#include <algorithm>


/**
 * Check if an option is inside the command line
 * @param begin : The begin of the tab of arguments
 * @param end : End of the tab of arguments
 * @param option : Option we want to see
 * @return True if the option is finded ; False otherwise
 */
char* arg_get_option(char **begin, char **end, const std::string &option) {
    char **it = std::find(begin, end, option);

    if (it != end && ++it != end)
        return *it;

    return 0;
}


/**
 * Test if an argument is an option for the program
 * @param begin : The begin of the tab of arguments
 * @param end : End of the tab of arguments
 * @param option : Option we want to see
 * @return True if the option is finded ; False otherwise
 */
bool arg_is_option(char** begin, char** end, const std::string& option) {
    return std::find(begin, end, option) != end;
}


/**
 * Main of the program
 * @param argc : number of arguments
 * @param argv : arguments
 * @return 0 for good exec ; 1 for the -h ; an another number otherwise
 */
int main(int argc, char **argv) {
    if(arg_is_option(argv, argv+argc, "-h")) {
        std::cout << "Two options are available for this program : " << std::endl;
        std::cout << "  -h : Give you the help for the different options ;" << std::endl;
        std::cout << "  -c name_file : Use a configuration file different thant the original one." << std::endl << std::endl;
        std::cout << "Some keyboard key are available during the execution of the program :" << std::endl;
        std::cout << "  s : Save the configuration in the file given" << std::endl;
        std::cout << "  Click : Add a server on the field" << std::endl;
        std::cout << "  del : Delete the selected server on the field" << std::endl;
        std::cout << "  d : Add a drone to the field" << std::endl;
        std::cout << "  1 : Change the color of the selected server to red" << std::endl;
        std::cout << "  2 : Change the color of the selected server to orange" << std::endl;
        std::cout << "  3 : Change the color of the selected server to yellow" << std::endl;
        std::cout << "  4 : Change the color of the selected server to green" << std::endl;
        std::cout << "  5 : Change the color of the selected server to cyan" << std::endl;
        std::cout << "  6 : Change the color of the selected server to blue" << std::endl;
        std::cout << "  7 : Change the color of the selected server to pink" << std::endl;
        std::cout << "  8 : Change the color of the selected server to purple" << std::endl;
        std::cout << "  9 : Change the color of the selected server to magenta" << std::endl;
        std::cout << "  0 : Change the color of the selected server to grey" << std::endl;
        std::cout << "  + : Change the color of the selected server to brown" << std::endl;
        return 1;

    }else if(arg_is_option(argv, argv+argc, "-c") && argc == 3){
        MyFile::csv_file = std::string("../config_files/") + argv[2];

    }else if(argc != 1){
        std::cout << "Usage of incorrect options." << std::endl;
        return -1;
    }

    MainWindow("Drones", argc, argv).start();
    return 0;
}