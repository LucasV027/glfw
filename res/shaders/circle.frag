#version 330 core

uniform vec3 circleColor;
out vec4 fragColor;
in vec2 uv;

void main()
{
    vec2 center = vec2(0.5, 0.5);
    float radius = 0.4;

    float dist = distance(uv, center);

    if (dist <= radius) {
        fragColor = vec4(circleColor, 1.0);
    } else {
        fragColor = vec4(0.0);
    }
}
