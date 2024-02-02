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

	entity_for = new Entity("meshes/240109Forjado.obj", modelM3);
	entity_for->SetMatrix(0.0f, 0.0f, 0.0f);

}

// Render one frame
//key pressed
void Application::Render(void)
{
	entity_for->SetMatrix(0.0f, 0.0f, 0.0f);
	entity_for->Render(&framebuffer, &camera, Color::WHITE);

	//KEY INSTRUCTIONS
	//1. Draw sigle entity
	if (key == 1){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));

		//Reset entity matrix
		entity_anna->SetMatrix(0.0f, 0.0f, 0.0f);
		//entity_for->SetMatrix(0.0f, 0.0f, 0.0f);

		//Render mesh
		entity_anna->Render(&framebuffer, &camera, Color::WHITE);
		//entity_for->Render(&framebuffer, &camera, Color::WHITE);

	}
	
	//2. Meshes scene animation
	if (key == 2){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));

		//Render
		entity_anna->Render(&framebuffer, &camera, Color::YELLOW);
		entity_cleo->Render(&framebuffer, &camera, Color::PURPLE);
		entity_lee->Render(&framebuffer, &camera, Color::RED);
	}
	//3. Ortographic camera
	if (key == 3){
		//Config screen
		framebuffer.Fill(Color::BLUE);
		
		camera.SetOrthographic(-2, 2, -2, 2, 0.01f, 100);
		isPerspective = false;
		isOrthographic = true;
	}
	//4. Perspective camera
	if (key == 4){
		//Config screen
		framebuffer.Fill(Color::BLUE);
		
		camera.SetPerspective(45, static_cast<float>(framebuffer.width) / framebuffer.height, 0.01f, 100);
		isPerspective = true;
		isOrthographic = false;
	}

	//5. Camera near

	if (key == 5){
		//Config screen
		framebuffer.Fill(Color::BLUE);
		
		// Set current property to camera near
		changeNear = true;
		changeFar = false;
		changeFOV = false;

	}

	//6. Camera far
	if (key == 6){
		//Config screen
		framebuffer.Fill(Color::BLUE);

		// Set current property to camera far
		changeFar = true;
		changeNear = false;
		changeFOV = false;
	}

	//7. FOV
	if (key == 7){
		//Config screen
		framebuffer.Fill(Color::BLUE);

		// Set current property to camera fov
		changeFar = false;
		changeFOV = true;
		changeNear = false;
	}

	//7. Propery +
	if (key == 8){
		//Config screen
		framebuffer.Fill(Color::BLUE);

        // Increase current property
        if (changeNear) {
            camera.near_plane += 0.03f;
        } else if (changeFar) {
			camera.far_plane += 40.0f;
		} else if (changeFOV) {
			camera.fov += 10.0f;
		}
		camera.UpdateProjectionMatrix();



	}

	//8. Propery -
	if (key == 9){
		//Config screen
		framebuffer.Fill(Color::BLUE);

		// Decrease current property
		if (changeNear) {
			camera.near_plane -= 0.03f;
		} else if (changeFar) {
			camera.far_plane -= 40.0f;

		} else if (changeFOV) {
			camera.fov -= 10.0f;
		}

		camera.UpdateProjectionMatrix();


		
	}
	
	
	framebuffer.Render();
};

// Called after render
void Application::Update(float seconds_elapsed)
{
	if(key ==2){
	// Clean screen
	framebuffer.Fill(Color(0, 0, 0));

	// Update the entities
	entity_cleo->Update(seconds_elapsed);
	entity_anna->Update(seconds_elapsed);
	entity_lee->Update(seconds_elapsed);

	} else {
		//Reset position of meshes animation
		entity_anna->SetMatrix(0.0f, 0.0f, 0.0f);
		entity_cleo->SetMatrix(1.0f, 0.0f, 0.0f);
		entity_lee->SetMatrix(-1.0f, 0.0f, 0.0f);
	}

}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch(event.keysym.sym) {
		case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
		case SDLK_1: key = 1; break;
		case SDLK_2: key = 2; break;
		case SDLK_o: key = 3; break;
		case SDLK_p: key = 4; break;
		case SDLK_n: key = 5; break;
		case SDLK_f: key = 6; break;
		case SDLK_v: key = 7; break;
		case SDLK_PLUS: key = 8; break;
		case SDLK_MINUS: key = 9; break;
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


}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;

	if(dy > 0){
		// Zoom in
		camera.eye.z = camera.eye.z + 0.3f;
		camera.UpdateViewMatrix();
	} else {
		// Zoom out
		camera.eye.z = camera.eye.z - 0.3f;
		camera.UpdateViewMatrix();
	}

}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}