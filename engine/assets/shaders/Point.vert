#version 420 core

layout (location = 0) in vec3 a_PointPos;
layout (location = 1) in vec4 a_PointColor;

out vec4 f_PointColor;

uniform mat4 a_ProjectionMatrix;

void main()
{
   gl_Position = a_ProjectionMatrix * vec4(a_PointPos.x, a_PointPos.y, a_PointPos.z, 1.0);
   f_PointColor = a_PointColor;
}

