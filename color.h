#ifndef SERVERS_AND_DRONES_COLOR_H
#define SERVERS_AND_DRONES_COLOR_H


const float BLANK[4] = {1.0f, 1.0f, 1.0f, 1.0f};
const float BLACK[4] = {0.0,0.0,0.0,1.0f};
const float BLUE[4] = {0.0,0.0,1.0f,1.0f};
const float BROWN[4] = {0.55f, 0.27f, 0.07f, 1.0f};
const float CYAN[4] = {0.0f,1.0f,1.0f,1.0f};
const float GREEN[4] = {0.0,1.0f,0.0,1.0f};
const float GREY[4] = {0.75f,0.75f,0.75f,1.0f};
const float MAGENTA[4] = {1.0f,0.0f,1.0f,1.0f};
const float ORANGE[4] = {1.0f,0.27f,0.0,1.0f};
const float PINK[4] = {1.0f, 0.75f, 0.8f, 1.0f};
const float PURPLE[4] = {0.5f, 0.0f, 0.5f, 1.0f};
const float RED[4] = {1.0f,0.0,0.0,1.0f};
const float YELLOW[4] = {1.0f,1.0f,0.0,1.0f};

const float* stringToColor(const std::string &color);

#endif //SERVERS_AND_DRONES_COLOR_H
