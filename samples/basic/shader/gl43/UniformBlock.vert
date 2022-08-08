#version 430 core

in vec4 attributePosition;

uniform vec4 cubesPosition;
uniform cameraPosUniformBlock
{
	mat4 cameraProjectionMatrix;
	vec3 cameraPosition;
};

void main()
{
	/* View matrix calculated from camera point of view. */
	mat4 cameraViewMatrix;
	
	/* Matrices and vectors used for calculating output variables. */
	vec3 modelPosition;
	mat4 modelViewMatrix;
	mat4 modelViewProjectionMatrix;
	
	modelPosition = vec3(cubesPosition.x, cubesPosition.y, cubesPosition.z);
	mat4 translationMatrix = mat4 (1.0, 	        0.0,             0.0,             0.0, 
				       0.0, 	        1.0,             0.0,             0.0, 
				       0.0, 	        0.0,             1.0,             0.0, 
				       modelPosition.x, modelPosition.y, modelPosition.z, 1.0);
	
	cameraViewMatrix = mat4 ( 1.0, 		          0.0,               0.0,              0.0, 
				  0.0, 		          1.0,               0.0,              0.0, 
				  0.0, 		          0.0,               1.0,              0.0, 
				 -cameraPosition.x,  -cameraPosition.y, -cameraPosition.z, 1.0);
	modelViewMatrix = cameraViewMatrix * translationMatrix;
	modelViewProjectionMatrix = cameraProjectionMatrix * modelViewMatrix;

        gl_Position = modelViewProjectionMatrix * attributePosition;
}
