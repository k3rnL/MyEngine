#version 330 core


layout(location = 0) in vec3 vertex;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  MVP * vec4(vertex, 1);
    //gl_Position.xyz = vertex;
    //gl_Position.w = 1;
}
