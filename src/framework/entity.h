
#include "application.h"
#include "mesh.h"
#include "camera.h"
#include "material.h"

class Entity {
    public:
    Matrix44 modelMatrix;
    Mesh mesh;
    Texture* texture;
    Shader* shader;
    Material* material;

    // Constructor
    Entity();
    Entity(Mesh mesh, Texture* texture, Shader* shader);

    //Methods
    void Render();
    void Render(sUniformData uniformData, int ligthIndex);
    void Render(sUniformData uniformData);
    void Update(float dt);
    void SetMatrix(float x, float y, float z);
    void SetShader(Shader* s);

    //Others
    bool negZ1 = true;
    bool negZ2 = true;
    bool negZ3 = true;


};

