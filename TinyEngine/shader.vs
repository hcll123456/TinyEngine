#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 u_mvp;

out vec4 ourColor;

void main()
{
    gl_Position = u_mvp *vec4(aPos, 1.0);
    ourColor = aColor;
}