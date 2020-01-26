#include "config_manager.h"

vector<Server*> load_config(std::string file_path) {
    vector<Server*> servers;
    std::ifstream file(file_path);
    if (file.is_open()) {
        std::string line;
        size_t pos = 0;

        std::string s_name, s_Vector2D, s_Color, s_x, s_y;
        int x = INT32_MIN, y = INT32_MIN;

        int line_number = 0;
        bool is_line_valid = true;

        std::string delim = ";";

        std::cout << "File successfully opened!" << std::endl;
        while (getline(file, line)) {
        //std::cout << line << std::endl;

            line_number++;
            is_line_valid = true;
            pos = 0;
            s_name = "";
            s_Vector2D = "";
            s_Color = "";

            pos = line.find(delim);
            s_name = line.substr(0, pos);
            line.erase(0, pos + delim.length());

            pos = line.find(delim);
            s_Vector2D = line.substr(0, pos);
            line.erase(0, pos + delim.length());

            //s_Color = line.substr(0, line.length() - 1); // TODO if windows csv file: line.length() - 1 (\r\n)
            s_Color = line.substr(0, line.length());


            std::istringstream iss(s_Vector2D);
            ((iss.get() == '(') ? is_line_valid = true : is_line_valid = false); // remove '('
            iss >> x; // get x
            ((iss.get() == ',') ? is_line_valid = true : is_line_valid = false); // remove ','
            iss >> y; // get y
            ((iss.get() == ')') ? is_line_valid = true : is_line_valid = false); // remove ')'

            std::cout << s_name << " | " << x << " | " << y << " | " << s_Color << std::endl;

            if (is_line_valid && s_name != "" && s_Color != "" && x != INT32_MIN && y != INT32_MIN) {
                servers.push_back(new Server( Vector2D(x, y), s_name, s_Color ) );
            } else {
                std::cerr << "While reading file, line " << line_number << " was rejected!" << std::endl;
            }
        }
        file.close();

        return servers;
    } else {
        std::cerr << "Error while reading file!" << std::endl;
        return servers;
    }
}