varying vec2 vTex;

uniform sampler2D uTex;

void main()
{
	vec4 tex = texture2D(uTex, vTex);
	gl_FragColor = tex;
}