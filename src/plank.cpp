#include "plank.h"
#include "main.h"

Plank::Plank(float x, float y, color_t color) {
    printf("%lf %lf\n", x, y);
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

         GLfloat g_vertex_buffer_data[] = {
            1, 0, 0, // vertex 1
            -1,  0, 0, // vertex 2
            1,  0.3, 0, // vertex 3

            -1, 0.3, 0, // vertex 1
            1,  0.3, 0, // vertex 2
            -1,  0, 0, // vertex 3
    };
    this->object = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, color, GL_FILL);
    
}

void Plank::draw(glm::mat4 VP) {
   Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(-0.4, 0.16, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Plank::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plank::tick() {
    this->position.x -= speed;

    
}

bounding_box_t Plank::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
