#include"../glad.h"
#include"points.h"
#include"../linmath.h"
#include<GLFW/glfw3.h>
#include<iostream>
#include<vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInputs(GLFWwindow* window);

points mesh;

struct

int main(){
    mesh.addPoint(10.0, 10.0, 0);
    mesh.addPoint(20.0, 10.0, 1);
    mesh.points.at(0).addConnection(1, 10.0, 0.0, 20.0);

    float verticies[] = {
        0.0, 0.0, 0.0
    }

    unsigned int VAO;

    if(!glfwInit()){
        std::cout << "failed to load glfw";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "softbody sim", NULL, NULL);

    if(window == NULL){
        std::cout << "failed to load window";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "failed to load GLAD";
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        processInputs(window);

        glClearColor(0.2, 0.2, 0.3, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    (void)window;
    glViewport(0, 0, width, height);
}
void processInputs(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}
