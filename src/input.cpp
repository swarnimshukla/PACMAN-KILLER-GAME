#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki, lbutton_down = false;
double drag_oldx = -1, drag_oldy = -1;
double px, py, x=-20, y=-20;
using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        // switch (key) {
        // case GLFW_KEY_C:
        // rectangle_rot_status = !rectangle_rot_status;
        // break;
        // case GLFW_KEY_P:
        // triangle_rot_status = !triangle_rot_status;
        // break;
        // case GLFW_KEY_X:
        //// do something ..
        // break;
        // default:
        // break;
        // }
    } else if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    switch (key) {
    case 'q':
        quit(window);
        break;
    default:
        break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            // Do something
            lbutton_down = true;
            glfwGetCursorPos(window, &x, &y);
                    px = x;
                    py = y;
                    cursorPositionCallback(window, px, py);
            //return;
        } else if (action == GLFW_RELEASE) {
            // Do something
            lbutton_down = false;
        }
        break;
    // case GLFW_MOUSE_BUTTON_RIGHT:
    // if (action == GLFW_RELEASE) {
    // rectangle_rot_dir *= -1;
    // }
    // break;
    default:
        break;
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    //glfwGetCursorPos(window, &x, &y);
    if(lbutton_down){
        if(xpos-px>0){
            move_right();
            //xpos = px;
        }
        else{
            move_left();
            //xpos = px;
        }
        px = xpos;
    }
    //printf("yoyo\n");
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if(yoffset < 0){
        screen_zoom -= 0.01;
        reset_screen();       
    }
    if(yoffset > 0){
        screen_zoom += 0.01;
        reset_screen();       
    }
}
