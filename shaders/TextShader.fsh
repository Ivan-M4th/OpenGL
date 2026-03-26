#version 330 core

in vec2 textureCoords;

uniform sampler2D texture;

uniform vec3 color;

uniform float width;
uniform float borderWidth;

void main()
{
  float distance = 1.0 - texture2D(texture, textureCoords).a;
  float alpha = 1.0 - smoothstep(width, width + borderWidth, distance);

  gl_FragColor = vec4(color, alpha);
}
