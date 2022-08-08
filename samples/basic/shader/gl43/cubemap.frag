#version 430 core
precision mediump float;
uniform samplerCube s_texture;
uniform vec3 camera_pos;
in vec3 v_normal;
in vec3 position;
out vec4 gl_FragColor;
void main() {
   float ratio = 1.0/1.52;
   vec3 I = normalize(camera_pos - position);
   vec3 R = reflect(I, normalize(v_normal));
   //vec3 R = refract(I, normalize(v_normal), ratio);
   gl_FragColor = vec4(textureCube( s_texture, R).rgb, 1.0);
   //gl_FragColor = texture( s_texture, v_normal );
}   
