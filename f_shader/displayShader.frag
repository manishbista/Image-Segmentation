#version 130
uniform sampler2D texture0;
varying vec2 outUV;

void main()
{
 vec3 tex = texture2D(texture0, outUV).rgb;
 gl_FragColor = vec4(tex, 1.0);
}
