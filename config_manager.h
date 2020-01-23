#ifndef SERVERS_AND_DRONES_CONFIG_MANAGER_H
#define SERVERS_AND_DRONES_CONFIG_MANAGER_H


//#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "server.h"

const std::string DEFAULT_CONFIG = "../config/default.csv";

vector<Server*> load_config(std::string file_path);
void save_config(std::string file_path, vector<Server*> servers);


#endif //SERVERS_AND_DRONES_CONFIG_MANAGER_H
