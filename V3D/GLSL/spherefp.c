#version 330
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float ambienti;
uniform float diffusei;
uniform float speculari;
in vec3 normal;
in vec3 lightV;

out vec4 vFragColor;
void main(void)
{
	float p = dot(normalize(lightV),normalize(normal));
	if( p < 0.0)
	    p = 0.0;
	vFragColor = vec4(ambient,0.8)*ambienti + vec4(diffuse,1.0)*p*diffusei +vec4(specular,1.0)*pow(p,8.0)*speculari;
	


}