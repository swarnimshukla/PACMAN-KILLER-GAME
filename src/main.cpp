#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ground.h"
#include "pool.h"
#include "ball2.h"
#include "porcupine.h"
#include "magnet.h"
#include "plank.h"
#include "bits/stdc++.h"

using namespace std;
GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
Ground gr,gr1,gr2,gr3,gr4;
Pool p1,p2;
Ball2 b2;
Ball  ball2,ball[100];
Porcupine por, por1, por2;
Magnet mag, mag1, mag2, mag3;
Plank plank1, plank2, plank3, plank4;
int i,count=0;
int size=48;
double temp;
int magnet_count=0;
double score;
int life=3;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
   
    for(i=1;i<size;++i)
        ball[i].draw(VP);
    
    gr.draw(VP);
    gr1.draw(VP);
    p1.draw(VP);
    b2.draw(VP);
    gr2.draw(VP);
    gr3.draw(VP);
    // gr4.draw(VP);
    p2.draw(VP);
    por.draw(VP);
    por1.draw(VP);
    por2.draw(VP);
     if(magnet_count >= 300 && magnet_count<= 700){
        mag.draw(VP);
        mag1.draw(VP);
    }
    if(magnet_count >= 900  && magnet_count < 1100){
        mag2.draw(VP);
        mag3.draw(VP);
    }
    if(magnet_count==1200)
        magnet_count=0;
    // plank1.position.x = ball[5].position.x + ball[5].radius*cos(0.785);
    // plank1.position.y = ball[5].position.y + ball[5].radius*sin(0.785);
    // plank1.rotation = -44.9;
    plank1.draw(VP);
    plank2.draw(VP);
    plank3.draw(VP);
    plank4.draw(VP);
    


}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int zoom_in = glfwGetKey(window, GLFW_KEY_W);
    int zoom_out = glfwGetKey(window, GLFW_KEY_S);
    int right1 = glfwGetKey(window, GLFW_KEY_D);
    int left1 = glfwGetKey(window, GLFW_KEY_A);
    


    if (left){
        move_left();
                
    }
    if(right){
        move_right();
        
    }
    if (space) {
        if(b2.position.y >= -3.5 && b2.position.y <= -3.4)
            b2.speed = 0.4;
        else if(b2.position.y <= -4.5)
            b2.speed = 0.2;
        
    }
    if(up){
        screen_center_y += 0.05;
        reset_screen();
        mag.position.y  += 0.1;
        mag1.position.y += 0.1;
        mag2.position.y += 0.1;
        mag3.position.y += 0.1;
    }
    if(down){
        screen_center_y -= 0.05;
        reset_screen();
        mag.position.y -= 0.1;
        mag1.position.y -= 0.1;
        mag2.position.y -= 0.1;
        mag3.position.y -= 0.1;

    }
    if(zoom_in){
        screen_zoom += 0.01;
        reset_screen();
        

    }
    if(zoom_out){
        screen_zoom -= 0.01;
        reset_screen();
        
    }
    if(right1){
        screen_center_x += 0.1;
        reset_screen();

    }
    if(left1){
        screen_center_x -= 0.1;
        reset_screen();
    }

}

void tick_elements() {
    
    b2.tick();
    por.tick();
    por1.tick();
    por2.tick();
    plank1.tick();
    plank2.tick();
    plank3.tick();
    plank4.tick();
    
    for(i=1;i<size;++i)
        ball[i].tick();
    for(i=1;i<size;++i)
        if(b2.speed<0)
            if (detect_collision(b2.bounding_box(), ball[i].bounding_box())) {
                b2.speed=0.3;
                ball[i].position.x=-10.5;
                if(i%4 == 0)
                    score += 10;
                if(i%4 == 1)
                    score += 20;
                if(i%4 == 2)
                    score += 30;
                if(i%4 == 3)
                    score += 40;

                

            }
    // if(ball2.position.x>=7.5)
    //     ball2.position.x=7.5;
    // if(magnet_count >= 300  && b2.position.x >= -7.5 && magnet_count<= 700) 
    //     b2.position.x -= b2.magnet_speed;        
    
    // if(magnet_count >= 900  && b2.position.x <= 7.5 && magnet_count<=1100)
    //     b2.position.x += b2.magnet_speed; 

    if(b2.position.y <= -2.4)
        b2.px=0;
    if(b2.px!=0){
        screen_center_x += 0.1;
        reset_screen();    
    }
    if(b2.position.x <= -4.49 && b2.position.x>= -7.09996 && b2.position.y<=-3.2 && b2.speed<0){
        life--;
    }
       

}

