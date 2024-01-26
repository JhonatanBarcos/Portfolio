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
Image Fruits;
int key = -1;
void Application::Render(void)
{

	//1. Draw line
	if (key == 1){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));

		framebuffer.DrawLineDDA(1, 1, 300, 200, Color::GREEN);
	}
	
	//2. Draw Rectangle
	if (key == 2){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));

		framebuffer.DrawRect(300, 100, 300, 200, Color::BLUE, 2, true, Color::RED);
	}
	//3. Draw Circle
	if (key == 3){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));

		framebuffer.DrawCircle(400, 300, 200, Color::RED, 2, true, Color::BLUE);
	}
	//4. Draw Triangle
		if (key == 4){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));

		// Define the triangle vertices
		Vector2 p0(0, 200);
		Vector2 p1(300, 400);
		Vector2 p2(500, 100);

		// Define the border and fill colors
		Color borderColor(255, 0, 0); // Red border
		Color fillColor(0, 255, 0); // Green fill

		// Draw the triangle
		framebuffer.DrawTriangle(p0, p1, p2, borderColor, true, fillColor);
		}

	//x. draw image
	if (key == 5){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));

		// Load the image
		//bool success = Toolbar.LoadPNG("images/fruits.png", false);
		//framebuffer.DrawImage(Fruits, 0, 0, success);
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