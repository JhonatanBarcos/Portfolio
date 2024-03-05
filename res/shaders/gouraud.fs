varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;
varying vec3 v_Ip;

uniform sampler2D u_texture;

void main()
{
	//vec4 texture_color = texture2D(u_texture, v_uv);
	gl_FragColor = vec4(v_Ip, 1.0);
}
