#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, color_t color, int type) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    if(type==0){
         int pos=0,i,j,n=100;
            GLfloat g_vertex_buffer_data[9*n];
            float pi = 3.14159, angle = -1.5*pi, rot=(pi)/(n);
            for(i=0;i<n;i++){
                g_vertex_buffer_data[pos++]= 0.0f;
                g_vertex_buffer_data[pos++]= 0.0f;
                g_vertex_buffer_data[pos++]= 0.0f;
                g_vertex_buffer_data[pos++]= cos(angle)*1.3;
                g_vertex_buffer_data[pos++]= sin(angle)*1.3;
                g_vertex_buffer_data[pos++]= 0.0f;
                angle += rot;
                g_vertex_buffer_data[pos++]= cos(angle)*1.3;
                g_vertex_buffer_data[pos++]= sin(angle)*1.3;
                g_vertex_buffer_data[pos++]= 0.0f;
        }
            this->object = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data, color, GL_FILL);
    }
    else if(type==1){
     int pos=0,i,j,n=100;
            GLfloat g_vertex_buffer_data[9*n];
            float pi = 3.14159, angle = -1.5*pi, rot=(pi)/(n);
            for(i=0;i<n;i++){
                g_vertex_buffer_data[pos++]= 0.0f;
                g_vertex_buffer_data[pos++]= 0.0f;
                g_vertex_buffer_data[pos++]= 0.0f;
                g_vertex_buffer_data[pos++]= cos(angle)*1;
                g_vertex_buffer_data[pos++]= sin(angle)*1;
                g_vertex_buffer_data[pos++]= 0.0f;
                angle += rot;
                g_vertex_buffer_data[pos++]= cos(angle)*1;
                g_vertex_buffer_data[pos++]= sin(angle)*1;
                g_vertex_buffer_data[pos++]= 0.0f;
        }
            this->object = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data, color, GL_FILL);        

    }
    else if(type==2){
     int pos=0,i,j,n=100;
            GLfloat g_vertex_buffer_data[9*n];
            float pi = 3.14159, angle = 1.5*pi, rot=(pi)/(n);
            for(i=0;i<n;i++){
                g_vertex_buffer_data[pos++]= 0.0f;
                g_vertex_buffer_data[pos++]= 0.0f;
                g_vertex_buffer_data[pos++]= 0.0f;
                g_vertex_buffer_data[pos++]= cos(angle)*1.3;
                g_vertex_buffer_data[pos++]= sin(angle)*1.3;
                g_vertex_buffer_data[pos++]= 0.0f;
                angle += rot;
                g_vertex_buffer_data[pos++]= cos(angle)*1.3;
                g_vertex_buffer_data[pos++]= sin(angle)*1.3;
                g_vertex_buffer_data[pos++]= 0.0f;
        }
            this->object = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data, color, GL_FILL);        

    }else if(type==3){
     int pos=0,i,j,n=100;
            GLfloat g_vertex_buffer_data[9*n];
            float pi = 3.14159, angle = 1.5*pi, rot=(pi)/(n);
            for(i=0;i<n;i++){
                g_vertex_buffer_data[pos++]= 0.0f;
                g_vertex_buffer_data[pos++]= 0.0f;
                g_vertex_buffer_data[pos++]= 0.0f;
                g_vertex_buffer_data[pos++]= cos(angle)*1;
                g_vertex_buffer_data[pos++]= sin(angle)*1;
                g_vertex_buffer_data[pos++]= 0.0f;
                angle += rot;
                g_vertex_buffer_data[pos++]= cos(angle)*1;
                g_vertex_buffer_data[pos++]= sin(angle)*1;
                g_vertex_buffer_data[pos++]= 0.0f;
        }
            this->object = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data, color, GL_FILL);        

    }
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Magnet::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
