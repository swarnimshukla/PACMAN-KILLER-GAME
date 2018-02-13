#include "ball2.h"
#include "main.h"

Ball2::Ball2(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0;
    v= 0.1;
    u= 0.05;
    flag=0;
    magnet_speed = 0.03;
    gravity = -0.015;
    px=0;
    int i;
    GLfloat g_vertex_buffer_data[1000004];
     for(i=0;i<10068;i++){
         g_vertex_buffer_data[i*9]=0.0f;
         g_vertex_buffer_data[i*9+1]=0.0f;
         g_vertex_buffer_data[i*9+2]=0.0f;
         if(i==0){
            g_vertex_buffer_data[i*9+3]=0.5f;
            g_vertex_buffer_data[i*9+4]=0.0;
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

void Ball2::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball2::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball2::tick() {
    // printf("%lf %lf %lf\n",this->position.x, this->position.y, gravity);
    if(this->position.y<=-4.5) {
        if(this->position.x>=-2.8 && this->position.x <= 0.8 ){
            if(flag==0 && speed<0){
                this->position.y-=u;
            }
            else if(flag==0 && speed >0){
                gravity= -0.015;    
                this->position.y += speed;
                speed += gravity;
            }
            else if(flag==1){
                gravity= -0.015;    
                this->position.y += speed;
                speed += gravity;
                flag=0;
                
            }
        }
    }
    else{
        gravity= -0.015;    
        this->position.y += speed;
        speed += gravity;
    }
    if(position.x <= -3.0 || position.x >= 1.1 )
        if(position.y <-3.4){
            position.y = -3.4;
            speed = 0;
        }

    if(px!=0){
        for(int i=0; i<30;++i)
            this-> position.x -= px;

        // px=0;        
    }

}

bounding_box_t Ball2::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 2*0.4, 2*0.4 };
    // float s = this-> speed;  
    return bbox;
}
