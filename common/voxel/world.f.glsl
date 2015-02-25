varying vec4 texcoord;
 
void main(void) {
  gl_FragColor = vec4(texcoord.w / 128.0, texcoord.w / 256.0, texcoord.w / 512.0, 1.0);
}
