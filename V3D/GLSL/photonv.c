#version 330
in vec3 vVertex;
in vec4 vColor;
out vec4 Color;
//out vec3 eyePos;
uniform mat4 mvp;
uniform mat4 mv;

void main(void)
{
Color = vColor;
//eyePos = (vec3(inverse(c*mv*c)*eyePosTemp) + 0.5);
gl_Position = mvp * vec4(vVertex,1.0f);
}
