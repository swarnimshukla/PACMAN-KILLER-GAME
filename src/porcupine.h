#include "main.h"

#ifndef PORCUPINE_H
#define PORCUPINE_H


class Porcupine{
public:
    Porcupine() {}
    Porcupine(float x, float y, color_t color, int type);
    glm::vec3 position;
    int direction;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // PORCUPINE_H
