#version 330 core
out vec4 FragColor;

uniform vec2 pointPos;

void main(){
    if(dist(gl_FragCoord, pointPos) < 10){
        FragColor = vec4(1.0, 1.0, 0.1, 1.0);
    }
    else{
        discard;
    }
}
