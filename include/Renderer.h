#pragma once
#include <glad/glad.h>
#include "GameObject.h"

class Renderer {
public:
    Renderer(GLuint shaderProgram, GLuint VAO);

    void draw(const GameObject& obj);

    void resize(int width, int height);

private:
    GLuint shaderProgram;
    GLuint VAO;
    GLint offsetLocation;
    GLint projectionLocation;
};
