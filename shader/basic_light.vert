#version 330 core


layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 vertex_normal;

// Values that stay constant for the whole mesh.
uniform mat4 projection; // Projected view
uniform mat4 view;
uniform mat4 model_view; // Camera view
uniform vec3 camera_position;

out vec3 to_shade_vertex;
out vec3 normal;
out vec3 vector_to_camera;

void main(){

    // compute true position of actual vertex and pass it to fragment shader
    to_shade_vertex = (model_view * vec4(vertex, 1)).xyz;
    normal = vertex_normal;
    vector_to_camera = camera_position - (view * model_view * vec4(vertex, 1)).xyz;
    //vector_to_camera = vec3(0, 0, 0) - (view * model_view * vec4(vertex, 1)).xyz;
    vector_to_camera = normalize(vector_to_camera);

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  projection * view * model_view * vec4(vertex, 1);

}
