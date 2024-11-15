#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;

uniform float iTime;
uniform mat4 mvp;

out vec3 color;

mat3 Rw(vec3 w, float thetha)
{
    w = normalize(w);
    float s = sin(thetha);
    float cb = 1. - cos(thetha);
    float c = cos(thetha);

    mat3 m;
    m[0] = vec3(w.x * w.x * cb + c, w.x * w.y * cb - s * w.z, w.x * w.z * cb + s * w.y);
    m[1] = vec3(w.x * w.y * cb + s * w.z, w.y * w.y * cb + c, w.y * w.z * cb - s * w.x);
    m[2] = vec3(w.x * w.z * cb - s * w.y, w.y * w.z * cb + s * w.x, w.z * w.z * cb + c);

    return m;
}

void main()
{
    color = vertexColor;
    gl_Position = vec4(vertexPos * Rw(vec3(1., 1., 1.), iTime), 1.0);
}