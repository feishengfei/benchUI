#version 430 core
precision highp float;

uniform double d1;
uniform dvec2 d2;
uniform dvec3 d3;
uniform dvec4 d4;
uniform double dv1;
uniform dvec2 dv2;
uniform dvec3 dv3;
uniform dvec4 dv4;
uniform dmat2 dm2;
uniform dmat3 dm3;
uniform dmat4 dm4;
uniform dmat2x3 dm23;
uniform dmat2x4 dm24;
uniform dmat3x2 dm32;
uniform dmat3x4 dm34;
uniform dmat4x2 dm42;
uniform dmat4x3 dm43;

layout(location = 0) in vec2 a_v2Position;

void main()
{
    dmat4 md1 = dmat4(d1, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,
    					0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0);
    dmat4 md2 = dmat4(d2, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,
    					0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0);
    dmat4 md3 = dmat4(d3, 0.0,  0.0, 0.0, 0.0, 0.0,
    					0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0);
    dmat4 md4 = dmat4(d4,  0.0, 0.0, 0.0, 0.0,
    					0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0);
    dmat4 md1v = dmat4(dv1, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,
    					0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0);
    dmat4 md2v = dmat4(dv2, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,
    					0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0);
    dmat4 md3v = dmat4(dv3, 0.0,  0.0, 0.0, 0.0, 0.0,
    					0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0);
    dmat4 md4v = dmat4(dv4,  0.0, 0.0, 0.0, 0.0,
    					0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0);
    dmat4 mm2 = dmat4(dm2[0], 0.0, 0.0,  dm2[1], 0.0, 0.0,
    					0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0);
    dmat4 mm3 = dmat4(dm3[0], 0.0,  dm3[1], 0.0,
    					dm3[2], 0.0,  0.0, 0.0, 0.0, 0.0);
    dmat4 mm4 = dm4;
    dmat4 mm23 = dmat4(dm23[0], 0.0,  dm23[1], 0.0,
    					0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0);
    dmat4 mm24 = dmat4(dm24[0],  dm24[1],
    					0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0);
    dmat4 mm32 = dmat4(dm32[0], 0.0, 0.0,  dm32[1], 0.0, 0.0,
    					dm32[2], 0.0, 0.0,  0.0, 0.0, 0.0, 0.0);
    dmat4 mm34 = dmat4(dm34[0],  dm34[1],  dm34[2],
    					0.0, 0.0, 0.0, 0.0);
    dmat4 mm42 = dmat4(dm42[0], 0.0, 0.0,  dm42[1], 0.0, 0.0,
    					dm42[2], 0.0, 0.0,  dm42[3], 0.0, 0.0);
    dmat4 mm43 = dmat4(dm43[0], 0.0,  dm43[1], 0.0,
    					dm43[2], 0.0,  dm43[3], 0.0);
    dmat4 trans = md1 + md2 + md3 + md4
    			+ md1v + md2v + md3v + md4v
    			+ mm2 + mm3 + mm4
    			+ mm23 + mm24 + mm32 + mm34 + mm42 + mm43;

    int idx = gl_InstanceID * 2;
    int x = idx / 4;
    int y = idx % 4;
//    gl_Position = vec4(a_v2Position.x + 0.1*gl_InstanceID, a_v2Position.y, 0.0, 1.0);
    gl_Position = vec4(trans[x][y]/2 + a_v2Position.x, trans[x][y+1]/2 + a_v2Position.y, 0.0, 1.0);
}
