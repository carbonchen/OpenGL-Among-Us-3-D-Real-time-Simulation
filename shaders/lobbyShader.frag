#version 330 core

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note you don't have access to the vertex shader's default output, gl_Position.

in vec3 normalOutput;
in vec3 posOutput;
in vec2 texCoordOutput;

uniform sampler2D ourTexture;

uniform vec3 viewPos;

// final color of the pixel
out vec4 fragColor;

void main()
{
    vec3 ambChart = vec3(0.0, 0.0, 0.0);
    vec3 diffChart = vec3(0.5, 0.5, 0.0);
    vec3 specChart = vec3(0.6, 0.6, 0.6);
    float shininess = 0.25;
    vec3 lightColor = vec3(1.0);

    // normal calculation for phong illumination
    vec3 normal = normalize(normalOutput);

    //ambient
    vec3 ambient  = lightColor * vec3(texture(ourTexture, texCoordOutput));

    //diffuse (directional lighting)
    vec3 lightDir = normalize(-vec3(0.0f, -1.0f, 0.0f));
    float diff = dot(normal, lightDir);
    vec3 diffuse = lightColor * diff * vec3(texture(ourTexture, texCoordOutput));

    //specular
    vec3 viewDir = normalize(viewPos - posOutput);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = lightColor * spec * vec3(texture(ourTexture, texCoordOutput));

    fragColor = vec4(ambient + diffuse + specular, 1.0f);
}