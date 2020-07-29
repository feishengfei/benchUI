#version 100
attribute vec4 attributePosition; 
attribute vec3 attributeNormals;  
uniform mat4  rotationMatrix;
uniform mat4 scaleMatrix;
uniform mat4 cameraProjectionMatrix;
uniform mat4 lightProjectionMatrix; 
uniform mat4 lightViewMatrix;
uniform vec3 cameraPosition;
uniform vec3 lightPosition; 
uniform vec4 cubesPosition;

varying vec4 outputLightPosition;
varying vec3 outputNormal;
varying vec4 outputPosition;
varying mat4 outputViewToTextureMatrix;

void main()
{
	mat4 cameraViewMatrix;
	
	vec3 modelPosition;
	mat4 modelViewMatrix;
	mat4 modelViewProjectionMatrix;
	
	modelPosition = vec3(cubesPosition.x, cubesPosition.y, cubesPosition.z);
	
	mat4 translationMatrix = mat4 (1.0, 0.0, 0.0, 0.0, 
					0.0, 1.0, 0.0, 0.0, 
					0.0, 0.0, 1.0, 0.0, 
		modelPosition.x, modelPosition.y, modelPosition.z, 1.0);
	
		cameraViewMatrix = mat4 ( 1.0, 0.0,   0.0,  0.0, 
					0.0, 1.0,   0.0,  0.0, 
					0.0, 0.0,   1.0,  0.0, 
			-cameraPosition.x,  -cameraPosition.y, -cameraPosition.z, 1.0);
											
		modelViewMatrix = cameraViewMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		modelViewProjectionMatrix = cameraProjectionMatrix * modelViewMatrix;

	const mat4 biasMatrix = mat4(0.5, 0.0, 0.0, 0.0,
						         0.0, 0.5, 0.0, 0.0,
						         0.0, 0.0, 0.5, 0.0,
						         0.5, 0.5, 0.5, 1.0);
						   
	outputLightPosition = modelViewMatrix * vec4(lightPosition, 1.0);
	outputNormal        = attributeNormals;
	outputPosition      = modelViewMatrix * attributePosition;

		outputViewToTextureMatrix = biasMatrix * lightProjectionMatrix * lightViewMatrix * cameraViewMatrix;
	
	gl_Position = modelViewProjectionMatrix * attributePosition;
}
