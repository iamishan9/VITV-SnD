#include <iostream>
#include <fstream>
#include <sstream>

void readFile(std::ifstream &file) {

    if ( file.is_open() ) {
        std::string line;
        size_t pos = 0;

        std::string sName, sVector2D, sColor, sX, sY;
        int x = INT32_MIN, y = INT32_MIN;

        int lineNumber = 0;
        bool isValidLine = true;

        std::string delim = ";";

        std::cout << "File successfully opened!" << std::endl;
        while ( getline(file, line) ) {
            //std::cout << line << std::endl;

            lineNumber++;
            isValidLine = true;
            pos = 0;
            sName = "";
            sVector2D = "";
            sColor = "";

            pos = line.find(delim);
            sName = line.substr(0, pos);
            line.erase(0, pos + delim.length());

            pos = line.find(delim);
            sVector2D = line.substr(0, pos);
            line.erase(0, pos + delim.length());

            //sColor = line.substr(0, line.length() - 1); // TODO if windows csv file: line.length() - 1 (\r\n)
            sColor = line.substr(0, line.length());


            std::istringstream iss(sVector2D);
            ( (iss.get() == '(' ) ? : isValidLine = false ); // remove '('
            iss >> x; // get x
            ( (iss.get() == ',' ) ? : isValidLine = false ); // remove ','
            iss >> y; // get y
            ( (iss.get() == ')' ) ? : isValidLine = false ); // remove ')'

            //std::cout << sName << " | " << sVector2D << " | " << sColor << std::endl;
            std::cout << sName << " | " << x << " | " << y << " | " << sColor << std::endl;

            if(isValidLine && sName != "" && sColor != "" && x != INT32_MIN && y != INT32_MIN) {
                //insert(new Server(sName, Vector2D(x,y), sColor));
            }
            else {
                std::cerr << "While reading file, line " << lineNumber << " was rejected!" << std::endl;
            }
        }
        file.close();
    }
    else {
        std::cerr << "Error while reading file!" << std::endl;
    }
}

void readFile(std::string filePath) {
    std::ifstream fileServers(filePath);
    readFile(fileServers);
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::ifstream fileServers("../dataset_servers.csv");
    readFile(fileServers);

    // OR

    //readFile("../dataset_servers.csv");


    std::cout << "Good bye, World!" << std::endl;
    return 0;
}