void move_left(){
    // if(b2.position.x >-7.4  )
        b2.position.x -= b2.v ;
        screen_center_x -= 0.1;
        reset_screen();
        mag.position.x -= 0.1;
        mag1.position.x -= 0.1;
        mag2.position.x -= 0.1;
        mag3.position.x -= 0.1;
        

    // else
        // b2.position.x -= 0.01;      
    if(b2.position.x<= -2.75 && b2.position.x>= -2.9){
        if(b2.position.y<= -4.5){
            b2.position.x=-3.3;
            b2.position.y= -3.5;
        }
   
    }
}
void move_right(){
    
    b2.position.x= b2.position.x + b2.v;
    screen_center_x += 0.1;
        reset_screen();        
    mag.position.x += 0.1;
    mag1.position.x += 0.1;
    mag2.position.x += 0.1;
    mag3.position.x += 0.1;
    if(b2.position.x>= 0.789 && b2.position.x<= 0.8000001){
        if(b2.position.y<=-4.5){
            b2.position.x=1.3;
            b2.position.y= -3.5;
        }
    }


}
void check_boundary(){
    for(i=1;i<30;++i){
        if(ball[i].position.x>48.5){
            ball[i].position.x= -18;
        }
        plank1.position.x = ball[1].position.x + ball[1].radius*cos(0.785);
        plank1.position.y = ball[1].position.y + ball[1].radius*sin(0.785);
        plank2.position.x = ball[2].position.x + ball[2].radius*cos(0.785);
        plank2.position.y = ball[2].position.y + ball[2].radius*sin(0.785);
        plank3.position.x = ball[3].position.x + ball[3].radius*cos(0.785);
        plank3.position.y = ball[3].position.y + ball[3].radius*sin(0.785);
        plank4.position.x = ball[4].position.x + ball[4].radius*cos(0.785);
        plank4.position.y = ball[4].position.y + ball[4].radius*sin(0.785);

    }
}
void trampoline_jump(){
    if( b2.position.x > 4 && b2.position.x < 6 && b2.position.y>=-3.4 )
        if(b2.position.y < -3.2)
            if( b2.speed <= 0)
                b2.speed =0.5;
}
void plank_reflection(){
    if(b2.position.x <= (plank1.position.x + 1/(2*sqrt(2)) + 0.5) && b2.position.x >= (plank1.position.x - 1/(2*sqrt(2)) - 0.5) && b2.position.y >= -4.5)
        if(b2.position.y <= (plank1.position.y + 1/2*sqrt(2)) + 0.5 && b2.position.y >= (plank1.position.y - 1/(2*sqrt(2)) - 0.5))     
            if(b2.position.y + b2.position.x - plank1.position.x - plank1.position.y <= 0.5 && b2.speed <0){
                b2.speed=0.5; 
                b2.px = -0.004;
            }
    if(b2.position.x <= (plank2.position.x + 1/(2*sqrt(2)) + 0.5) && b2.position.x >= (plank2.position.x - 1/(2*sqrt(2)) - 0.5) && b2.position.y >= -4.5)
        if(b2.position.y <= (plank2.position.y + 1/2*sqrt(2)) + 0.5 && b2.position.y >= (plank2.position.y - 1/(2*sqrt(2)) - 0.5))     
            if(b2.position.y + b2.position.x - plank2.position.x - plank2.position.y <= 0.5 && b2.speed <0){
                b2.speed=0.5; 
                b2.px = -0.004;
            }
    if(b2.position.x <= (plank3.position.x + 1/(2*sqrt(2)) + 0.5) && b2.position.x >= (plank3.position.x - 1/(2*sqrt(2)) - 0.5) && b2.position.y >= -4.5)
        if(b2.position.y <= (plank3.position.y + 1/2*sqrt(2)) + 0.5 && b2.position.y >= (plank3.position.y - 1/(2*sqrt(2)) - 0.5))     
            if(b2.position.y + b2.position.x - plank3.position.x - plank3.position.y <= 0.5 && b2.speed <0){
                b2.speed=0.5; 
                b2.px = -0.004;
            }
            
    if(b2.position.x <= (plank4.position.x + 1/(2*sqrt(2)) + 0.5) && b2.position.x >= (plank4.position.x - 1/(2*sqrt(2)) - 0.5) && b2.position.y >= -4.5)
        if(b2.position.y <= (plank4.position.y + 1/2*sqrt(2)) + 0.5 && b2.position.y >= (plank4.position.y - 1/(2*sqrt(2)) - 0.5))     
            if(b2.position.y + b2.position.x - plank4.position.x - plank4.position.y <= 0.5 && b2.speed <0){
                b2.speed=0.5; 
                b2.px = -0.004;
            }                
        
}

