#version 310 es  
precision mediump float;

layout(binding = 0, offset = 0) uniform atomic_uint counter;

void main()
{
        atomicCounterIncrement(counter);
}
