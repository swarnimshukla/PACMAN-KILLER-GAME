#include "porcupine.h"
#include "main.h"

Porcupine::Porcupine(float x, float y, color_t color, int type) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    direction=1;
    if(type == 0){
        static const GLfloat g_vertex_buffer_data[] = {
            -5.3, -3.9, 0, // vertex 1
            -4.7,  -3.9, 0, // vertex 2
            -5,  -3.5, 0, // vertex 3
        };    
    this->object = create3DObject(GL_TRIANGLES, 3, g_vertex_buffer_data, color, GL_FILL);
    }
    else if( type == 1){
        static const GLfloat g_vertex_buffer_data[] = {
            -5.3, -3.9, 0, // vertex 1
            -5.9,  -3.9, 0, // vertex 2
            -5.6,  -3.5, 0, // vertex 3
        };    
    this->object = create3DObject(GL_TRIANGLES, 3, g_vertex_buffer_data, color, GL_FILL);
    }
    else if( type == 2){
         static const GLfloat g_vertex_buffer_data[] = {
                -5.9, -3.9, 0, // vertex 1
                -6.5,  -3.9, 0, // vertex 2
                -6.2,  -3.5, 0, // vertex 3
            };    
        this->object = create3DObject(GL_TRIANGLES, 3, g_vertex_buffer_data, color, GL_FILL);   
    }

}

void Porcupine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Porcupine::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Porcupine::tick() {
    if(direction ==1 ){
        position.x += 0.01;
        if(position.x >= 0.5)
            direction=0;
    }
    else if(direction == 0)
        position.x -= 0.01;
        if(position.x <= -0.873)
            direction=1;
}

bounding_box_t Porcupine::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
