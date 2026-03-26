#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textureCoordsIn;

out vec2 textureCoords;
out vec2 fscreenPosition;

uniform vec2 translation;
uniform vec2 scale;

vec2 toScreenCoords(vec2 translation)
{
  return vec2(2.0*translation.x - 1.0, -2.0*translation.y + 1.0);
}

void main()
{
  textureCoords = textureCoordsIn;
  fscreenPosition = translation + position*scale;
  gl_Position = vec4(toScreenCoords(translation) + 2.0*position*scale, -1.0, 1.0);
}
