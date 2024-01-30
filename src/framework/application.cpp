#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "button.h"
#include "entity.h"



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
	camera = Camera();
	camera.LookAt(Vector3(0,0, -4), Vector3(0, 0.25, 0), Vector3(0, 30, 0));
	camera.SetPerspective(45,framebuffer.width/framebuffer.height, 0.01,100);

	//Init entity
	entity_anna = new Entity("meshes/anna.obj", modelM);
	entity_anna->SetMatrix(0.0, -0.1, 0.0);
}

// Render one frame
//key pressed
void Application::Render(void)
{
	//KEY INSTRUCTIONS
	//1. Draw sigle entity
	if (key == 1){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));
		entity_anna->Render(&framebuffer, &camera, Color::WHITE);

	}
	
	//2. Draw Rectangle
	if (key == 2){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));
	}
	//3. Draw Circle
	if (key == 3){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));
	}
	//4. Draw Triangle
		if (key == 4){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));
		}

	//5. Paint
	if (key == 5){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));
	}

	//6. Animation
	if (key == 6){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));
	}
	
	
	framebuffer.Render();
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
		case SDLK_1: key = 1; break;
		case SDLK_2: key = 2; break;
		case SDLK_3: key = 3; break;
		case SDLK_4: key = 4; break;
		case SDLK_5: key = 5; break;
		case SDLK_6: key = 6; break;
	}
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {

	}
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {

	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{

}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;

	// ...
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}