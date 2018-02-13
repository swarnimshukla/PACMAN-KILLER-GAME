#include "main.h"
#include "ground.h"

Ground::Ground(float x, float y, color_t color, int c ) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    if(c==0){
        static const GLfloat vertex_buffer_data[] = {
            -100, -100, 0, // vertex 1
            100,  -100, 0, // vertex 2
            100,  -5.5, 0, // vertex 3
    
            100,  -5.5, 0, // vertex 3
            -100, -100, 0, // vertex 4
            -100, -5.5, 0 // vertex 1
        };
        this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
    }
    else if(c==1) {
        static const GLfloat vertex_buffer_data[] = {
            100, -5.5, 0, // vertex 1
            100,  -4.5, 0, // vertex 2
            -100,  -5.5, 0, // vertex 3
    
            100,  -4.5, 0, // vertex 3
            -100, -4.5, 0, // vertex 4
            -100, -5.5, 0 // vertex 1
        };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
    }
    else if(c==2){
        static const GLfloat vertex_buffer_data[] = {
            3, -4.5, 0, // vertex 1
            3.2,  -4.5, 0, // vertex 2
            3.2,  -3.5, 0, // vertex 3
    
            3.2,  -3.5, 0, // vertex 3
            3, -4.5, 0, // vertex 4
            3, -3.5, 0 // vertex 1
        };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
    }
    else if(c==3){
        static const GLfloat vertex_buffer_data[] = {
            4.5, -4.5, 0, // vertex 1
            4.7,  -4.5, 0, // vertex 2
            4.7,  -3.5, 0, // vertex 3
    
            4.7,  -3.5, 0, // vertex 3
            4.5, -4.5, 0, // vertex 4
            4.5, -3.5, 0 // vertex 1
        };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
    }
    // else if(c==4){
    //     static const GLfloat vertex_buffer_data[] = {
    //         8, 8, 0, // vertex 1
    //         8,  -4.5, 0, // vertex 2
    //         -8,  -4.5, 0, // vertex 3
        
    //         -8,  8, 0, // vertex 3
    //         8, 8, 0, // vertex 4
    //         -8, -4.5, 0 // vertex 1
    //        };
    //     this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);   
    // } 
}

void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0 , 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ground::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


bounding_box_t Ground::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
