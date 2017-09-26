uniform sampler2D texture0;
varying vec2 outUV;

void main()
{
 vec3 multiplier = vec3(0.2125, 0.7154, 0.0721);
 vec3 gray = texture2D(texture0, outUV).rgb;
 float intensity = dot(gray, multiplier);
 gl_FragColor = vec4(intensity, intensity, intensity, 1.0);
 //gl_FragColor = vec4(gray, 1.0);
}

