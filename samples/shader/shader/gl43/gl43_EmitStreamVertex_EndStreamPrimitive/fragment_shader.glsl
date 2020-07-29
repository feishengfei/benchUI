#version  //GLSL Version 3.20; OpenGL es 3.2

precision mediump float;
//in vec4 gColor;
out vec4 FragColor;



void main()
{
//		FragColor = gColor;
		FragColor = vec4(1.0 , 0.0, 0.0, 1.0);
}

//fColor = texture(Texture, texCoord) * object_color;
//fColor = object_color;
