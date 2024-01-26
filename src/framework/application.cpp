#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "button.h"


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

//Declare images
Image black;
Image blue;
Image circle;
Image clear;
Image cyan;
Image eraser;
Image fruits;
Image green;
Image line;
Image load;
Image pink;
Image rectangle;
Image red;
Image save;
Image toolbar;

Button lineButton;
Button rectangleButton;
Button circleButton;
Button saveButton;
Button loadButton;
Button clearButton;
Button eraserButton;
Button redButton;
Button greenButton;
Button blueButton;

void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;

	// Load PNGs
	black.LoadPNG("images/black.png", true);
	blue.LoadPNG("images/blue.png", false);
	circle.LoadPNG("images/circle.png", false);
	clear.LoadPNG("images/clear.png", false);
	cyan.LoadPNG("images/cyan.png", false);
	eraser.LoadPNG("images/eraser.png", false);
	fruits.LoadPNG("images/fruits.png", false);
	green.LoadPNG("images/green.png", false);
	line.LoadPNG("images/line.png", false);
	load.LoadPNG("images/load.png", false);
	pink.LoadPNG("images/pink.png", false);
	rectangle.LoadPNG("images/rectangle.png", false);
	red.LoadPNG("images/red.png", false);
	save.LoadPNG("images/save.png", false);
	toolbar.LoadPNG("images/toolbar.png", false);

	// Load buttons
	lineButton = Button(line, Vector2(35, 650));
	rectangleButton = Button(rectangle, Vector2(70, 650));
	circleButton = Button(circle, Vector2(105, 650));
	saveButton = Button(save, Vector2(140, 650));
	loadButton = Button(load, Vector2(175, 650));
	clearButton = Button(clear, Vector2(210, 650));
	eraserButton = Button(eraser, Vector2(245, 650));
	redButton = Button(red, Vector2(280, 650));
	greenButton = Button(green, Vector2(315, 650));
	blueButton = Button(blue, Vector2(350, 650));

}

// Render one frame
//key pressed
int key = -1;
void Application::Render(void)
{
	//KEY INSTRUCTIONS
	//1. Draw line
	if (key == 1){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));

		framebuffer.DrawLineDDA(200, 300, 700, 200, Color::GREEN);
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

	//5. Paint
	if (key == 5){
		// Clean screen
		framebuffer.Fill(Color(0, 0, 0));

		// Draw buttons
		lineButton.drawButton(framebuffer);
		rectangleButton.drawButton(framebuffer);
		circleButton.drawButton(framebuffer);
		saveButton.drawButton(framebuffer);
		loadButton.drawButton(framebuffer);
		clearButton.drawButton(framebuffer);
		eraserButton.drawButton(framebuffer);
		redButton.drawButton(framebuffer);
		greenButton.drawButton(framebuffer);
		blueButton.drawButton(framebuffer);
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