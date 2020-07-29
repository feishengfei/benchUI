#version 430 core

in vec2 vpos;
out vec4 fColor;

void main()
{
    float anglex = radians(vpos.x);
    float angley = radians(vpos.y);
    float colX = (sin(anglex)+1)/2.0;
    float colY = (cos(anglex)+1)/2.0;
    if(vpos.x == 0.0 && vpos.y > 0.0){
    fColor = vec4(1.0, 0.0, 0.0, 1.0);}
    else if(vpos.x == 0.0 && vpos.y < 0.0){
    fColor = vec4(1.0, 0.0, 1.0, 1.0);
    }else if(vpos.x > 0.0 && vpos.y == 0.0){
    fColor = vec4(0.0, 0.0, 1.0, 1.0);
    }else if(vpos.x < 0.0 && vpos.y == 0.0){
    fColor = vec4(0.0, 1.0, 1.0, 1.0);
    }else if(vpos.x > 0.0 && vpos.y > 0.0){
    fColor = vec4(colX, colY, 1.0, 1.0);
    }else if(vpos.x > 0.0 && vpos.y < 0.0){
    fColor = vec4(colX, 0.0, 1.0, 1.0);
    }else if(vpos.x < 0.0 && vpos.y > 0.0){
    fColor = vec4(colX, 0.0, colY, 1.0);
    }else if(vpos.x < 0.0 && vpos.y < 0.0){
    fColor = vec4(0.0, 0.0, colY, 1.0);
    }
}
