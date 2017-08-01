#version 330 core


layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_uv;

// Values that stay constant for the whole mesh.
uniform mat4 projection; // Projected view
uniform mat4 view;
uniform mat4 model_view; // Camera view
uniform vec3 camera_position;

out vec3 to_shade_vertex;
out vec3 normal_input;
out vec3 vector_to_camera;
out vec2 uv;

void main(){

    // compute true position of actual vertex and pass it to fragment shader
    to_shade_vertex = (model_view * vec4(vertex, 1)).xyz;
    normal_input = vertex_normal;
    // vector_to_camera = camera_position - (model_view * vec4(vertex, 1)).xyz;
    vector_to_camera = camera_position - to_shade_vertex;
    vector_to_camera = normalize(vector_to_camera);

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  projection * view * model_view * vec4(vertex, 1);

    uv = vertex_uv;
}
