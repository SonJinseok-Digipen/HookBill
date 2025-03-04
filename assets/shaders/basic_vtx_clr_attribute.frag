#version 410 core

layout(location = 0) in vec3 vColor;
layout(location = 1) in vec2 fVertexTextureCordinate;

layout(location = 0) out vec4 fFragClr;

uniform sampler2D     uTex2d;
void main()
{
    fFragClr = texture(uTex2d,fVertexTextureCordinate);
}
