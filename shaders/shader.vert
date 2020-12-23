#version 330 core

// Vertex shader. GLSL is very similar to C.
// You can define extra functions if needed, and the main() function is
// called when the vertex shader gets run.
// The vertex shader gets called once per vertex.

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;


uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 normalOutput;
out vec3 posOutput;

void main()
{
    // default output, should be assigned something
    gl_Position = projection * view * model * vec4(position, 1.0);

    // fragment position
    posOutput = vec3(model * vec4(position, 1.0));

    // normal vector
    normalOutput = mat3(transpose(inverse(model))) * normal;
}