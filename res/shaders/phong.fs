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

uniform sampler2D u_texture_col;
uniform sampler2D u_texture_nor;
uniform float u_shininess;
uniform vec3 u_option;

void main()
{
	// Set the ouput color per pixel
	vec4 texture_color = texture2D(u_texture_col, v_uv);
	vec4 texture_normal =  texture2D(u_texture_nor, v_uv);
	vec3 Ip;

	vec3 L = v_lightPos - v_world_position;
	vec3 V = v_eye - v_world_position;
	vec3 R = reflect(-L, v_world_normal);
	L = normalize(L);
	V = normalize(V);
	R = normalize(R);

	float dot1 = dot(L, v_world_normal);
	float dot2 = dot(R, V);
	
	vec3 ka = v_ka;
	vec3 kd = v_kd;
	vec3 ks = v_ks;

    // Check the usage of each texture
    if (u_option.x == 1.0) { // Use color texture for diffuse and ambient
        ka *= texture_color.xyz;
        kd = texture_color.xyz;
        //ks = vec3(texture_color.a); 
    }

    if (u_option.y == 1.0) { // Use specular texture
        ks = vec3(texture_color.a); // Use alpha channel as specular coefficient
    }

    if (u_option.z == 1.0) { // Use normal texture
        float mix_factor = 0.5;
        vec3 final_normal = mix(v_world_normal, texture_normal, mix_factor);
        R = reflect(-L, final_normal);
        dot1 = max(dot(L, final_normal), 0.0);
        dot2 = max(dot(R, V), 0.0);
    }

    dot1 = clamp(dot1, 0.0, 1.0);
    dot2 = clamp(dot2, 0.0, 1.0);

	Ip = ka*v_Ia + (kd*dot1*v_Id + ks*pow(dot2, u_shininess)*v_Is);
	
	gl_FragColor = vec4(Ip, 1.0);
}