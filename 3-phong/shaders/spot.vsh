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
uniform highp vec4 light_point;
uniform highp vec4 light_direction;
uniform highp vec4 view_point;

highp vec4 spot_light(highp vec3 point, highp vec3 normal, highp vec3 view_position, highp vec3 spot_position, highp vec3 spot_direction, highp float inner, highp float outter){
    highp vec3 light_dir = normalize(point - spot_position);
    highp float light_distance = distance(point, spot_position);
    highp float distance_I = 10./(pow(light_distance, 1.) + 1.);
    highp vec3 L = -normalize(light_dir);
    highp vec3 N = normalize(normal);
    highp vec3 R = reflect(L, N);
    highp vec3 V = -normalize(view_position - point);
    highp vec3 S = normalize(spot_direction);

    highp float direction_I;
    highp float cosA = abs(dot(L, S));
    if(cosA > inner){
        direction_I = 1;
    }else if(inner > cosA && cosA > outter){
        direction_I = (cosA - outter) / (inner - outter);
    }else if(outter > cosA){
        direction_I = 0;
    }

    highp float cosTheta = dot(L, N);
    highp float cosAlpha = dot(R, V);
    highp float cosAlphaN = pow(max(cosAlpha, 0.), 40.);

    //cosTheta = 0;
    //cosAlphaN  = 0;
    return vec4(   min(Ca.x * Ga.x + direction_I * distance_I * max(Cd.x * Ld.x * cosTheta, 0.) + direction_I * distance_I * min(Cs.x * Ls.x * cosAlphaN, 0.), 1),
                   min(Ca.y * Ga.y + direction_I * distance_I * max(Cd.y * Ld.y * cosTheta, 0.) + direction_I * distance_I * min(Cs.y * Ls.y * cosAlphaN, 0.), 1),
                   min(Ca.z * Ga.z + direction_I * distance_I * max(Cd.z * Ld.z * cosTheta, 0.) + direction_I * distance_I * min(Cs.z * Ls.z * cosAlphaN, 0.), 1),
                   1);
}

void main(void)
{
    highp vec3 convertedNor = vec4(normalize(transpose(inverse(model)) * norAttr)).xyz;
    highp vec3 convertedPos = vec4(model * posAttr).xyz;

    //col = getColor(convertedNor);
    //col = vec4(1., 1., 1., 1.);

    col = spot_light(convertedPos, convertedNor, view_point.xyz, light_point.xyz, light_direction.xyz, 0.999, 0.9);
    gl_Position = view * model * posAttr;
}
