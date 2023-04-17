#version 330
attribute highp vec4 posAttr;
attribute lowp vec4  norAttr;

varying highp vec3 convertedPos;
varying lowp vec3  convertedNor;

uniform highp mat4 model;
uniform highp mat4 view;

void main(void)
{
    convertedNor = vec4(normalize(transpose(inverse(model)) * norAttr)).xyz;
    convertedPos = vec4(model * posAttr).xyz;

    gl_Position = view * model * posAttr;
}
