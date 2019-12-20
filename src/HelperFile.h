#ifndef VITV_SND_HELPERFILE_H
#define VITV_SND_HELPERFILE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Server.h"


/**
 * Load a config file with the descriptor
 * @param file : descriptor of file
 */
vector<Server*> loadConfig(std::ifstream &file);


/**
 * Load a config file with the path of the file
 * @param filePath : Path of the file
 */
vector<Server*> loadConfig(std::string filePath);


/**
 * Save the config file with the configuration on the window
 * Using the descriptor
 * @param file : Descriptor of file
 */
void saveConfig(std::ofstream &file, vector<Server*> servers);


/**
 * Save a config file with the configuration of the window
 * @param filePath : Path of the file
 */
void saveConfig(std::string filePath, vector<Server*> servers);

#endif //VITV_SND_HELPERFILE_H
