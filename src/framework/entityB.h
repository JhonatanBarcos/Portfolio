#pragma once
#include "camera.h"
#include "mesh.h"
#include "image.h"


class Entity
{
private:
    Mesh mesh;
    Matrix44 modelMatrix;

public:
    // Constructors, dependiendo de los parametros, crear mas constructores
    Entity();
    Entity::Entity(const char* filename, Matrix44 modelMatrix); //{ this->mesh = mesh; this->modelMatrix = modelMatrix; }
    void Render(Image* framebuffer, Camera* camera, const Color& c);
    void Update(float seconds_elapsed, int axis, bool translation);
    void SetMatrix(float x, float y, float z);
    
};

