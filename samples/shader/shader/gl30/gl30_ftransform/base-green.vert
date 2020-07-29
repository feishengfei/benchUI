#version    //version under 1.4 

precision mediump float;

in vec4 a_v4Position;

void main()
{

    gl_Position = a_v4Position * ftransform();
//    gl_Position = a_v4Position;
}
