#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec2 offset;

void main() {
    gl_Position = vec4(aPos + offset, 0.0, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(0.2, 0.8, 0.3, 1.0);
}
)";
float vertices[] = {
    // two triangles forming a rectangle
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.5f,  0.5f,

     0.5f,  0.5f,
    -0.5f,  0.5f,
    -0.5f, -0.5f
};

float posX = 0.0f;
float posY = 0.0f;
float speed = 1.0f;


int main() {
    double lastTime = glfwGetTime();
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "2D Game", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	std::cerr << "Failed to initialize GLAD\n";
	return 1;
    }
    std::cout << glGetString(GL_VERSION) << "\n";


    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    

    while (!glfwWindowShouldClose(window)) {
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - lastTime;
	std::cout << "dt: " << deltaTime << "\n";
	lastTime = currentTime;
	
	//TODO: UPDATE LOGIC
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	    posX -= speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	    posX += speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	    posY += speed * deltaTime;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	    posY -= speed * deltaTime;

	
	//Render
        glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
	
	glUseProgram(shaderProgram);
	int offsetLoc = glGetUniformLocation(shaderProgram, "offset");
	glUniform2f(offsetLoc, posX, posY);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

