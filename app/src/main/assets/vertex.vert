attribute vec3 inPosition;
attribute vec2 inCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec2 texCoord;

void main()
{
    texCoord = inCoord;
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
}