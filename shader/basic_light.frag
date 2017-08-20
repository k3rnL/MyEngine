/**
 * @Author: daniel_b
 * @Date:   2017-07-27T03:32:34+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-30T20:32:03+02:00
 */



#version 330 core

in vec3 to_shade_vertex;

uniform vec3 mat_color;
uniform vec3 light_pos;

uniform mat4 model_rotation; // Camera view
uniform mat4 model_view;

uniform struct MaterialData
{
              vec3  diffuse_color;
              int   diffuse_map;
}              mt_data;

uniform sampler2D diffuse_map;

out vec3 color;
in vec3 normal_input;
in vec3 vector_to_camera;
in vec2 uv;

void main(){

  vec3 normal = mat3(model_view) * normal_input;

  vec3 light_vector = normalize(light_pos - to_shade_vertex);

  mat4 rot = model_rotation * model_rotation;
  float angle = clamp(dot(light_vector, normalize(normal)), 0.0, 1.0);
  // float angle = clamp(dot((rot * vec4(light_vector, 0)).xyz, normalize(normal)), 0.0, 1.0);

  if ((bool) mt_data.diffuse_map == 1)
    color = vec3(texture(diffuse_map, uv)) * angle;
  else
    color = mat_color * angle;

  vec3 vector_light_reflected = normalize(reflect(-light_vector, normal));
  angle = clamp(dot(vector_light_reflected, vector_to_camera), 0.0, 0.6);
  angle = pow(1.5, angle);

  color = color * angle;
  // color = 0.5 + 0.5 * normal;
}
