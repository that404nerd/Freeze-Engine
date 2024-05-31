#version 420 core

out vec4 o_PointColor;
in vec4 f_PointColor;

void main()
{
  o_PointColor = f_PointColor;
}
