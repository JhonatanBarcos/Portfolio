#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "entity.h"

Mesh quad = Mesh();
Shader* shader = new Shader();
Texture* texture = new Texture();

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->mouse_state = 0;
	this->time = 0.f;
	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(nullptr);
	this->framebuffer.Resize(w, h);
}

Application::~Application()
{
}

void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;

	//Init camera
	Vector3 eye = Vector3(0.0f, 0.0f, 5.0f);
	Vector3 center = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	camera.LookAt(eye, center, up);
	camera.SetPerspective(45, static_cast<float>(framebuffer.width) / framebuffer.height, 0.01f, 100);
/*
	//Init entities
	entity_anna = new Entity("meshes/anna.obj", modelM);
	entity_anna->SetMatrix(0.0f, 0.0f, 0.0f);

	entity_cleo = new Entity("meshes/cleo.obj", modelM1);
	entity_cleo->SetMatrix(1.0f, 0.0f, 0.0f);

	entity_lee = new Entity("meshes/lee.obj", modelM2);
	entity_lee->SetMatrix(-1.0f, 0.0f, 0.0f);
*/

	//Init shader
	shader = Shader::Get("shaders/quad.vs", "shaders/quad.fs");
	
	//Init texture
	texture = Texture::Get("res/images/fruits.png");

	//Init quad mesh
	quad.CreateQuad();


	

}

// Render one frame
//key pressed
void Application::Render(void)
{

	//clear the frame buffer and the depth buffer
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->Enable();
	shader->SetFloat("u_option", key);
	//shader->SetTexture("u_texture", texture);
	quad.Render();

	shader->Disable();



	//framebuffer.Render();

};

// Called after render
void Application::Update(float seconds_elapsed)
{


}

//keyboard press event
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch(event.keysym.sym) {
		case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
		case SDLK_1: // Handle SDLK_1 separately
			if (event.keysym.mod & KMOD_LSHIFT && event.keysym.sym == SDLK_a) { // Check for combination of SDLK_1 and SDLK_a
				key = 1.0;
			}
			if(event.keysym.mod & KMOD_LSHIFT && event.keysym.sym == SDLK_b) { // Check for combination of SDLK_1 and SDLK_b
				key = 2.0;
			}
			break;
		case SDLK_2: key = 2.0; break;
		case SDLK_3: key = 3; break;
		case SDLK_4: key = 4; break;
	}
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
		leftClick = true;
		mouse_position.x = static_cast<float>(event.x);
		mouse_position.y = static_cast<float>(event.y);

	}

	if (event.button == SDL_BUTTON_RIGHT) {

		rightClick = true;
		//clean screen
		framebuffer.Fill(Color::BLACK);

		mouse_position.x = static_cast<float>(event.x);
		mouse_position.y = static_cast<float>(event.y);

		float normalizedX = (2.0f * mouse_position.x) / window_width - 1.0f;
		float normalizedY = 1.0f - (2.0f * mouse_position.y) / window_height;


		Vector3 center = Vector3(normalizedX, normalizedY, camera.GetCenter().z);

		camera.LookAt(camera.GetEye(),center,camera.GetUp());
		camera.UpdateViewMatrix();
	}
	
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
		leftClick = false;
	}

	if (event.button == SDL_BUTTON_RIGHT) {
		rightClick = false;
	
	}

}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT) {
		//clean screen
		framebuffer.Fill(Color::BLACK);

		//orbit
		camera.Orbit(-mouse_delta.x * 0.01, Vector3::UP);
		camera.Orbit(-mouse_delta.y * 0.01, Vector3::RIGHT);
	}


}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;

	//clean screen
	framebuffer.Fill(Color::BLACK);

	//zoom
	camera.Zoom(dy < 0 ? 1.1 : 0.9);

}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}