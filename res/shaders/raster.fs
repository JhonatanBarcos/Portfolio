// This variables comes from the vertex shader
// They are baricentric interpolated by pixel according to the distance to every vertex
varying vec3 v_world_normal;
varying vec2 v_uv;
uniform sampler2D u_texture;

void main()
{
	// Muestreamos la textura utilizando las coordenadas de textura
	vec4 texture_color = texture2D(u_texture, v_uv);

	// Asignamos el color de la textura al fragmento
	gl_FragColor = texture_color;
}
