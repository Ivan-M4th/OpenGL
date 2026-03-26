#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textureCoordsIn;

out vec2 textureCoords;

uniform float screenRatio;
uniform vec2 translation;

vec2 toScreenCoords(vec2 translation)
{
  return vec2(2.0*translation.x - 1.0, -2.0*translation.y + 1.0);
}

vec2 applyRatio(vec2 position)
{
  return vec2(position.x, screenRatio*position.y);
}

void main()
{
  textureCoords = textureCoordsIn;
  gl_Position = vec4(applyRatio(position) + toScreenCoords(translation), -1.0, 1.0);
}
