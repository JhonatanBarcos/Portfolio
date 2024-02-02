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
void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
    int i;
    // Iterate through each vertex
    for (i = 0; i < mesh.GetVertices().size(); i += 3) {
        // Obtain the world space vertices
        Vector3 worldV1 = this->modelMatrix * mesh.GetVertices()[i];
        Vector3 worldV2 = this->modelMatrix * mesh.GetVertices()[i + 1];
        Vector3 worldV3 = this->modelMatrix * mesh.GetVertices()[i + 2];

        // Project vertex to clip space using ProjectVector
        Vector3 clipV1 = camera->ProjectVector(worldV1, negZ1);
        Vector3 clipV2 = camera->ProjectVector(worldV2, negZ2);
        Vector3 clipV3 = camera->ProjectVector(worldV3, negZ3);

         // If any of the vertices is behind the camera, do not draw the triangle
        if (negZ1 || negZ2 || negZ3) {
            continue;
        }
        int x1 = static_cast<int>((clipV1.x+1) * 0.5 * framebuffer->width);
        int y1 = static_cast<int>((clipV1.y+1) * 0.5 * framebuffer->height);
        int x2 = static_cast<int>((clipV2.x+1) * 0.5 * framebuffer->width);
        int y2 = static_cast<int>((clipV2.y+1) * 0.5 * framebuffer->height);
        int x3 = static_cast<int>((clipV3.x+1) * 0.5 * framebuffer->width);
        int y3 = static_cast<int>((clipV3.y+1) * 0.5 * framebuffer->height);

        // Draw the triangle on the framebuffer using the given color
        framebuffer->DrawLineDDA(x1, y1, x2, y2, c);
        framebuffer->DrawLineDDA(x2, y2, x3, y3, c);
        framebuffer->DrawLineDDA(x3, y3, x1, y1, c);
        }
        // else: Discard the triangle
}

void Entity::Update(float dt) {
    this->modelMatrix.Translate(0.01, 0.00, 0.0);
    this->modelMatrix.Rotate(1*DEG2RAD, Vector3(0, 1, 0));

 }

void Entity::SetMatrix(float x, float y, float z) {
    this->modelMatrix.SetTranslation(x, y, z);
}


