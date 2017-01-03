#version 330
in vec3 vVertex;
in vec4 vColor;
out vec4 Color;
//out vec3 eyePos;
uniform mat4 mvp;
uniform mat4 mv;

//vec4 eyePosTemp = vec4(0.0,0.0,-10.0,0.0);
//mat4 c = mat4(1.0,0.0,0.0,0.0,
//              0.0,1.0,0.0,0.0,
//			  0.0,0.0,-1.0,0.0,
//			  0.0,0.0,0.0,1.0);
void main(void)
{
Color = vColor;
//eyePos = (vec3(inverse(c*mv*c)*eyePosTemp) + 0.5);
gl_Position = mvp * vec4(vVertex,1.0f);
}
