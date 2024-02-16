#include "entity.h"

// Default constructor
Entity::Entity() {

}

// Constructor with parameters
Entity::Entity(Matrix44& modelMatrix, const Mesh& mesh) {
    this->modelMatrix = modelMatrix;
    this->mesh = mesh;
}

Entity::Entity(const char* filename, Matrix44 modelMatrix) {
    this->modelMatrix = Matrix44();
    this->mesh.LoadOBJ(filename);
}

// Methods
void Entity::Render(){
    
}



void Entity::Update(float dt) {
    this->modelMatrix.Translate(0.01, 0.00, 0.0);
    this->modelMatrix.Rotate(1*DEG2RAD, Vector3(0, 1, 0));

 }

void Entity::SetMatrix(float x, float y, float z) {
    this->modelMatrix.SetTranslation(x, y, z);
}


