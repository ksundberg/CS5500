varying vec4 texcoord;

void main(void)
{
  vec4 color;
  
  // Switch on BlockType.
  if (texcoord.w < 2.0)
  {
    color = vec4(0.6, 0.2, 0.2, 1.0);
  }
  else if (texcoord.w < 3.0)
  {
    color = vec4(0.2, 0.5, 0.9, 1.0);
  }
  else if (texcoord.w < 4.0)
  {
    color = vec4(0.2, 0.1, 0.05, 1.0);
  }
  else if (texcoord.w < 5.0)
  {
    color = vec4(1.0, 0.75, 0.45, 1.0);
  }
  else if (texcoord.w < 6.0)
  {
    color = vec4(0.1, 0.1, 0.1, 1.0);
  }
  else if (texcoord.w < 7.0)
  {
    color = vec4(0.1, 0.5, 0.1, 1.0);
  }
  else if (texcoord.w < 8.0)
  {
    color = vec4(0.5, 0.2, 0.1, 1.0);
  }
  else
  { 
    color = vec4(1.0, 0.5, 0.9, 1.0);
  }
  gl_FragColor = color;
}
