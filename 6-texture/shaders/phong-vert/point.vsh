#version 330
attribute highp vec4 posAttr;
attribute lowp vec4  norAttr;
varying lowp vec4 col;

uniform highp mat4 model;
uniform highp mat4 view;

uniform highp mat3 color_mat;

uniform int lights_cnt;
uniform highp vec4 light_points[100];
uniform highp vec4 view_point;

highp vec4 point_light(highp vec3 point, highp vec3 normal, highp vec3 view_position, highp vec3 light_point){
    highp vec3 light_dir = normalize(point - light_point);
    highp float light_distance = distance(point, light_point);
    highp float light_I = 1./(pow(light_distance, 2.) + 1.);
    highp vec3 L = -normalize(light_dir);
    highp vec3 N = normalize(normal);
    highp vec3 R = reflect(L, N);
    highp vec3 V = -normalize(view_position - point);
    highp float cosTheta = dot(L, N);
    highp float cosAlpha = dot(R, V);
    highp float cosAlphaN = pow(max(cosAlpha, 0.), 20.);

    highp vec3 factor = vec3(0., light_I * max(cosTheta, 0.), light_I * max(cosAlphaN, 0.));
    return vec4(color_mat * factor, 0.);
}

highp vec4 ambient(){
    return vec4(color_mat[0][0], color_mat[1][0], color_mat[2][0], 1.);
}

void main(void)
{
    highp vec3 convertedNor = vec4(normalize(transpose(inverse(model)) * norAttr)).xyz;
    highp vec3 convertedPos = vec4(model * posAttr).xyz;

    col = ambient();
    for(int i = 0; i < lights_cnt; i++){
        col += point_light(convertedPos, convertedNor, view_point.xyz, light_points[i].xyz);
    }

    gl_Position = view * model * posAttr;
}
