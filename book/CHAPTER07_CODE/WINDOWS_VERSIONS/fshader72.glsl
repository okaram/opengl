#version 150

in vec3 R;
uniform samplerCube texMap;
out vec4 fColor;

void main()
{
     vec4 texColor = textureCube(texMap, R);

    fColor = texColor;
}
