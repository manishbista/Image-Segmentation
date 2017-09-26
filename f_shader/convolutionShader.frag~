uniform sampler2D grayInputImage;
varying vec2 outUV;
uniform mat3 kernelMatrix;
uniform float SCREEN_WIDTH;
uniform float SCREEN_HEIGHT;

vec3 colorValue;
vec3 outputColorValue;
mat3 pixelMatrix;
float texelWidthOffset;
float texelHeightOffset;

void main()
{
 texelWidthOffset = 1.0/SCREEN_WIDTH;
 texelHeightOffset = 1.0/SCREEN_HEIGHT;

//red
 colorValue.x = texture2D(grayInputImage, vec2(outUV.x - texelWidthOffset, outUV.y - texelHeightOffset)).r;
 colorValue.y = texture2D(grayInputImage, vec2(outUV.x, outUV.y - texelHeightOffset)).r;
 colorValue.z = texture2D(grayInputImage, vec2(outUV.x + texelWidthOffset, outUV.y - texelHeightOffset)).r;
 outputColorValue.x = dot(kernelMatrix[0], colorValue);

 colorValue.x = texture2D(grayInputImage, vec2(outUV.x - texelWidthOffset, outUV.y)).r;
 colorValue.y = texture2D(grayInputImage, vec2(outUV.x, outUV.y)).r;
 colorValue.z = texture2D(grayInputImage, vec2(outUV.x + texelWidthOffset, outUV.y)).r;
 outputColorValue.x = outputColorValue.x + dot(kernelMatrix[1], colorValue);

 colorValue.x = texture2D(grayInputImage, vec2(outUV.x - texelWidthOffset, outUV.y + texelHeightOffset)).r;
 colorValue.y = texture2D(grayInputImage, vec2(outUV.x, outUV.y + texelHeightOffset)).r;
 colorValue.z = texture2D(grayInputImage, vec2(outUV.x + texelWidthOffset, outUV.y + texelHeightOffset)).r;
 outputColorValue.x = outputColorValue.x + dot(kernelMatrix[2], colorValue);

 outputColorValue.x = max(0.0, outputColorValue.x);

//green
 colorValue.x = texture2D(grayInputImage, vec2(outUV.x - texelWidthOffset, outUV.y - texelHeightOffset)).g;
 colorValue.y = texture2D(grayInputImage, vec2(outUV.x, outUV.y - texelHeightOffset)).g;
 colorValue.z = texture2D(grayInputImage, vec2(outUV.x + texelWidthOffset, outUV.y - texelHeightOffset)).g;
 outputColorValue.y = dot(kernelMatrix[0], colorValue);

 colorValue.x = texture2D(grayInputImage, vec2(outUV.x - texelWidthOffset, outUV.y)).g;
 colorValue.y = texture2D(grayInputImage, vec2(outUV.x, outUV.y)).g;
 colorValue.z = texture2D(grayInputImage, vec2(outUV.x + texelWidthOffset, outUV.y)).g;
 outputColorValue.y = outputColorValue.y + dot(kernelMatrix[1], colorValue);

 colorValue.x = texture2D(grayInputImage, vec2(outUV.x - texelWidthOffset, outUV.y + texelHeightOffset)).g;
 colorValue.y = texture2D(grayInputImage, vec2(outUV.x, outUV.y + texelHeightOffset)).g;
 colorValue.z = texture2D(grayInputImage, vec2(outUV.x + texelWidthOffset, outUV.y + texelHeightOffset)).g;
 outputColorValue.y = outputColorValue.y + dot(kernelMatrix[2], colorValue);

 outputColorValue.y = max(0.0, outputColorValue.y);

//blue
 colorValue.x = texture2D(grayInputImage, vec2(outUV.x - texelWidthOffset, outUV.y - texelHeightOffset)).b;
 colorValue.y = texture2D(grayInputImage, vec2(outUV.x, outUV.y - texelHeightOffset)).b;
 colorValue.z = texture2D(grayInputImage, vec2(outUV.x + texelWidthOffset, outUV.y - texelHeightOffset)).b;
 outputColorValue.z = dot(kernelMatrix[0], colorValue);

 colorValue.x = texture2D(grayInputImage, vec2(outUV.x - texelWidthOffset, outUV.y)).b;
 colorValue.y = texture2D(grayInputImage, vec2(outUV.x, outUV.y)).b;
 colorValue.z = texture2D(grayInputImage, vec2(outUV.x + texelWidthOffset, outUV.y)).b;
 outputColorValue.z = outputColorValue.z + dot(kernelMatrix[1], colorValue);

 colorValue.x = texture2D(grayInputImage, vec2(outUV.x - texelWidthOffset, outUV.y + texelHeightOffset)).b;
 colorValue.y = texture2D(grayInputImage, vec2(outUV.x, outUV.y + texelHeightOffset)).b;
 colorValue.z = texture2D(grayInputImage, vec2(outUV.x + texelWidthOffset, outUV.y + texelHeightOffset)).b;
 outputColorValue.z = outputColorValue.z + dot(kernelMatrix[2], colorValue);

 outputColorValue.z = max(0.0, outputColorValue.z);


 gl_FragColor = vec4(outputColorValue, 1.0);
}


