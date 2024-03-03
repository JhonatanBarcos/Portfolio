uniform mat4 u_model;
uniform mat4 u_viewprojection;
uniform vec3 u_ka;
uniform vec3 u_kd;
uniform vec3 u_ks;
uniform vec3 u_Id;
uniform vec3 u_Is;
uniform vec3 u_Ia;
uniform vec3 u_lightPos;
uniform vec3 u_eye;
uniform float u_shininess;

// Variables to pass to the fragment shader
varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;
varying vec3 v_final_color;

//here create uniforms for all the data we need here

void main()
{	
	v_uv = gl_MultiTexCoord0.xy;
	//apply formula
	vec3 Ip;

	// Convert local position to world space
	vec3 world_position = (u_model * vec4( gl_Vertex.xyz, 1.0)).xyz;
	
	// Convert local normal to world space
	vec3 world_normal = (u_model * vec4( gl_Normal.xyz, 0.0)).xyz;

	vec3 L = u_lightPos - world_position;
	vec3 V = u_eye - world_position;
	vec3 R = reflect(-L, world_normal);
	L = normalize(L);
	V = normalize(V);
	R = normalize(R);

	float dot1 = dot(L, world_normal);
	float dot2 = dot(R, V);
	dot1 = clamp(dot1, 0.0, 1.0);
	dot2 = clamp(dot2, 0.0, 1.0);

	Ip = u_ka*u_Ia + (u_kd*dot1*u_Id + u_ks*pow(dot2, u_shininess)*u_Is);

	// Pass them to the fragment shader interpolated
	v_world_position = world_position;
	v_world_normal = world_normal;
	v_final_color = Ip;
	
	// Project the vertex using the model view projection matrix
	gl_Position = u_viewprojection * vec4(world_position, 1.0); //output of the vertex shader
}