void inside_pool(){
    if(b2.position.x > -3.3 && b2.position.x < 1.3){
        if( b2.position.y <= -4.5 ){
            if(b2.position.x < 1.3 && b2.position.x > 0.79 ){
                b2.position.x=0.8;
                b2.position.y = (-4 - sqrt(1.8*1.8-((b2.position.x+1)*(b2.position.x+1))));
                b2.flag=1;
            }
            else if( b2.position.x>-3.3 && b2.position.x<=-2.75){
                b2.position.x=-2.8;
                b2.position.y = (-4 - sqrt(1.8*1.8-((b2.position.x+1)*(b2.position.x+1))));
                b2.flag=1;
            }  
            else if(b2.position.x < 0.8 && b2.position.x > -2.8 ){ 
                temp = (-4 - sqrt(1.8*1.8-((b2.position.x+1)*(b2.position.x+1))));
                if(b2.position.y<=temp && b2.speed<0){
                    b2.flag=1;
                    b2.position.y=temp;
                    b2.speed=0;
                }
            }
            if(b2.flag==1){
                if(b2.position.x>-1){
                        b2.position.x-= 0.025;
                    }
                    
                else{
                        b2.position.x += 0.025;
                }

            }

        }
    }
}
void displayScore(){
    string a = "Score : ";
    string b = to_string(score);
    b = a+b;
    string c = " Life : ";
    string d= to_string(life);
    d = c + d;
    b = b + d;

    glfwSetWindowTitle(window, const_cast<char*>(b.c_str()));
}
/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    
    for(i=1;i<size;++i){
        
        if( i % 4 == 0 )
            ball[i] = Ball(-11+ rand()%((-9 + 1) +11),-2 + rand() % (5 + 1 + 2), COLOR_YELLOW);
        else if( i % 4 == 1 )
            ball[i] = Ball(-11+ rand()%((-5 + 1) +11),-2 + rand() % (5 + 1 + 2), COLOR_PURPLE);
        else if( i % 4 == 2 ) 
            ball[i] = Ball(-11+ rand()%((-3 + 1) +11),-2 + rand() % (5 + 1 + 2), COLOR_FUCHSIA);
        else if( i % 4 == 3 )
            ball[i] = Ball(-11+ rand()%((-4 + 1) +11),-2 + rand() % (5 + 1 + 2), COLOR_LIME);
        ball[i].speed = -ball[i].speed;
        ball[i].state=0;
    }

    gr = Ground( 0, 0, COLOR_BROWN, 0 );
    gr1 = Ground( 0, 0, COLOR_GREEN, 1 );
    p1 = Pool( -1 , -4.5 , COLOR_BLUE, 0 );
    b2 = Ball2( 2, -3.5, COLOR_RED);
    b2.flag=0;
    gr2= Ground( 0.8, 0, COLOR_RED, 2 );
    gr3= Ground( 1.5, 0, COLOR_RED, 3 );
    // gr4= Ground(0, 0 , COLOR_BLACK, 4);
    p2 = Pool( 5, -3.5  , COLOR_RED, 1);
    por= Porcupine( 0, 0, COLOR_BLACK, 0 );
    por1 = Porcupine( 0, 0, COLOR_BLACK, 1 );
    por2 = Porcupine( 0, 0, COLOR_BLACK, 2 );
    mag = Magnet(-6.4, 7, COLOR_RED, 0);
    mag1 = Magnet(-6.4,7, COLOR_BACKGROUND, 1);
    mag2 = Magnet(6.4, 7, COLOR_RED, 2);
    mag3 = Magnet(6.4,7, COLOR_BACKGROUND, 3);
    plank1 = Plank(ball[1].position.x + (ball[1].radius)*cos(0.785) ,ball[1].position.y + (ball[1].radius)*sin(0.785) , COLOR_BROWN);
    plank1.speed= ball[1].speed;
    plank1.rotation = 90 + 45;
    plank2 = Plank(ball[2].position.x + (ball[2].radius)*cos(0.785) ,ball[2].position.y + (ball[2].radius)*sin(0.785) , COLOR_BROWN);
    plank2.speed= ball[2].speed;
    plank2.rotation = 90 + 45;
    plank3 = Plank(ball[3].position.x + (ball[3].radius)*cos(0.785) ,ball[3].position.y + (ball[3].radius)*sin(0.785) , COLOR_BROWN);
    plank3.speed= ball[3].speed;
    plank3.rotation = 90 + 45;
    plank4 = Plank(ball[4].position.x + (ball[2].radius)*cos(0.785) ,ball[2].position.y + (ball[2].radius)*sin(0.785) , COLOR_BROWN);
    plank4.speed= ball[4].speed;
    plank4.rotation = 90 + 45;


    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    int level=100;
    int lev_count=0; 

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */

    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            magnet_count++;
            tick_elements();
            tick_input(window);
            check_boundary();
            trampoline_jump();
            inside_pool();
            plank_reflection();
            if(score>=level && lev_count<=3){
                level += 200;
                for(int k=1 ; k<size;k++)
                    ball[k].speed -= 0.04;
                lev_count++;

            }
            displayScore();
            if(life==0)
                break;
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    if (abs( a.y - b.y) <= ((b.height + a.height)/2) && abs(a.x - b.x) <=0.4)
            return 1;
    else 
        return 0;   
    
    }

void reset_screen() {
    float top    = screen_center_y + 8 / screen_zoom;
    float bottom = screen_center_y - 8 / screen_zoom;
    float left   = screen_center_x - 8 / screen_zoom;
    float right  = screen_center_x + 8 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
