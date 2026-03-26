#version 330 core

in vec2 textureCoords;
in vec2 fscreenPosition;

uniform sampler2D texture;
uniform bvec2 useFadeOut;
uniform vec4 fadeOutBounds;
uniform vec2 fadeOutBorderSize;
uniform vec4 blendColor;
uniform vec2 colorBlending;
uniform int componentType;

uniform vec4 color;

uniform float textWidth;
uniform float textBorderWidth;

void calculateFadeOut(out float alpha)
{
  alpha = 1.0;
  if(useFadeOut.x)
  {
    alpha = 1.0 - smoothstep(fadeOutBounds.y, fadeOutBounds.y + fadeOutBorderSize.x, fscreenPosition.x);
    alpha*=smoothstep(fadeOutBounds.x - fadeOutBorderSize.x, fadeOutBounds.x, fscreenPosition.x);
  }
}

void calculateColorBlending(inout vec4 totalColor)
{
  totalColor = vec4((1.0 - colorBlending.x)*totalColor.xyz + colorBlending.x*blendColor.xyz, (1.0 - colorBlending.y)*totalColor.a + colorBlending.y*blendColor.a);
}

void processColorComponent()
{
  float alpha;
  calculateFadeOut(alpha);
  alpha = alpha*texture2D(texture, textureCoords).a;

  gl_FragColor = vec4(color.xyz, color.a*alpha);
}

void processTexuredComponent()
{
  float alpha;
  calculateFadeOut(alpha);

  vec4 totalColor = texture2D(texture, textureCoords)*vec4(1.0, 1.0, 1.0, alpha);

  calculateColorBlending(totalColor);
  gl_FragColor = totalColor;
}

void processTextComponent()
{
  float alpha;
  calculateFadeOut(alpha);

  float distance = 1.0 - texture2D(texture, textureCoords).a;
  float distanceAlpha = 1.0 - smoothstep(textWidth, textWidth + textBorderWidth, distance);

  vec4 totalColor = vec4(color.xyz, distanceAlpha*alpha);
  calculateColorBlending(totalColor);

  gl_FragColor = totalColor;
}

void main()
{
  if(componentType == 0)
  {
    processColorComponent();
  }
  else if(componentType == 1)
  {
    processTexuredComponent();
  }
  else if(componentType == 2)
  {
    processTextComponent();
  }
}
