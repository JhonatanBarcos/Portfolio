varying vec2 v_uv;
uniform float u_option;
uniform float u_aspectRatio;
uniform sampler2D u_texture;

float dx = distance(v_uv.x,0.5);
float dy = distance(v_uv.y,0.5);
float d = sqrt(dx*dx + dy*dy);

void main()
{
	//colors
	vec3 white = vec3(1,1,1);
	vec3 red = vec3(1,0,0);
	vec3 green = vec3(0,1,0);
	vec3 blue = vec3(0,0,1);
	vec3 black = vec3(0,0,0);


	//APARTAT 1

	// 1.a
	if(u_option == 1.1){
		// Interpolamos entre el color rojo y el azul basado en la coordenada de textura
		vec3 color = mix(blue, red, v_uv.x);

		// Asignamos el color al fragmento
		gl_FragColor = vec4(color,1.0);
	}

	//1.b
	if(u_option == 1.2){
		// Utilizamos d calculado previamente para calcular el color final
		vec3 final_color = vec3(d);
		
		// Asignamos el color al fragmento
		gl_FragColor = vec4(final_color, 1.0);	
	}

	//1.c
	if(u_option == 1.3){

		vec3 color = vec3(step(0.1, mod(v_uv.x, 0.2)), 0.0, 1.0 - step(0.1, mod(v_uv.y, 0.2)));  
		// Asignamos el color al fragmento
		gl_FragColor = vec4(color, 1.0);
	}

	//1.d
	if (u_option == 1.4){
		// Definimos las dimensiones de la cuadrícula
		vec2 gridDimension = vec2(16.0);
		
		// Calculamos el color de la cuadrícula basado en las coordenadas de textura
		vec2 gridColor = floor(v_uv * gridDimension) / gridDimension;
		
		// Asignamos el color al fragmento
		gl_FragColor = vec4(gridColor, 0.0, 1.0);
	}

	//1.e
	if(u_option == 1.5){
		// Definimos las dimensiones de la cuadrícula
		vec2 gridDimension = vec2(16.0);

		// Calcular el color de la cuadrícula basado en las coordenadas de textura
		vec2 gridCell = floor(v_uv * gridDimension);
		float isEven = mod(gridCell.x + gridCell.y, 2.0); // Alternamos entre 0 y 1
		vec3 gridColor = vec3(isEven); // Blanco par y negro impar
		
		// Asignamos el color resultante al fragmento
		gl_FragColor = vec4(gridColor, 1.0);
	}

	//1.f
	if (u_option == 1.6) {
		// Calculamos la coordenada y de la sinusoide usando la función sin
		float y = step(v_uv.y, 0.2 * sin(2.0 * 3.14159 * v_uv.x) + 0.5);
		
		// Calculamos la distancia entre la coordenada y de la sinusoide y la coordenada y del píxel
		float dist = abs(v_uv.y - y);
		
		// Creamos el color que se mostrará en pantalla, mezclando entre verde y negro según la distancia
		vec3 color = mix(green, black, dist);
		
		// Asignamos el color resultante al fragmento
		gl_FragColor = vec4(color, 1.0);
	}


	//APARTAT 2

	//2.a
	if (u_option == 2.1){
		// Obtenemos el color del fragmento de la textura en las coordenadas de textura v_uv
		vec4 texture_color = texture2D(u_texture, v_uv);

		// Calculamos la intensidad de gris del color del fragmento
		float gray = dot(texture_color.rgb, vec3(0.3333));

		// Creamos un nuevo color para el fragmento utilizando la intensidad de gris 
		gl_FragColor = vec4(vec3(gray), texture_color.a);
	}
	
	//2.b
	if (u_option == 2.2){
		// Obtenemos el color del fragmento de la textura en las coordenadas de textura v_uv
		vec4 texture_color = texture2D(u_texture, v_uv);

		// Invertimos los colores de la textura
		vec3 inverted_color  = vec3(1.0-texture_color.r,1.0-texture_color.g,1.0-texture_color.b);

		// Creamos un nuevo color para el fragmento utilizando la intensidad de gris 
		gl_FragColor = vec4(inverted_color, texture_color.a);

	}

	//2.c
	if (u_option == 2.3){
		// Obtenemos el color del fragmento de la textura en las coordenadas de textura v_uv
		vec4 texture_color = texture2D(u_texture, v_uv);

		// Aplicamos un filtro de coolor verde a la textura
		vec3 green_filter = green * texture_color.g;

		// Creamos un nuevo color para el fragmento utilizando la intensidad de gris
		gl_FragColor = vec4(green_filter, texture_color.a);
	}

	//2.d
	if (u_option == 2.4){
		// Obtenemos el color del fragmento de la textura en las coordenadas de textura v_uv
		vec4 texture_color = texture2D(u_texture, v_uv);

		// Calculamos la intensidad de gris del color del fragmento
		float gray = dot(texture_color.rgb, vec3(0.3333));

		// Definimos un umbral para la intensidad de gris
		float threshold = 0.5;

		// Creamos un nuevo color para el fragmento utilizando la intensidad de gris con un umbral de 0.5
		gl_FragColor = vec4(vec3(step(threshold, gray)), texture_color.a);
	}

	//2.e
	if (u_option == 2.5){
		// Obtenemos el color del fragmento de la textura en las coordenadas de textura v_uv
		vec4 texture_color = texture2D(u_texture, v_uv);

		// Calculamos el valor de desenfoque interpolando basadonos en la distancia al centro
		float vignetting = smoothstep(0.0, 0.9, d);

		// Aplicamos el desenfoque al color del fragmento mezclando con el color original
		vec3 vignettingColor = mix(texture_color, texture_color - white, vignetting);

		// Asignamos el color resultante al fragmento
		gl_FragColor = vec4(vignettingColor,1.0);
	}

	//2.f
	if (u_option == 2.6){
		// Definir el número de muestras de desenfoque
		int numSamples = 10;

		// Calcular el tamaño del paso para cada muestra
		vec2 stepSize = 3.0 / vec2(textureSize(u_texture, 0));

		// Inicializar el color acumulado
		vec4 accumulatedColor = vec4(0.0);

		// Realizar el desenfoque muestreando los píxeles vecinos
		for (int i = -numSamples; i <= numSamples; i++) {
			for (int j = -numSamples; j <= numSamples; j++) {
				// Calcular el desplazamiento para la muestra actual
				vec2 offset = vec2(float(i), float(j)) * stepSize;

				// Muestrear el color de la textura en la posición desplazada
				vec4 sampleColor = texture2D(u_texture, v_uv + offset);

				// Acumular el color
				accumulatedColor += sampleColor;
			}
		}

		// Calcular el color promedio
		vec4 blurredColor = accumulatedColor / float((2 * numSamples + 1) * (2 * numSamples + 1));

		// Asignar el color desenfocado al fragmento
		gl_FragColor = blurredColor;

	}


	//APARTAT 3

	if (u_option == 3.1){
		//
	}

	if (u_option == 3.2){
		//
	}

}

