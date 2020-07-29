#version 430 core


layout(location = 0) in vec4 vPosition;

out vec4 vocolor;

void main()
{
    gl_Position = vPosition;
    if(gl_Position.x < 0.0){
    vocolor = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else if(gl_Position.x == 0.0){
    vocolor = vec4(0.0, 1.0, 0.0, 1.0);
    }
    else{
    vocolor = vec4(0.0, 0.0, 1.0, 1.0);
    }
}
