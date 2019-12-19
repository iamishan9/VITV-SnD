//
// Created by vince on 19/12/2019.
//

#include <iostream>
#include "Colors.h"


const int * Colors::getColorByString(string name_color){
    // Transform the upper caracters into lower caracters
    transform(name_color.begin(), name_color.end(), name_color.begin(), [](unsigned char c){
        return std::tolower(c);
    });


    if(name_color.compare("red") == 0){
        return red;
    }else if(name_color.compare("orange") == 0){
        return orange;
    }else if(name_color.compare("yellow") == 0){
        return yellow;
    }else if(name_color.compare("green") == 0){
        return green;
    }else if(name_color.compare("cyan") == 0){
        return cyan;
    }else if(name_color.compare("blue") == 0){
        return blue;
    }else if(name_color.compare("pink") == 0){
        return pink;
    }else if(name_color.compare("purple") == 0){
        return purple;
    }else if(name_color.compare("magenta") == 0){
        return magenta;
    }else if(name_color.compare("grey") == 0){
        return grey;
    }else if(name_color.compare("brown") == 0){
        return brown;
    }

    return blank;
}
