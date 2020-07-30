#version 430 core

out vec4 FragColor;

layout(location = 1) uniform vec4 draw_color = vec4(0.5, 0.8, 1.0, 1.0);

void main(){
	FragColor = draw_color;
}




