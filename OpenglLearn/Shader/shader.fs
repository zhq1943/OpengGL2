#version 330 core
out vec4 FragColor;
//in vec4 vertexColor;
in vec3 ourColor;
//uniform vec4 ourColor;
void main()
{
    FragColor = vec4(ourColor,1.0f);
};