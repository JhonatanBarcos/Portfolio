
#include "application.h"
#include "mesh.h"
#include "camera.h"

class Entity {
private:
    Matrix44 modelMatrix;
    Mesh mesh;

public:
    // Constructor
    Entity();
    Entity(Matrix44& modelMatrix, const Mesh& mesh);
    Entity(const char* filename, Matrix44 modelMatrix);

    //Methods
    void Render(Image* framebuffer, Camera* camera, const Color& c);
    void SetMatrix(float x, float y, float z);
};
