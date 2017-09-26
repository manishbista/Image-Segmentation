#version 130
uniform sampler2D colorImage;
varying vec2 outUV;
uniform float SCREEN_WIDTH;
uniform float SCREEN_HEIGHT;

out vec4 outMagnitude;
out vec4 outAngle;

float texelWidthOffset;
float texelHeightOffset;

vec3 center, positionL, positionR, positionT, positionB;
vec3 horizontalDiff, verticalDiff;
vec3 thitaRad, thitaDeg, mag;

void main()
{
 texelWidthOffset = 1.0/SCREEN_WIDTH;
 texelHeightOffset = 1.0/SCREEN_HEIGHT;

 positionT = texture2D(colorImage, vec2(outUV.x, outUV.y + texelHeightOffset)).rgb;
 positionR = texture2D(colorImage, vec2(outUV.x + texelWidthOffset, outUV.y)).rgb;
 positionB = texture2D(colorImage, vec2(outUV.x, outUV.y - texelHeightOffset)).rgb;
 positionL = texture2D(colorImage, vec2(outUV.x - texelWidthOffset, outUV.y)).rgb;

 horizontalDiff = (positionR - positionL)*0.5 + vec3(0.5);
 verticalDiff = (positionT - positionB)*0.5 + vec3(0.5);

 thitaRad = atan(positionT - positionB, positionR - positionL);				//thita = y over x, thita value ranges from -pi/2 to pi/2
 thitaDeg = degrees(thitaRad) + vec3(90.0, 90.0, 90.0);		//thita in degrees ranges from 0 to 180
 mag = sqrt(horizontalDiff * horizontalDiff + verticalDiff * verticalDiff);

 outMagnitude = vec4(mag, 1.0);
 outAngle = vec4(thitaDeg / 180.0, 1.0);
}


