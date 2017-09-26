#version 130

uniform sampler2D rgbImage;
varying vec2 outUV;

vec3 rgbColor, hsvColor;

float rgbMin, rgbMax, delta;

void main()
{
 rgbColor = texture2D(rgbImage, outUV).rgb;
 rgbMin = min(rgbColor.x, rgbColor.y);
 rgbMin = min(rgbColor.z, rgbMin);

 rgbMax = max(rgbColor.x, rgbColor.y);
 rgbMax = max(rgbColor.z, rgbMax);

 delta = rgbMax - rgbMin;

//for value-component
 hsvColor.z = rgbMax;
 if(delta < 0.00001)
 {
	hsvColor.x = 0.0;
	hsvColor.y = 0.0;
 }

 else
 {
	//for saturation component
	if(rgbMax < 0.00001){
	hsvColor.y = 0.0;}
	else {
	hsvColor.y = delta/rgbMax;}


	//for hue component
   	if(rgbColor.x == rgbMax ){                          
        hsvColor.x = ( rgbColor.y - rgbColor.z ) / delta;  
	hsvColor.x = mod(hsvColor.x, 6.0); }      
   	else if( rgbColor.y == rgbMax)
        hsvColor.x = 2.0 + ( rgbColor.z - rgbColor.x ) / delta;  
    	else
        hsvColor.x = 4.0 + ( rgbColor.x - rgbColor.y ) / delta;  

    	hsvColor.x = hsvColor.x * 60.0;                              

   	if( hsvColor.x < 0.0 )
        hsvColor.x = hsvColor.x + 360.0;

	hsvColor.x = hsvColor.x/360.0;


 }

 gl_FragColor = vec4(vec3(hsvColor.x, hsvColor.y, hsvColor.z), 1.0);
}

