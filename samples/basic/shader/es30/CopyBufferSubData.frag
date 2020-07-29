precision mediump float;
/*out vec4 gl_FragColor;   
void main()
{
   gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );
}
*/
/*
in vec4 v_v4FillColor;
out vec4 FragColor; 

void main()
{
        FragColor = v_v4FillColor;
}
*/
varying vec4 v_v4FillColor;

void main()
{
        gl_FragColor = v_v4FillColor;
}
