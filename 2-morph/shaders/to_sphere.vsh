attribute highp vec4 posAttr;
attribute lowp vec4 colAttr;
varying lowp vec4 col;
uniform highp mat4 matrix;
uniform highp float factor;
void main() {
   col = colAttr;
   highp vec4 posAttr_norm = vec4(factor * normalize(posAttr.xyz) + (1. - factor) * posAttr.xyz, 1.);
   //highp vec4 posAttr_norm = vec4(normalize(posAttr.xyz).x, factor * normalize(posAttr.xyz).y, normalize(posAttr.xyz).z, 1.);
   gl_Position = matrix * posAttr_norm;
}
