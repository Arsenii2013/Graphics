#version 330
attribute highp vec4 posAttr;
attribute lowp vec4  norAttr;
varying lowp vec4 col;

uniform highp mat4 model;
uniform highp mat4 view;

uniform highp vec4 Ca;
uniform highp vec4 Cd;
uniform highp vec4 Cs;
uniform highp vec4 Ga;
uniform highp vec4 Ld;
uniform highp vec4 Ls;
uniform highp vec4 light_direction;
uniform highp vec4 view_point;


highp vec4 directional_light(highp vec3 point, highp vec3 normal, highp vec3 view_position, highp vec3 light_dir){
    highp vec3 L = normalize(light_dir);
    highp vec3 N = normalize(normal);
    highp vec3 R = reflect(L, N);
    highp vec3 V = -normalize(view_position - point);
    highp float cosTheta = dot(L, N);
    highp float cosAlpha = dot(R, V);
    highp float cosAlphaN = pow(max(cosAlpha, 0.), 20.);

    //cosTheta = 0;
    //cosAlphaN  = 0;
    return vec4(   Ca.x * Ga.x + max(Cd.x * Ld.x * cosTheta, 0.) + max(Cs.x * Ls.x * cosAlphaN, 0.),
                   Ca.y * Ga.y + max(Cd.y * Ld.y * cosTheta, 0.) + max(Cs.y * Ls.y * cosAlphaN, 0.),
                   Ca.z * Ga.z + max(Cd.z * Ld.z * cosTheta, 0.) + max(Cs.z * Ls.z * cosAlphaN, 0.),
                   1);
}
void main(void)
{
    highp vec3 convertedNor = vec4(normalize(transpose(inverse(model)) * norAttr)).xyz;
    highp vec3 convertedPos = vec4(model * posAttr).xyz;

    //col = getColor(convertedNor);
    //col = vec4(1., 1., 1., 1.);

    col = directional_light(convertedPos, convertedNor, view_point.xyz, light_direction.xyz);
    gl_Position = view * model * posAttr;
}
