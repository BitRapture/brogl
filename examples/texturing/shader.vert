attribute vec3 aPosition;
attribute vec2 aTexCoord;

varying vec2 vTex;

uniform mat4 uModel;
uniform mat4 uProjection;

void main()
{
	gl_Position = uProjection * uModel * vec4(aPosition, 1.0);
	vTex = aTexCoord;
}