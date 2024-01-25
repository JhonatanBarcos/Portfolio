#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 

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
}

// Render one frame
Image Toolbar;
int tecla = -1;
void Application::Render(void)
{
/*
	//1. Draw line
	if (tecla == 1){
		framebuffer.Fill(Color(0, 0, 0));
		framebuffer.DrawLineDDA(1, 1, 300, 200, Color::GREEN);
	}
	

	//2. draw Rectangle
	if (tecla == 2){
		framebuffer.Fill(Color(0, 0, 0));
		//framebuffer.DrawRect(1, 1, 300, 200, Color::BLUE, false);
	}
	//3. draw Circle
	if (tecla == 3){
		framebuffer.Fill(Color(0, 0, 0));
		//framebuffer.DrawCircle(1, 1, 300, Color::RED);
	}
	//4. draw Triangle

	//x. draw image
	//if (tecla == 5){
	//	bool success = Toolbar.LoadPNG("images/toolbar.png", false);
	//	framebuffer.DrawImage(Toolbar, 0, 0, success);
	//}
*/
/*
	bool success = framebuffer.LoadPNG("images/toolbar.png", false);
	framebuffer.DrawImage(Toolbar,0 ,0 , success);
*/
	//draw triangle
	// Create an instance of the Image class

	// Define the vertices of the triangle
	if (tecla == 4){
		Vector2 p0(0, 200);
		Vector2 p1(300, 400);
		Vector2 p2(500, 100);

		// Define the border and fill colors
		Color borderColor(255, 0, 0); // Red border
		Color fillColor(0, 255, 0); // Green fill

		// Draw the triangle
		framebuffer.DrawTriangle(p0, p1, p2, borderColor, true, fillColor);
	}
	framebuffer.Render();
}

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
		case SDLK_1: tecla = 1; break;
		case SDLK_2: tecla = 2; break;
		case SDLK_3: tecla = 3; break;
		case SDLK_4: tecla = 4; break;
		case SDLK_5: tecla = 5; break;
		case SDLK_6: tecla = 6; break;
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