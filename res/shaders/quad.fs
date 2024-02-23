varying vec2 v_uv;
uniform float u_option;
uniform float u_aspectRatio;

float dx = distance(v_uv.x,0.5);
float dy = distance(v_uv.y,0.5);
float d = sqrt(dx*dx + dy*dy);

void main()
{
	//colors
	vec3 white = vec3(0,0,0);
	vec3 red = vec3(1,0,0);
	vec3 green = vec3(0,1,0);
	vec3 blue = vec3(0,0,1);
	vec3 black = vec3(1,1,1);

	// 1.a
	if(u_option == 1.1){
		vec3 color = mix(blue, red, v_uv.x);
		gl_FragColor = vec4(color,1.0);
	}

	//1.b
	if(u_option == 2.1){
		vec2 center = vec2(u_aspectRatio*0.5);
		vec4 color = vec4(black, 1.0);
		float d = distance(v_uv, center);
		gl_FragColor = d * color;
	}

	
}
