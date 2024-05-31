#version 420 core

layout (location = 0) in vec3 a_LinePos;
layout (location = 1) in vec4 a_LineColor;

out vec4 f_LineColor;

uniform mat4 a_ProjectionMatrix;

void main()
{
  gl_Position = a_ProjectionMatrix * vec4(a_LinePos.x, a_LinePos.y, a_LinePos.z, 1.0f);
  f_LineColor = a_LineColor;
}
