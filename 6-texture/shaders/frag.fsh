#version 330

varying highp vec3 convertedPos;
varying lowp vec3  convertedNor;
varying highp vec3 Pos;
varying lowp vec3  Nor;

uniform highp vec4 Ga;
uniform highp vec4 Ld;
uniform highp vec4 Ls;

uniform highp vec4 light_direction;
uniform highp vec4 view_point;

uniform sampler2D tex;
uniform sampler2D norm;

#define PI 3.1415926538

uniform highp mat4 model_TI;

highp vec3 calcNorm(vec3 localNormal, vec2 uv)
{
    // Рассчитываем базисные вектора с.о. нормали (tangent space)
    vec3 n = normalize( localNormal.xyz );
    vec3 t = normalize( cross(n, vec3(1,1,1)) );
    vec3 b = cross(n, t);
    // Достаём нормаль из карты высот
    vec3 normal = texture( norm, uv ).rgb;
    normal = normalize( normal * 2.0 - 1.0 );
    // Рассчитываем результирующую нормаль
    vec3 resultingNormal = normalize( normal.r * t + normal.g * b + normal.b * n );

    return resultingNormal;
}

highp vec4 directional_light(highp vec3 point, highp vec3 normal, highp vec3 view_position, highp vec3 light_direction){
    highp vec3 L = -normalize(light_direction);
    //highp vec3 N = normalize(normal);
    vec2 uv = vec2(-(atan(Pos.z, Pos.x)) / 2., acos(Pos.y)) / PI;
    highp vec3 N = vec4(model_TI * -vec4(calcNorm(Nor, uv), 1.)).xyz;
    highp vec3 R = reflect(L, N);
    highp vec3 V = -normalize(view_position - point);
    highp float cosTheta = dot(L, N);
    highp float cosAlpha = dot(R, V);
    highp float cosAlphaN = pow(max(cosAlpha, 0.), 20.);
    highp vec3 factor = vec3(0., max(cosTheta, 0.), max(cosAlphaN, 0.));
    vec4 Ca = texture2D(tex, uv);
    vec4 Cd = texture2D(tex, uv);
    vec4 Cs = texture2D(tex, uv);
    //vec4 Ca = vec4(0.5, 0.5, 0.5, 1.);
    //vec4 Cd = vec4(0.5, 0.5, 0.5, 1.);
    //vec4 Cs = vec4(0.5, 0.5, 0.5, 1.);
    return vec4(   Ca.x * Ga.x + max(Cd.x * Ld.x * cosTheta, 0.) + max(Cs.x * Ls.x * cosAlphaN, 0.),
                   Ca.y * Ga.y + max(Cd.y * Ld.y * cosTheta, 0.) + max(Cs.y * Ls.y * cosAlphaN, 0.),
                   Ca.z * Ga.z + max(Cd.z * Ld.z * cosTheta, 0.) + max(Cs.z * Ls.z * cosAlphaN, 0.),
                   1);
}


void main(void)
{
    gl_FragColor = directional_light(convertedPos, convertedNor, view_point.xyz, light_direction.xyz);
}
