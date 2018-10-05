#version 120

uniform vec4 color;
varying vec4 pos;
uniform sampler2D img0;
uniform sampler2D img1;

void main(){
	gl_FragColor = 0.5f*(0.5f*color + abs(pos)*0.5f)
		+ 0.5f * (
			0.5f * texture2D(img0, gl_TexCoord[0].xy)
			+ 0.5f * texture2D(img1, gl_TexCoord[1].xy)
		);
}