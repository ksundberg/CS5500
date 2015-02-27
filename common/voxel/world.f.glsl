varying vec4 texcoord;
 
void main(void) {
  if (texcoord.w < 2.0)
  {
    gl_FragColor = vec4(0.2,0.2,0.2,1.0);
  }
  else
  {
    gl_FragColor = vec4(texcoord.w / 8.0, texcoord.w / 16.0, texcoord.w / 32.0, 1.0);
  }
}
