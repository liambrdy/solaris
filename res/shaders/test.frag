#version 440

layout (location = 0) out vec4 outColor;

in vec3 fragColor;

void main() {
    outColor = vec4(fragColor, 1.0);
}