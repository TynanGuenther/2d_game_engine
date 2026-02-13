#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec2 offset;
uniform mat4 projection;


void main() {
    vec2 worldPos = aPos + offset;
    gl_Position = projection * vec4(worldPos, 0.0, 1.0);
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
     0.0f,  0.0f,
     50.0f, 0.0f,
     50.0f, 50.0f,

     0.0f,  0.0f,
     50.0f, 50.0f,
     0.0f,  50.0f
};

float posX = 0.0f;
float posY = 0.0f;
float velocityX = 0.0f;
float velocityY = 0.0f;
float speed = 300.0f;


void createOrtho(float left, float right,
                 float bottom, float top,
                 float* matrix)
{
    matrix[0] =  2.0f / (right - left);
    matrix[1] =  0.0f;
    matrix[2] =  0.0f;
    matrix[3] =  0.0f;

    matrix[4] =  0.0f;
    matrix[5] =  2.0f / (top - bottom);
    matrix[6] =  0.0f;
    matrix[7] =  0.0f;

    matrix[8] =  0.0f;
    matrix[9] =  0.0f;
    matrix[10] = -1.0f;
    matrix[11] =  0.0f;

    matrix[12] = -(right + left) / (right - left);
    matrix[13] = -(top + bottom) / (top - bottom);
    matrix[14] =  0.0f;
    matrix[15] =  1.0f;
}


void processInput(GLFWwindow* window) {
    velocityX = 0.0f;
    velocityY = 0.0f;
    //Move Rectangle
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        velocityX = -speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        velocityX = speed;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        velocityY = speed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	    velocityY = -speed;
}

void update(double deltaTime) {
    posX += velocityX * deltaTime;
    posY += velocityY * deltaTime;
    posX = std::clamp(posX, 0.0f, 800.0f - 50.0f);
    posY = std::clamp(posY, 0.0f, 600.0f - 50.0f);
}

void render(unsigned int shaderProgram, unsigned int VAO) {
        glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
	
	glUseProgram(shaderProgram);
	int offsetLoc = glGetUniformLocation(shaderProgram, "offset");
	glUniform2f(offsetLoc, posX, posY);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


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

    //enable VSync
    glfwSwapInterval(1);

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
//
    float projection[16];
    createOrtho(0.0f, 800.0f, 0.0f, 600.0f, projection);
    
    glUseProgram(shaderProgram);
    
    int projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection);
//    

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
	lastTime = currentTime;

	processInput(window);

	update(deltaTime);

	render(shaderProgram, VAO);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

