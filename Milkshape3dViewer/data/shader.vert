varying float lightness;
uniform mat4 mv_matrix;
uniform mat4 p_matrix;

void main() {
    gl_Position =  p_matrix * mv_matrix * gl_Vertex;
    vec4 normal = mv_matrix * vec4(gl_Normal.xyz, 0.0);
    vec3 lightDir = vec3(0, 0, 1);
    lightness = dot(normal.xyz, lightDir);
}
