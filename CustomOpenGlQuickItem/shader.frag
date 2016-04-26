//uniform lowp float t;
varying vec3 coords;
void main() {
    gl_FragColor = vec4(coords.x, coords.y, coords.z, 1.0);
}
