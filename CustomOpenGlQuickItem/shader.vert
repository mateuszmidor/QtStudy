attribute vec4 vertices;
varying vec3 coords;
uniform mat4 mvp_matrix;

void main() {
    gl_Position = mvp_matrix * vertices;
    coords = (vertices.xyz + vec3(1.0)) * 0.5;
}
