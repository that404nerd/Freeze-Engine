#version 420 core

out vec4 o_TextureQuadColor;

in vec4 f_Color;
in vec2 f_TextureCoords;

uniform sampler2D o_Texture;

void main()
{
  o_TextureQuadColor = texture(o_Texture, f_TextureCoords);
}
