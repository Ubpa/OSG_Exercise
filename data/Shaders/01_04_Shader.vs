#version 120

uniform float h;
varying vec4 pos;

void main(){
	vec4 center = vec4(0,0,0,1.0f);
	vec4 vertex = gl_Vertex;
	vertex.xyz *= 0.8f*h + 0.2f;
	pos = vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_MultiTexCoord1;
	gl_Position = gl_ModelViewProjectionMatrix * vertex;
}