varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;
varying vec3 v_final_color;

uniform sampler2D u_texture;

void main()
{
	// Set the ouput color per pixel
	//vec4 texture_color = texture2D(u_texture, v_uv);

	gl_FragColor = vec4(v_final_color, 1.0);
}
