#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "entity.h"

// Global variables
Mesh mesh;
Shader* shader;
Shader* shaderg;
Shader* shaderp;
Texture* texture_normal;
Texture* texture_color;
Material* material;
sUniformData data;
Entity* entity;
Vector3 option = Vector3(0);


Application::Application(const char* caption, int width, int height)
{
    this->window = createWindow(caption, width, height);

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

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

    // Init camera
    Vector3 eye(0.0f, 0.0f, 5.0f);
    Vector3 center(0.0f, 0.0f, 0.0f);
    Vector3 up(0.0f, 1.0f, 0.0f);

    camera.LookAt(eye, center, up);
    camera.SetPerspective(45, static_cast<float>(framebuffer.width) / framebuffer.height, 0.01f, 100);

    // Init mesh
    mesh.LoadOBJ("meshes/lee.obj");

    // Init textures
    texture_color = new Texture();
    texture_color->Load("textures/lee_color_specular.tga");

    texture_normal = new Texture();
    texture_normal->Load("textures/lee_normal.tga");


	//Init shader by default without ilumination
	shader = Shader::Get("/shaders/raster.vs", "/shaders/raster.fs");
	shaderp = Shader::Get("/shaders/phong.vs", "/shaders/phong.fs");
	shaderg = Shader::Get("shaders/gouraud.vs", "shaders/gouraud.fs");

	//Init entity
	entity = new Entity(mesh, texture_color, shader);
    material = new Material(shader, texture_color, texture_normal, Vector3(0.1, 0.1, 0.1), Vector3(1.0, 1.0, 1.0), Vector3(0.5, 0.5, 0.5), 0.5);
    entity->material = material;

	// Init light 1
	data.lights[0].pos = Vector3(1.0f, 0.0f, 3.0f); // Posición en (1, 0, 3)
	data.lights[0].Id = Vector3(1.0f, 1.0f, 1.0f); // Color blanc
	data.lights[0].Is = Vector3(1.0f, 1.0f, 1.0f); // Intensidad

	// Init light 2
	data.lights[1].pos = Vector3(-2.0f, 2.0f, 1.0f); // Posición en (-2, 2, 1)
	data.lights[1].Id = Vector3(0.0f, 1.0f, 0.0f); // Color verde
	data.lights[1].Is = Vector3(1.0f, 1.0f, 1.0f); // Intensidad

	// Init light 3
	data.lights[2].pos = Vector3(6.0f, 3.0f, 1.0f); // Posición en (6, 3, 1)
	data.lights[2].Id = Vector3(1.0f, 0.0f, 0.0f); // Color rojo
	data.lights[2].Is = Vector3(1.0f, 1.0f, 1.0f); // Intensidad


	// Set number of lights = 1
	data.numLights = 1;

    // Init uniform data
    data.Ia = Vector3(0.2f, 0.2f, 0.2f);
    data.viewprojection_matrix = camera.viewprojection_matrix;
    data.eye = eye;
}

void Application::Render(void)
{
    // Enable shader
    shader->Enable();
    shader->SetVector3("u_option", option);

    // Update camera
    data.viewprojection_matrix = camera.viewprojection_matrix;
    data.eye = camera.eye;
    shader->SetMatrix44("u_viewprojection", camera.viewprojection_matrix);

    // Render entitys
    entity->Render(data);

    // Disable shader
    shader->Disable();
}

    

void Application::Update(float seconds_elapsed)
{
}

void Application::OnKeyPressed(SDL_KeyboardEvent event)
{
    switch (event.keysym.sym) {
    case SDLK_ESCAPE: exit(0); break;

     case SDLK_g: 
        if (shader != shaderg) {
            shader = shaderg;
            entity->material->SetShader(shader);
			entity->SetShader(shader);
            std::cout << "Switched to Gouraud shading" << std::endl;
        }
        break;

    case SDLK_p: 
        if (shader != shaderp) {
            shader = shaderp;
            entity->material->SetShader(shader);
			entity->SetShader(shader);
            std::cout << "Switched to Phong shading" << std::endl;
        }
        break;

    case SDLK_c: 
        if (shader == shaderp) {
            if (option.x != 1.0) {
                option.x = 1.0;
                std::cout << "Using color texture" << std::endl;
            } else {
                option.x = 0.0;
                std::cout << "Not using color texture" << std::endl;
            }
        } 
        break;

    case SDLK_s: 
        if (shader == shaderp) {
            if (option.y != 1.0) {
                option.y = 1.0;
                std::cout << "Using specular texture" << std::endl;
            } else {
                option.y = 0.0;
                std::cout << "Not using specular texture" << std::endl;
            }
        } 
        break;

    case SDLK_n: 
        if (shader == shaderp) {
            if (option.z != 1.0) {
				option.z = 1.0;
                std::cout << "Using normal texture" << std::endl;
            } else {
				option.z = 0.0;
                std::cout << "Not using normal texture" << std::endl;
            }
        }  
        break;

    case SDLK_1: 
        data.numLights = 1;
        break;

    case SDLK_2: 
        data.numLights = 2;
        break;

	case SDLK_3:
		data.numLights = 3;
		break;
	}
}


void Application::OnMouseButtonDown(SDL_MouseButtonEvent event)
{
    if (event.button == SDL_BUTTON_LEFT) {
        leftClick = true;
        mouse_position.x = static_cast<float>(event.x);
        mouse_position.y = static_cast<float>(event.y);
    }

    if (event.button == SDL_BUTTON_RIGHT) {
        rightClick = true;

        // Clean screen
        framebuffer.Fill(Color::BLACK);

        mouse_position.x = static_cast<float>(event.x);
        mouse_position.y = static_cast<float>(event.y);

        float normalizedX = (2.0f * mouse_position.x) / window_width - 1.0f;
        float normalizedY = 1.0f - (2.0f * mouse_position.y) / window_height;

        Vector3 center(normalizedX, normalizedY, camera.GetCenter().z);

        camera.LookAt(camera.GetEye(), center, camera.GetUp());
        camera.UpdateViewMatrix();
    }
}

void Application::OnMouseButtonUp(SDL_MouseButtonEvent event)
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
        // Clean screen
        framebuffer.Fill(Color::BLACK);

        // Orbit
        camera.Orbit(-mouse_delta.x * 0.01, Vector3::UP);
        camera.Orbit(-mouse_delta.y * 0.01, Vector3::RIGHT);
    }
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
    float dy = event.preciseY;

    // Clean screen
    framebuffer.Fill(Color::BLACK);

    // Zoom
    camera.Zoom(dy < 0 ? 1.1 : 0.9);
}

void Application::OnFileChanged(const char* filename)
{
    Shader::ReloadSingleShader(filename);
}
