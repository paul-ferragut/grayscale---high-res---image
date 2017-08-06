#version 120


varying vec2 texCoordVarying;

void main() {
gl_TexCoord[0] = gl_MultiTexCoord0;
gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
