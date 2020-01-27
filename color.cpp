#include <string>
#include "color.h"

const float* stringToColor(const std::string &color) {

    if (color == "RED"){
        return RED;
    } else if(color == "ORANGE") {
        return ORANGE;
    } else if(color == "YELLOW") {
        return YELLOW;
    } else if(color == "GREEN") {
        return GREEN;
    } else if(color == "CYAN") {
        return CYAN;
    } else if(color == "BLUE") {
        return BLUE;
    } else if(color == "PINK") {
        return PINK;
    } else if(color == "PURPLE") {
        return PURPLE;
    } else if(color == "MAGENTA") {
        return MAGENTA;
    } else if(color == "GREY") {
        return GREY;
    } else if(color == "BROWN;") {
        return BROWN;
    }

    return BLANK;
}