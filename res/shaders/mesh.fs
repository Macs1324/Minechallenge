#version 330
const vec3 lightPos = normalize(vec3(0.0, 1.0, 1.0));
in vec2 fUv;
in vec3 fNormal;
in vec3 fPos;
uniform sampler2D sprite;
out vec4 color;
void main()
{
    vec3 camera_dir = normalize(-fPos);
    vec3 half_direction = normalize(normalize(lightPos) + camera_dir);
    float specular = pow(max(dot(half_direction, normalize(fNormal)), 0.0), 16.0);
    float light = dot(fNormal, lightPos);
    color = mix(mix(texture(sprite, fUv) / 2.0, texture(sprite, fUv), 0.5 + (light / 2.0)), vec4(1.0, 1.0, 1.0, 1.0), (specular / 3));
    // color = texture(sprite, fUv);
}