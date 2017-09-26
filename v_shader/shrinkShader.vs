#version 130

attribute vec3 vertex;
attribute vec2 UV;

varying vec2 outUV;


uniform mat4 modelViewProjectionMatrix;
uniform float TEX_WIDTH;
uniform float TEX_HEIGHT;
uniform float SCREEN_WIDTH;
uniform float SCREEN_HEIGHT;

void main()
{
	gl_Position=modelViewProjectionMatrix*vec4(vertex,1.0);
	
	outUV.x = (SCREEN_WIDTH *  UV.x) / TEX_WIDTH;
	outUV.y = (SCREEN_HEIGHT *  UV.y) / TEX_HEIGHT;
}
