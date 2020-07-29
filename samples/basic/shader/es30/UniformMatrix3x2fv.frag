#version 300 es  
precision mediump float;
/*out vec4 gl_FragColor;   
void main()
{
   gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );
}
*/
in vec4 v_v4FillColor;
out vec4 FragColor; 
uniform mat3x2 cameraProjectionMatrix;

void main()
{
	vec4 tmpColor = vec4(cameraProjectionMatrix[0][0], cameraProjectionMatrix[1][0], cameraProjectionMatrix[2][0], 0.0);
        FragColor = v_v4FillColor + tmpColor;
}
