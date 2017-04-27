#define GLFW_INCLUDE_GLU
#include<iostream>
#include<GLFW/glfw3.h>
#include<cmath>
#include<Camera.h>

using namespace std;

bool keys[1024], firstMouse = true;
GLfloat lastX = 200, lastY = 200;
Camera cam;

void drawCube();
void drawZUOBIAO();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xdelta, double ydelta);
void doMovement();

int main() {
    //GLfloat camPosX, camPosZ;
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(400, 400, "I'm a cube", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        doMovement();
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        //glMatrixMode(GL_MODELVIEW | GL_PROJECTION);
        //glLoadIdentity();
        //glOrtho(-2, 2, -2, 2, 0, 4); //不设置look at函数时的正交投影
        //glFrustum(-1, 1, -1, 1, 1, 10); //不设置look函数时的透视投影
        //gluPerspective(66, 1, 0.1, 1000); //这个更符合人眼...但是不让用:(
        //gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0); //视角
        //camPosX = sin(glfwGetTime())*2;
        //camPosZ = cos(glfwGetTime())*2;
        //gluLookAt(camPosX, 1, camPosZ, 0, 0, 0, 0, 1, 0);
        drawZUOBIAO();
        //glTranslatef(0.5, -0.5, -1.5);
        drawCube();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}

void drawCube() {
    glBegin(GL_QUADS);
    //surface one
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.05f, 0.05f, 0.05f);
    glVertex3f(0.05f, 0.05f, -0.05f);
    glVertex3f(-0.05f, 0.05f, -0.05f);
    glVertex3f(-0.05f, 0.05f, 0.05f);
    //surface two
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.05f, -0.05f, 0.05f);
    glVertex3f(0.05f, -0.05f, -0.05f);
    glVertex3f(-0.05f, -0.05f, -0.05f);
    glVertex3f(-0.05f, -0.05f, 0.05f);
    //surface three
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.05f, 0.05f, 0.05f);
    glVertex3f(-0.05f, 0.05f, 0.05f);
    glVertex3f(-0.05f, -0.05f, 0.05f);
    glVertex3f(0.05f, -0.05f, 0.05f);
    //surface four
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.05f, 0.05f, -0.05f);
    glVertex3f(-0.05f, 0.05f, -0.05f);
    glVertex3f(-0.05f, -0.05f, -0.05f);
    glVertex3f(0.05f, -0.05f, -0.05f);
    //surface five
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.05f, 0.05f, 0.05f);
    glVertex3f(0.05f, 0.05f, -0.05f);
    glVertex3f(0.05f, -0.05f, -0.05f);
    glVertex3f(0.05f, -0.05f, 0.05f);
    //surface six
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-0.05f, 0.05f, 0.05f);
    glVertex3f(-0.05f, 0.05f, -0.05f);
    glVertex3f(-0.05f, -0.05f, -0.05f);
    glVertex3f(-0.05f, -0.05f, 0.05f);

    glEnd();
    glFlush();
}

void drawZUOBIAO() {
    glBegin(GL_LINES);
    glColor3f(0.4f, 0.7f, 0.6f);
    glVertex3f(-2, 0, 0);
    glVertex3f(2, 0, 0);
    glColor3f(0, 0, 0.5f);
    glVertex3f(0, -2, 0);
    glVertex3f(0, 2, 0);
    glColor3f(1, 0.2f, 0);
    glVertex3f(0, 0, -2);
    glVertex3f(0, 0, 2);
    glEnd();
    glFlush();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (action == GLFW_PRESS) {
        keys[key] = true;
    } else if (action == GLFW_RELEASE) {
        keys[key] = false;
    } 
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    GLfloat deltaX = xpos-lastX;
    GLfloat deltaY = ypos-lastY;
    lastX = xpos;
    lastY = ypos;
    cam.rotate(0.3*deltaY, 0.3*deltaX);
}
/*
void scroll_callback(GLFWwindow* window, double xdelta, double ydelta) {
    if (cam.GetFieldOfView() >= 1 && cam.GetFieldOfView() <= 60) {
        cam.SetFieldOfView(cam.GetFieldOfView()-ydelta);
    }
    if (cam.GetFieldOfView() < 1) cam.SetFieldOfView(1);
    if (cam.GetFieldOfView() > 60) cam.SetFieldOfView(60);
}
*/

void doMovement() {
    cam.GluLookAt();
    if (keys[GLFW_KEY_W]) {
        cam.moveForward(0.02);
        cam.GluLookAt();
    } if (keys[GLFW_KEY_S]) {
        cam.moveBack(0.02);
        cam.GluLookAt();
    } if (keys[GLFW_KEY_A]) {
        cam.moveLeft(0.02);
        cam.GluLookAt();
    } if (keys[GLFW_KEY_D]) {
        cam.moveRight(0.02);
        cam.GluLookAt();
    }
}
