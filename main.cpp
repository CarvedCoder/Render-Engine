#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ostream>

void framebuffer_size_callback(GLFWwindow * window,int width,int height){
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow * window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)== GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
}

const char *vertexShaderSource = "#version 460 core\n"
    "layout(location=0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
    "}\0";

const char * fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main ()\n"
    "{\n"
    "FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
    "}\0";


unsigned int setupBuffers(float vertices[],size_t byteCount){
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,byteCount,vertices,GL_STATIC_DRAW);
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO); 
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    return VAO;
}


unsigned int initVertexShader(const char * vertexShaderSource){
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } 
    return vertexShader;
}

unsigned int initFragmentShader(const char * fragmentShaderSource){
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
      
    if(!success){
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    } 
    return fragmentShader;
}

unsigned int initShaders(unsigned int vertexShader,unsigned int fragmentShader){
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram); 
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}


void initArrayVertices(){
    
}

int main(){
    
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow * window = glfwCreateWindow(800, 600, "Test", NULL,NULL);

    if(window == NULL){
        std::cout << "Failed to create the window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize glad" << std::endl;
        return -1;
    }

    glViewport(0,0,800,600);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
    -0.5f,-0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    0.0f,0.5f,0.0f
    }; 

    unsigned int vertexShader = initVertexShader(vertexShaderSource);

    unsigned int fragmentShader = initFragmentShader(fragmentShaderSource);
    
    unsigned int shaderProgram = initShaders(vertexShader,fragmentShader);

    unsigned int VAO = setupBuffers(vertices,sizeof(vertices)); 
    
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);

        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
