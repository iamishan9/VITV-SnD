//
// Created by vince on 20/12/2019.
//

#ifndef VITV_SND_HELPERFILE_H
#define VITV_SND_HELPERFILE_H

#include <iostream>
#include <fstream>
#include <sstream>

/**
 * Load a config file with the descriptor
 * @param file : descriptor of file
 */
void loadConfig(std::ifstream &file);


/**
 * Load a config file with the path of the file
 * @param filePath : Path of the file
 */
void loadConfig(std::string filePath);


/**
 * Save the config file with the configuration on the window
 * Using the descriptor
 * @param file : Descriptor of file
 */
void saveConfig(std::ifstream &file);


/**
 * Save a config file with the configuration of the window
 * @param filePath : Path of the file
 */
void saveConfig(std::string filePath);

#endif //VITV_SND_HELPERFILE_H
