//uniform lowp float t;
varying vec3 coords;
varying float lightness;

void main() {
    gl_FragColor = vec4(lightness, lightness, lightness, 1.0);
}
