//
// Created by vince on 19/12/2019.
//

#ifndef VITV_SND__H
#define VITV_SND__H
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

const int blank[3] = {255, 255, 255};
const int red[3] = {255, 0, 0};
const int orange[3] = {255, 165, 0};
const int yellow[3] = {255, 255, 0};
const int green[3] = {0, 255, 0};
const int cyan[3] = {0, 255, 255};
const int blue[3] = {0, 0, 255};
const int pink[3] = {255, 192, 203};
const int purple[3] = {128, 0, 128};
const int magenta[3] = {255, 0, 255};
const int grey[3] = {105, 105, 105};
const int brown[3] = {139, 69, 19};

class Colors {
public:

    /**
     * Compare the name of the color and return the rgb tab values to the associated color
     * @param name_color : name of the color
     * @return tab containing the rgb values of the color passed in param
     */
     // TODO: reformat the code with a switch and an enum
    static const int * getColorByString(string name_color);
};


#endif //VITV_SND_H
