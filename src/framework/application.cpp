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
	Vector3 eye = Vector3(0.0f, 0.0f, 5.0f);
	Vector3 center = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	camera.LookAt(eye, center, up);
	camera.SetPerspective(45, static_cast<float>(framebuffer.width) / framebuffer.height, 0.01f, 100);

	//Init bools
	isPerspective = true;
	isOrthographic = false;
	changeFar = false;
	changeNear = false;
	changeFOV = false;

	//Init entities
	entity_anna = new Entity("meshes/anna.obj", modelM);
	entity_anna->SetMatrix(0.0f, 0.0f, 0.0f);

	entity_cleo = new Entity("meshes/cleo.obj", modelM1);
	entity_cleo->SetMatrix(1.0f, 0.0f, 0.0f);

	entity_lee = new Entity("meshes/lee.obj", modelM2);
	entity_lee->SetMatrix(-1.0f, 0.0f, 0.0f);

	//Default render mode
	entity_anna->mode = Entity::eRenderMode::TRIANGLES;

}

// Render one frame
//key pressed
void Application::Render(void)
{
	if (key == 4){
		//Reset entity matrix
		entity_anna->SetMatrix(0.0f, 0.0f, 0.0f);
		//Render mesh
		entity_anna->Render(&framebuffer, &camera, Color::WHITE);
		//render mesh with bufferz



	}

	//KEY INSTRUCTIONS
	//1. Toggle (activate/deactivate) between PLAIN COLOR/INTERPOLATED vertex colors
	if (key == 1) {
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));
		
		// Toggle render mode
		if (entity_anna->mode == Entity::eRenderMode::TRIANGLES) {
			entity_anna->mode = Entity::eRenderMode::TRIANGLES_INTERPOLATED;
		} else if (entity_anna->mode == Entity::eRenderMode::TRIANGLES_INTERPOLATED){
			entity_anna->mode = Entity::eRenderMode::TRIANGLES;
		}

	}
	

	//2. Toggle between OCCLUSIONS and NO OCCLUSIONS
	if (key == 2){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));

		//Render
		entity_anna->Render(&framebuffer, &camera, Color::YELLOW);
		entity_cleo->Render(&framebuffer, &camera, Color::PURPLE);
		entity_lee->Render(&framebuffer, &camera, Color::RED);
	}


	//3. Toggle between USE MESH TEXTURE and USE PLAIN COLOR colors
	if (key == 3){
		//Config screen
		framebuffer.Fill(Color::BLUE);
		
		camera.SetOrthographic(-2, 2, -2, 2, 0.01f, 100);
		isPerspective = false;
		isOrthographic = true;
		
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
		case SDLK_c: key = 1; break;
		case SDLK_z: key = 2; break;
		case SDLK_t: key = 3; break;
		case SDLK_1: key = 4; break;
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