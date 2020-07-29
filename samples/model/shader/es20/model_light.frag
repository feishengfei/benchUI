/**
 */
#version 100

precision mediump float;

varying vec4 outputLightPosition; 	   
varying vec3 outputNormal;              
varying vec4 outputPosition;            
varying mat4 outputViewToTextureMatrix; 

uniform vec4 		    colorOfGeometry;
uniform vec3  			lightDirection;

#define PI 3.14159265358979323846

struct DirectionalLight
{
	float ambient;
	vec3  color;
	vec3  direction;
};

struct SpotLight
{
	float ambient;
	float angle;
	float spotExponent;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	vec3  direction;
	vec4  position;
};

void main()
{
	DirectionalLight directionalLight;
	
	directionalLight.ambient   = 0.91; 
	directionalLight.color     = vec3(1.0,  1.0,  1.0);
	directionalLight.direction = vec3(0.2, -1.0, -0.2);

	SpotLight spotLight;

	spotLight.ambient              = 2.91;
	spotLight.angle                = 15.0;
	spotLight.spotExponent         = 5.0;
	spotLight.constantAttenuation  = 1.0;
	spotLight.linearAttenuation    = 0.1;
	spotLight.quadraticAttenuation = 0.9;
	spotLight.direction            = lightDirection; 
	spotLight.position             = outputLightPosition;

	/* Compute distance between the light position and the fragment position. */
	float xDistanceFromLightToVertex = (spotLight.position.x - outputPosition.x);
	float yDistanceFromLightToVertex = (spotLight.position.y - outputPosition.y);
	float zDistanceFromLightToVertex = (spotLight.position.z - outputPosition.z);
	float distanceFromLightToVertex  = sqrt((xDistanceFromLightToVertex * xDistanceFromLightToVertex) +
		(yDistanceFromLightToVertex * yDistanceFromLightToVertex) +
		(zDistanceFromLightToVertex * zDistanceFromLightToVertex));
	/* Directional light. */
	/* Calculate the value of diffuse intensity. */
	float diffuseIntensity = max(0.0, -dot(outputNormal, normalize(directionalLight.direction)));

    /* Calculate color for directional lighting. */
    vec4 color = colorOfGeometry * vec4(directionalLight.color * (directionalLight.ambient + diffuseIntensity), 1.0);
	
	// Spot light.
	float normalDotLight = max(dot(normalize(outputNormal), normalize(-spotLight.direction)), 0.0);
		
	vec3 vectorFromLightToFragment = vec3(outputPosition.x - spotLight.position.x, 
			  outputPosition.y - spotLight.position.y, 
			  outputPosition.z - spotLight.position.z);
										  
	float cosinusAlpha = dot(spotLight.direction, vectorFromLightToFragment) /
                             (sqrt(dot(spotLight.direction, spotLight.direction)) * 
			      sqrt(dot(vectorFromLightToFragment, vectorFromLightToFragment)));
	float alpha = acos(cosinusAlpha);
    float spotEffect = dot(normalize(spotLight.direction), normalize(vectorFromLightToFragment));
			
    spotEffect = pow(spotEffect, spotLight.spotExponent);
			
    float attenuation = spotEffect / (spotLight.constantAttenuation  +
	 spotLight.linearAttenuation    * distanceFromLightToVertex +
	 spotLight.quadraticAttenuation * distanceFromLightToVertex * distanceFromLightToVertex);
	
    color = color / 0.5 + (attenuation * (normalDotLight + spotLight.ambient));

    float angle = acos(dot(normalize(outputNormal), normalize(spotLight.direction)));

    float scaleIntensity = smoothstep(0.0, PI, angle);
    vec4 scaleVector = vec4(scaleIntensity, scaleIntensity, scaleIntensity, 1.0);
    color *= scaleVector;
    gl_FragColor = color;
}
