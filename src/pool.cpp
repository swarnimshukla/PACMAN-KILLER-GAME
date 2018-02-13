#include "main.h"
#include "pool.h"

Pool::Pool(float x, float y, color_t color, int c ) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    if(c==0){ 
        int pos=0,i,j,n=100;
        GLfloat g_vertex_buffer_data[9*n];
        float pi = 3.14159, angle = pi, rot=(pi)/(n);
        for(i=0;i<n;i++){
            g_vertex_buffer_data[pos++]= 0.0f;
            g_vertex_buffer_data[pos++]= 0.0f;
            g_vertex_buffer_data[pos++]= 0.0f;
            g_vertex_buffer_data[pos++]= cos(angle)*2.3;
            g_vertex_buffer_data[pos++]= sin(angle)*2.3;
            g_vertex_buffer_data[pos++]= 0.0f;
            angle += rot;
            g_vertex_buffer_data[pos++]= cos(angle)*2.3;
            g_vertex_buffer_data[pos++]= sin(angle)*2.3;
            g_vertex_buffer_data[pos++]= 0.0f;
    
        this->object = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data, color, GL_FILL);
        }
    }
    else{
        int pos=0,i,j,n=100;
        GLfloat g_vertex_buffer_data[9*n];
        float pi = 3.14159, angle = pi, rot=(pi)/(n);
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
    
        this->object = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data, color, GL_FILL);
        }
     
    }
}

void Pool::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0 , 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Pool::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


bounding_box_t Pool::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
