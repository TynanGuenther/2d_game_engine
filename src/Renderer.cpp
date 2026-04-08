#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer(GLuint shaderProgram, GLuint VAO)
    : shaderProgram(shaderProgram), VAO(VAO)
{
    offsetLocation = glGetUniformLocation(shaderProgram, "offset");
    sizeLocation   = glGetUniformLocation(shaderProgram, "size");
    projectionLocation = glGetUniformLocation(shaderProgram, "projection");
}

void Renderer::draw(const GameObject& obj)
{
    glUseProgram(shaderProgram);

    glUniform2f(offsetLocation,
        obj.transform.position.x,
        obj.transform.position.y);

    glUniform2f(sizeLocation,
        obj.transform.size.x / 50.0f,
        obj.transform.size.y / 50.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::resize(int width, int height)
{
    glm::mat4 projection = glm::ortho(
        0.0f,
        (float)width,
        0.0f,
        (float)height
    );

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(
        projectionLocation,
        1,
        GL_FALSE,
        glm::value_ptr(projection)
    );
}
