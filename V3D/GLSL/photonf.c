#version 330
out  vec4 vFragColor;
in vec4 Color;
//in vec3 eyePos;
uniform sampler3D tex;
uniform sampler1D tf;
//uniform sampler3D gtex;
uniform sampler2D backtex;
// texture of color map
uniform sampler2D colortex;
// texture of directIllumination
uniform sampler3D directIllTex;
// texture of indirectIllumination
uniform sampler3D inDirectIllTex;
uniform int width;
uniform int height;
uniform int step;
uniform mat4 mv;
//HDR exposure parameter
uniform float exposure;
//if use tf colors
uniform bool useTFColors;
//color box
uniform float colorBox;


vec4 backColor = texture(backtex,vec2(gl_FragCoord.x/width,gl_FragCoord.y/height));
vec3 lightdir = vec3(backColor.x-Color.x,backColor.y-Color.y,backColor.z-Color.z);
float lightlen = length(lightdir);
vec3 begin = vec3(Color);
float steplen = 1.73/float(step);
vec3 lightstep = normalize(lightdir)*steplen;
//func that get photon light
float getPhotonLight(vec3 begin);
//fuc that get color
vec4 getColor()
{

   float inalpha = 0.0;
   vec3 incolor= vec3(0.0);
   float alphaaccum = inalpha;
   vec3 coloraccum = incolor;
   
   for(float i = 0.0;i <= lightlen;i+=steplen,begin+=lightstep)
	{
		//if(any(lessThan(begin,vec3(0.0,0.0,0.0))))
		//	break;
		//if(any(greaterThan(begin,vec3(1.0,1.0,1.0))))
		//	break;
		float alpha = texture(tf,texture(tex,begin).a).a;
		vec4 Vol =  texture(tf,alpha);
		if(!useTFColors)
			Vol.rgb = texture(colortex,vec2(alpha,0.0)).bgr ;
		alpha = Vol.a;
		if(alpha ==0.0)
		{
			continue;
		}

	
		coloraccum = (((1 - inalpha)*Vol.rgb*alpha*getPhotonLight(begin)*(texture(directIllTex,begin).a)))* exposure + incolor;
		alphaaccum = (1 - inalpha)*alpha + inalpha;
		
		inalpha = alphaaccum;
		incolor = coloraccum;
		
		if( alphaaccum > 0.99)
			break;
   	   
	}

 
  //vec3 r = vec3(1.0) - exp(-vec3(coloraccum) * 10);		
  return vec4(coloraccum,1.0);	
	
}
void main(void)
{
   
	
    vFragColor = getColor();
}
/////////////////////////////////////////////////////

//get the estimate photon light
float getPhotonLight(vec3 begin)
{
	float totalInDirLight = texture(inDirectIllTex,begin).a
	+     
	                        texture(inDirectIllTex,begin + vec3(+steplen,0,0)).a + 
	                        texture(inDirectIllTex,begin + vec3(-steplen,0,0)).a +
							texture(inDirectIllTex,begin + vec3(0,+steplen,0)).a +
							texture(inDirectIllTex,begin + vec3(0,-steplen,0)).a +
							texture(inDirectIllTex,begin + vec3(0,0,+steplen)).a +
						    texture(inDirectIllTex,begin + vec3(0,0,-steplen)).a +
							texture(inDirectIllTex,begin + vec3(+steplen,+steplen,0)).a + 
	                        texture(inDirectIllTex,begin + vec3(-steplen,-steplen,0)).a +
							texture(inDirectIllTex,begin + vec3(0,+steplen,+steplen)).a +
							texture(inDirectIllTex,begin + vec3(0,-steplen,-steplen)).a ;
					
	
	return totalInDirLight/4.18;
	
}