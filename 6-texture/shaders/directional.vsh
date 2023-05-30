#version 330
attribute highp vec4 posAttr;
attribute lowp vec4  norAttr;

varying highp vec3 convertedPos;
varying lowp vec3  convertedNor;
varying highp vec3 Pos;
varying lowp vec3  Nor;

uniform highp mat4 model;
uniform highp mat4 model_TI;
uniform highp mat4 view;

void main(void)
{
    convertedNor = vec4(normalize(model_TI * norAttr)).xyz;
    convertedPos = vec4(model * posAttr).xyz;
    Pos = posAttr.xyz;
    Nor = norAttr.xyz;

    gl_Position = view * model * posAttr;
}
