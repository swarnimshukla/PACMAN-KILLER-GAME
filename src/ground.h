#include "main.h"

#ifndef GROUND_H
#define GROUND_H

class Ground {
public:
    Ground() {}
    Ground(float x, float y, color_t color, int c );
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();

private:
    VAO *object;
};

#endif //GROUND_H
