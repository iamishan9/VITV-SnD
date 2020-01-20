#pragma once
#include "src/MainWindow.h"
#include <algorithm>


/**
 *
 * @param begin
 * @param end
 * @param option
 * @return
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
 //TODO : Implementation of the -c option in the main program
int main(int argc, char **argv) {
    if(arg_is_option(argv, argv+argc, "-h")) {
        std::cout << "Two options are available for this program : " << std::endl;
        std::cout << "  -h : Give you the help for the different options ;" << std::endl;
        std::cout << "  -c name_file : Use a configuration file different thant the original one." << std::endl;
        return 1;

    }else if(arg_is_option(argv, argv+argc, "-c") && argc == 3){
        std::cout << "Usage of -c option" << std::endl;
        return 1;

    }else if(argc != 1){
        std::cout << "Usage of incorrect options." << std::endl;
        return -1;
    }

    MainWindow("Drones", argc, argv).start();
    return 0;
}