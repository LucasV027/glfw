#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;

uniform float iTime;
uniform mat4 mvp;

out vec2 v_TexCoord;

void main()
{
    gl_Position = mvp * position;
    v_TexCoord = texCoord;
}