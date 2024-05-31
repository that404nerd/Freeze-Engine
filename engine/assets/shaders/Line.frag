#version 420 core

out vec4 o_LineColor;
in vec4 f_LineColor;

void main()
{
  o_LineColor = f_LineColor;
}
