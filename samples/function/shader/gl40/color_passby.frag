#version 430
precision mediump float;

in vec4 Color; 
out vec4 FragColor; 

vec4 re1(vec4 a) {
    float x;
    x = 0.2;
    a.x = x;
    return a;
}

vec4 re2(vec4 b) {
    float x;
    x = 0.3;
    b.y = x;
    return b;
}

vec4 re(vec4 b) {
    vec4 mm = vec4(0.7, 0.5, 0.3, 0.0);
    return b + mm;
}

void main()
{
    vec4 mm = re1(Color);
    vec4 a = re2(mm);
    vec4 b = re(a);
    FragColor = b;
}
