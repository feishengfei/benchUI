#version  //GLSL Version 3.20; OpenGL es 3.2

precision mediump float;

in vec4 object_color;
in vec4 object_position;
in vec2 texCoord;
in vec4 norm;

uniform sampler2D Texture;
uniform vec4 light_color;
uniform vec3 light_position;
uniform int choice;

in vec4 observeDir; 

out vec4 FragColor;



void main()
{
	float ambient_strength = 0.2;
	vec4 ambient = ambient_strength * light_color;

	vec4 lightDir = normalize(vec4(light_position,1.0) - object_position);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * light_color;

	float specularStrength = 0.5;
	vec4 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(-observeDir, reflectDir), 0.0), 64.0);
	vec4 specular = specularStrength * spec * light_color;

	if(0 == choice)
		FragColor = (ambient + diffuse + specular) * object_color * texture(Texture, texCoord);
	else
		FragColor = (ambient + diffuse + specular) * object_color;
}

//fColor = texture(Texture, texCoord) * object_color;
//fColor = object_color;
