#include "entity.h"
#include "application.h"
#include "image.h"

// Default constructor
Entity::Entity() {}

// Constructor LAB 4 
Entity::Entity(Mesh mesh, Texture* texture, Shader* shader){
    this->mesh = mesh;
    this->modelMatrix = Matrix44();
    this->texture = texture;
    this->shader = shader;
}

// Methods
void Entity::Render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Habilitamos el shader
    shader->Enable();

    // Establecemos la matriz de modelo en el shader
    shader->SetMatrix44("u_model", this->modelMatrix);

    // Enlazamos la textura al shader
    shader->SetTexture("u_texture", texture);

    // Renderizamos la malla del objeto
    mesh.Render();

    // Desenlazamos la textura y deshabilitamos el shader
    shader->Disable();

    glDisable(GL_DEPTH_TEST);
}



void Entity::Update(float dt) {
    this->modelMatrix.Translate(0.01, 0.00, 0.0);
    this->modelMatrix.Rotate(1*DEG2RAD, Vector3(0, 1, 0));

 }

void Entity::SetMatrix(float x, float y, float z) {
    this->modelMatrix.SetTranslation(x, y, z);
}


