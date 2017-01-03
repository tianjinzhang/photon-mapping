#version 330
out  vec4 vFragColor;
in vec4 Color;
//in vec3 eyePos;
uniform sampler3D tex;
//uniform sampler3D gtex;
uniform sampler2D backtex;
uniform sampler1D tf;
// texture of color map
uniform sampler2D colortex;
// texture of ao map
uniform sampler3D aotex;
// texture of directIllumination
uniform sampler3D directIllTex;
// texture of indirectIllumination
uniform sampler2D inDirectIllTex;
uniform float min;
uniform float max;
uniform int width;
uniform int height;
uniform int step;
uniform int gradientStep;
uniform mat4 mv;
uniform int light;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 lightPosition;
uniform float surfaceShadingParameter;
//HDR is on ro off
uniform bool hdrOn;
//if use tf colors
uniform bool useTFColors;
//HDR exposure parameter
uniform float exposure;
//gamma correction
uniform float gammaCorrection;
//light attenuation
uniform float KL;
float KQ = 0.3;
float toLightDistance = 0.0;
float lightAttenuation = 1.0;
//the vixel to light
vec3 toLightDir;
//color box
uniform float colorBox;

vec4 backColor = texture(backtex,vec2(gl_FragCoord.x/width,gl_FragCoord.y/height));
vec3 lightdir = vec3(backColor.x-Color.x,backColor.y-Color.y,backColor.z-Color.z);

//vec3 lightdir = vec3(Color.x - eyePos.x,Color.y - eyePos.y,Color.z - eyePos.z);
vec3 begin = vec3(Color);
float lightlen = length(lightdir);
float steplen = 1.73/float(step);
float gradientStepLen = 1.73/float(gradientStep);
vec3 lightstep = normalize(lightdir)*steplen;
//func that get gradient
vec3 getGradient(vec3 pos);

vec3 getPhong()
{
    vec3 color;
	vec3 N = normalize( vec3(mv*vec4(getGradient(begin),0.0)));
	vec3 L = normalize(toLightDir);
	vec3 V = vec3(0.0,0.0,1.0);
	vec3 R = normalize(reflect(-L,V));
	float VR = dot(V,R);
	float NL = dot(L,N);
	if(NL < 0.0)
	  NL = 0.0;
	if(VR < 0.0)
	  VR = 0;
    color = (1.0 - surfaceShadingParameter) + (NL*diffuse + pow(VR,8.0)*specular)*surfaceShadingParameter;
  
	//color = ambient + getPhotonLight(begin); 
	//color = ambient + texture(directIllTex,begin).a + getPhotonLight(begin);
    return color; 
}
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
		float alpha = texture(tex,begin).a;
		vec4 Vol =  texture(tf,alpha);
		if(!useTFColors)	 
			Vol.rgb = texture(colortex,vec2(alpha + colorBox,0.3)).bgr ;
		alpha = Vol.a;
		
		toLightDir = lightPosition - vec3(mv*vec4(begin.xy*2.0 - 1.0,1.0 - begin.z*2.0,0.0));
		toLightDistance = length(toLightDir);
		lightAttenuation = 1.0/(1.0  + KQ * toLightDistance + KL * toLightDistance* toLightDistance);
		if(alpha ==0.0)
		{
			continue;
		}

		if( 0 == light)
		{
			coloraccum = (1 - inalpha)*Vol.rgb*alpha + incolor;
		}
		else if( 1 == light)
		{
	        coloraccum = (1 - inalpha)*Vol.rgb*alpha*getPhong()*lightAttenuation + incolor;
			
		}
		else if(2 == light)
		{
			coloraccum = (1 - inalpha)*Vol.rgb*alpha*( ambient + texture(directIllTex,begin ).a*lightAttenuation )+ incolor;
		}
		else if(3 == light)
		{
			coloraccum = (1 - inalpha)*Vol.rgb*alpha*( 1 ) + incolor;
		}
		else if(4 == light)
		{
			coloraccum = (1 - inalpha)*Vol.rgb*alpha*( ambient + texture(directIllTex,begin).a*lightAttenuation ) + incolor;
		}
		else if(5 == light || 7 == light)
		{
			coloraccum = (1 - inalpha)*Vol.rgb*alpha*getPhong()*( ambient + texture(directIllTex,begin).a*lightAttenuation) + incolor;
		}
		else if(6 == light)
		{
			coloraccum = (1 - inalpha)*Vol.rgb*alpha*(vec3(texture(aotex,begin).a)) + incolor;
		}else if(8 == light)
		{
			coloraccum = (1 - inalpha)*Vol.rgb*alpha*getPhong()*(vec3(texture(aotex,begin).a)) + incolor;
		}
		
		alphaaccum = (1 - inalpha)*alpha + inalpha;
		inalpha = alphaaccum;
		incolor = coloraccum;
		
		if( alphaaccum > 0.99)
			break;
   	   
	}


    vec4 result;
	vec3  r;
	if(3 == light)
	{
		result = texture(inDirectIllTex,(vec2(gl_FragCoord.x/width,gl_FragCoord.y/height)));
		
	}else if( 4 == light || 7 == light)
	{
		result = vec4(coloraccum,alphaaccum) + texture(inDirectIllTex,(vec2(gl_FragCoord.x/width,gl_FragCoord.y/height)));
        
	}
	else
	{
		result = vec4(coloraccum,alphaaccum);
	}
	
	
	if(hdrOn)
	{
		r = vec3(1.0) - exp(-vec3(result) * exposure);
	}else
	{
		r = vec3(result); 
	}
	r = pow(r,vec3(1.0/gammaCorrection));
	return vec4(r,1.0);
}
void main(void)
{
   
        vFragColor = getColor();
}
/////////////////////////////////////////////////////
//get the gradient////////////////////////////////
vec3 getGradient(vec3 pos)
{
    float fVolumeValXp = texture(tex,pos+vec3(+gradientStepLen,0,0)).a;
    float fVolumeValXm = texture(tex,pos+vec3(-gradientStepLen,0,0)).a;
    float fVolumeValYp = texture(tex,pos+vec3(0,+gradientStepLen,0)).a;
    float fVolumeValYm = texture(tex,pos+vec3(0,-gradientStepLen,0)).a;
    float fVolumeValZp = texture(tex,pos+vec3(0,0,+gradientStepLen)).a;
    float fVolumeValZm = texture(tex,pos+vec3(0,0,-gradientStepLen)).a;
    return -vec3(fVolumeValXp - fVolumeValXm,
              fVolumeValYp - fVolumeValYm,
              fVolumeValZp - fVolumeValZm ) / 2.0;
}

//////////////////////////////////////////////////
