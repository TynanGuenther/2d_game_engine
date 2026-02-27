#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec2 offset;
uniform mat4 projection;


void main() {
    vec2 worldPos = aPos + offset;
    gl_Position = projection * vec4(worldPos, 0.0, 1.0);
}
