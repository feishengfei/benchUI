#version 430 core 

precision mediump float;
in vec4 vfColor;

out vec4 FragColor;

void main()
{		
    if(gl_PointCoord.x < 0.5 && gl_PointCoord.y < 0.5)
	FragColor = vfColor;
    else if(gl_PointCoord.x < 0.5 && gl_PointCoord.y > 0.5)
	FragColor = vec4(0.0, 1.0, 0.0, 1.0);
    else if(gl_PointCoord.x > 0.5 && gl_PointCoord.y > 0.5)
        FragColor = vec4(0.0, 0.0, 1.0, 1.0);
    else
        FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}
