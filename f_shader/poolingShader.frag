uniform sampler2D textureUnit;
varying vec2 outUV;

uniform float SCREEN_WIDTH;
uniform float SCREEN_HEIGHT;
float texelWidthOffset;
float texelHeightOffset;
float maxA, maxB;
vec3 maxC;

vec4 vecPool;

void main()
{
 texelWidthOffset = 1.0/SCREEN_WIDTH;
 texelHeightOffset = 1.0/SCREEN_HEIGHT;

 vecPool.x = texture2D(textureUnit, vec2(2.0 * outUV.x, 2.0 * outUV.y)).r;
 vecPool.y = texture2D(textureUnit, vec2(2.0 * outUV.x, 2.0 * outUV.y + texelHeightOffset)).r;
 vecPool.z = texture2D(textureUnit, vec2(2.0 * outUV.x + texelWidthOffset, 2.0 * outUV.y)).r;
 vecPool.w = texture2D(textureUnit, vec2(2.0 * outUV.x + texelWidthOffset, 2.0 * outUV.y + texelHeightOffset)).r;	

 maxA = max(vecPool.x, vecPool.y);
 maxB = max(vecPool.z, vecPool.w);
 maxC.x = max(maxA, maxB);

 vecPool.x = texture2D(textureUnit, vec2(2.0 * outUV.x, 2.0 * outUV.y)).g;
 vecPool.y = texture2D(textureUnit, vec2(2.0 * outUV.x, 2.0 * outUV.y + texelHeightOffset)).g;
 vecPool.z = texture2D(textureUnit, vec2(2.0 * outUV.x + texelWidthOffset, 2.0 * outUV.y)).g;
 vecPool.w = texture2D(textureUnit, vec2(2.0 * outUV.x + texelWidthOffset, 2.0 * outUV.y + texelHeightOffset)).g;	

 maxA = max(vecPool.x, vecPool.y);
 maxB = max(vecPool.z, vecPool.w);
 maxC.y = max(maxA, maxB);

 vecPool.x = texture2D(textureUnit, vec2(2.0 * outUV.x, 2.0 * outUV.y)).b;
 vecPool.y = texture2D(textureUnit, vec2(2.0 * outUV.x, 2.0 * outUV.y + texelHeightOffset)).b;
 vecPool.z = texture2D(textureUnit, vec2(2.0 * outUV.x + texelWidthOffset, 2.0 * outUV.y)).b;
 vecPool.w = texture2D(textureUnit, vec2(2.0 * outUV.x + texelWidthOffset, 2.0 * outUV.y + texelHeightOffset)).b;	

 maxA = max(vecPool.x, vecPool.y);
 maxB = max(vecPool.z, vecPool.w);
 maxC.z = max(maxA, maxB);

 gl_FragColor = vec4(maxC, 1.0);
}


