
#include "application.h"
#include "mesh.h"
#include "camera.h"
#include "material.h"

class Entity {
private:
    Matrix44 modelMatrix;
    Mesh mesh;
    Texture* texture;
    Shader* shader;
    Material* material;

public:
    // Constructor
    Entity();
    Entity(Mesh mesh, Texture* texture, Shader* shader);

    //Methods
    void Render();
    void Render(sUniformData uniformData);
    void Entity::Update(float dt);
    void SetMatrix(float x, float y, float z);

    //Others
    bool negZ1 = true;
    bool negZ2 = true;
    bool negZ3 = true;


};

