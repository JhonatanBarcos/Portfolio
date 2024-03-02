#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "entity.h"

// Global variables
Mesh quad = Mesh();
Mesh mesh = Mesh();
Shader* shader = new Shader();
Shader* shader_entity = new Shader();
Texture* texture = new Texture();
Texture* texture_normal = new Texture();
Texture* texture_color = new Texture();
Material* material = new Material();
sUniformData data;
Entity* entity; 
bool ex1 = false;
bool ex2 = false;
bool ex3 = false;
bool ex4 = false;
bool subExA = false;
bool subExB = false;
bool subExC = false;
bool subExD = false;
bool subExE = false;
bool subExF = false;
float option;


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

	//Init shaders
	shader = Shader::Get("shaders/quad.vs", "shaders/quad.fs");
	shader_entity = Shader::Get("shaders/gourand.vs", "shaders/gourand.fs");

	//Init quad mesh
	quad.CreateQuad();

	//Init mesh
	mesh.LoadOBJ("meshes/lee.obj");
	texture_normal->Load("textures/lee_color_specular.tga");
	texture_color->Load("textures/lee_normal.tga");

	//Init entity
	entity = new Entity(mesh, texture_color, shader_entity);
	material = new Material(shader, texture_color, texture_normal, Vector3(0.2, 0.2, 0.2), Vector3(0.8, 0.8, 0.8), Vector3(0.0, 0.0, 0.0), 1.0);
	entity->material = material;

	// Init light
    data.light.pos = Vector3(0.0f, 0.0f, 0.0f); 
    data.light.Id = Vector3(1.0f, 1.0f, 1.0f); 
    data.light.Is = Vector3(1.0f, 1.0f, 1.0f); 

    // Initit uniform data
    data.Ia = Vector3(0.2f, 0.2f, 0.2f); 
    data.model_matrix = entity->modelMatrix; 
    data.viewprojection_matrix = camera.viewprojection_matrix; 
    data.eye = eye; 
}

// Render one frame
//key pressed
void Application::Render(void)
{


	shader_entity->Enable();
	shader_entity->SetFloat("u_option", option);
	shader_entity->SetMatrix44("u_viewprojection", camera.viewprojection_matrix);
	entity->Render(data);
	shader_entity->Disable();

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
		case SDLK_1: ex1 = true; ex2 = false; ex3 = false; ex4 = false; subExA= false; subExB = false; subExC = false; subExD = false; subExE = false; subExF = false; break;
		case SDLK_2: ex1 = false; ex2 = true; ex3 = false; ex4 = false; subExA= false; subExB = false; subExC = false; subExD = false; subExE = false; subExF = false; break;
		case SDLK_3: ex1 = false; ex2 = false; ex3 = true; ex4 = false; subExA= false; subExB = false; subExC = false; subExD = false; subExE = false; subExF = false; break;
		case SDLK_4: ex1 = false; ex2 = false; ex3 = false; ex4 = true; subExA= false; subExB = false; subExC = false; subExD = false; subExE = false; subExF = false; break;
		case SDLK_a: subExA = true; subExB = false; subExC = false; subExD = false; subExE = false; subExF = false; break;
		case SDLK_b: subExA = false; subExB = true; subExC = false; subExD = false; subExE = false; subExF = false; break;
		case SDLK_c: subExA = false; subExB = false; subExC = true; subExD = false; subExE = false; subExF = false; break;
		case SDLK_d: subExA = false; subExB = false; subExC = false; subExD = true; subExE = false; subExF = false; break;
		case SDLK_e: subExA = false; subExB = false; subExC = false; subExD = false; subExE = true; subExF = false; break;
		case SDLK_f: subExA = false; subExB = false; subExC = false; subExD = false; subExE = false; subExF = true; break;
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