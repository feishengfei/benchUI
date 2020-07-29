#version 300 es  

out float tf;
void main()
{
  gl_PointSize = 20.0;
  gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
  tf = 1.0;
}
