#include "main.h"

#ifndef POOL_H
#define POOL_H

class Pool {
public:
    Pool() {}
    Pool(float x, float y, color_t color, int c );
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();

private:
    VAO *object;
};

#endif //POOL_H
