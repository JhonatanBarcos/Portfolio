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
uniform vec3 u_option;

// Variables to pass to the fragment shader
varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;
varying vec3 v_ka;
varying vec3 v_kd;
varying vec3 v_ks;
varying vec3 v_Id;
varying vec3 v_Ia;
varying vec3 v_Is;
varying vec3 v_lightPos;
varying vec3 v_eye;
varying mat4 v_model;

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

	// Pass them to the fragment shader interpolated
	v_world_position = world_position;
	v_world_normal = world_normal;
	v_ka = u_ka;
	v_kd = u_kd;
	v_ks = u_ks;
	v_Id = u_Id;
	v_Ia = u_Ia;
	v_Is = u_Is;
	v_lightPos = u_lightPos;
	v_eye = u_eye;
	v_model = u_model;
	
	// Project the vertex using the model view projection matrix
	gl_Position = u_viewprojection * vec4(world_position, 1.0); //output of the vertex shader
}