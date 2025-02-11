#include"../glad.h"
#include"pointsObject.h"
#include"../linmath.h"
#include"shader.h"
#include<GLFW/glfw3.h>
#include<iostream>
#include<vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInputs(GLFWwindow* window);

float vertices[] = {
     1.0, 1.0, 0.0,
    -1.0, 1.0, 0.0,
     1.0,-1.0, 0.0,
    -1.0,-1.0, 0.0
};

unsigned int indices[]{
    0,1,2,
    1,2,3
};

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;

points mesh;

int main(){
    mesh.addPoint(10.0, 10.0, 0);
    mesh.addPoint(20.0, 10.0, 1);
    mesh.points.at(0).addConnection(1, 10.0, 0.0, 20.0);

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

    Shader shader(
            "src/shaders/vert.vert",
            "src/shaders/frag.frag"
            );


    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    framebuffer_size_callback(window, framebufferWidth, framebufferHeight);

    float pointCoord[2] = {
        mesh.points.at(0).x,
        mesh.points.at(0).y
    };

    while (!glfwWindowShouldClose(window)) {
        processInputs(window);

        glClearColor(0.2, 0.2, 0.3, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        shader.setVec2("pointCoord", pointCoord);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / 4, GL_UNSIGNED_INT, 0);

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
