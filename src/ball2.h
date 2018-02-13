#include "main.h"

#ifndef BALL2_H
#define BALL2_H


class Ball2 {
public:
    Ball2() {}
    Ball2(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double px;
    double gravity;
    int state;
    int flag;
    float magnet_speed;
    double v,u;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL2_H
