#version 330 core

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note you don't have access to the vertex shader's default output, gl_Position.

in vec3 normalOutput;
in vec3 posOutput;

uniform vec3 color;
uniform vec3 viewPos;

// final color of the pixel
out vec4 fragColor;

void main()
{
    // normal calculation for phong illumination
    vec3 normal = normalize(normalOutput);

    //diffuse
    // use directional lighting
    vec3 lightDir = normalize(-vec3(0.0f, -1.0f, 0.0f));
    float diffuse = dot(normal, lightDir);

    //specular
    vec3 viewDir = normalize(viewPos - posOutput);
    vec3 halfVector = lightDir + viewDir;
    float specular = dot(normal, halfVector);

    float intensity = diffuse * specular;

    vec3 result;
    if (intensity > 0.95) {
        result = vec3(1.0, 1.0, 1.0) * color;    
    }
    else if(intensity > 0.5) {
        result = vec3(0.7, 0.7, 0.7) * color;  
    }
    else if(intensity > 0.05) {
        result = vec3(0.35, 0.35, 0.35) * color;  
    }
    else {
        result = vec3(0.1, 0.1, 0.1) * color;  
    }

    float edge = max(0, dot(normal, viewDir));
    if (edge < 0.4) {
        result = vec3(0);
    }

    fragColor = vec4(result, 1.0);
}