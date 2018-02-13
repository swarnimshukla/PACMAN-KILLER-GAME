#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = (rand() % 450 + 200)*(0.0001);
    int i;
    GLfloat g_vertex_buffer_data[1000004];
     for(i=0;i<10068;i++){
         g_vertex_buffer_data[i*9]=0.0f;
         g_vertex_buffer_data[i*9+1]=0.0f;
         g_vertex_buffer_data[i*9+2]=0.0f;
         if(i==0){
            g_vertex_buffer_data[i*9+3]=0.0f;
            radius = (rand() % 600 + 400)*0.001;
            g_vertex_buffer_data[i*9+4]= radius;
            printf("%lf\n",radius);
            g_vertex_buffer_data[i*9+5]=0.0f;
            g_vertex_buffer_data[i*9+6] = (float)cos(-0.79)*g_vertex_buffer_data[i*9+3] - (float)sin(-0.79)*g_vertex_buffer_data[i*9+4];
            g_vertex_buffer_data[i*9+7] = (float)sin(-0.79)*g_vertex_buffer_data[i*9+3] + (float)cos(-0.79)*g_vertex_buffer_data[i*9+4];
            g_vertex_buffer_data[i*9+8] = 0.0f;
         }
         else{
             g_vertex_buffer_data[i*9+3]=g_vertex_buffer_data[(i-1)*9+6];
             g_vertex_buffer_data[i*9+4]=g_vertex_buffer_data[(i-1)*9+7];
             g_vertex_buffer_data[i*9+5]=g_vertex_buffer_data[(i-1)*9+8];
             g_vertex_buffer_data[i*9+6] = (float)cos(-0.79)*g_vertex_buffer_data[i*9+3] - (float)sin(-0.79)*g_vertex_buffer_data[i*9+4];
             g_vertex_buffer_data[i*9+7] = (float)sin(-0.79)*g_vertex_buffer_data[i*9+3] + (float)cos(-0.79)*g_vertex_buffer_data[i*9+4];
             g_vertex_buffer_data[i*9+8] = 0.0f;
         }
     }

    this->object = create3DObject(GL_TRIANGLES, 1000, g_vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 2*this->radius, 2*this->radius };
    return bbox;
}
