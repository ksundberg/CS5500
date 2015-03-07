varying vec4 texcoord;
uniform sampler2D texture;

void main(void) {
	vec2 coord2d;
	float intensity;

        coord2d = vec2((fract(texcoord.x + texcoord.z) + texcoord.w) / 16.0, -texcoord.y);
        intensity = 0.85;
	
	vec4 color = texture2D(texture, coord2d);

	if(color.a < 0.4)
		discard;

	color.xyz *= intensity;

	gl_FragColor = color;
}
