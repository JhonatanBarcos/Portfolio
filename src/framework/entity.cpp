#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "GL/glew.h"
#include "../extra/picopng.h"
#include "image.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include "entity.h"

Entity::Entity() {

}

Entity::Entity(Mesh *mesh) {
    this->mesh = mesh;
}

void Entity::defineModelMatrix() {
    modelMatrix = SetExampleViewMatrix();
    
    //Matrix44 traslationMatrix = defineTraslationMatrix(<#double tx#>, <#double ty#>, <#double tz#>);
    //Matrix44 rotationMatrix = defineRotationMatrix(<#double alpha#>, <#double beta#>, <#double gamma#>);
    //Matrix44 scaleMatrix = defineScaleMatrix(<#double sx#>, <#double sy#>, <#double sz#>);
    
}

Matrix44 Entity::defineTraslationMatrix(double tx, double ty, double tz) {
    Matrix44 m;
    
    m.M[0][0] = 1.0;
    m.M[0][1] = 0.0;
    m.M[0][2] = 0.0;
    m.M[0][3] = tx;
    
    m.M[1][0] = 0.0;
    m.M[1][1] = 1.0;
    m.M[1][2] = 0.0;
    m.M[1][3] = ty;
    
    m.M[2][0] = 0.0;
    m.M[2][1] = 0.0;
    m.M[2][2] = 1.0;
    m.M[2][3] = tz;
    
    m.M[3][0] = 0.0;
    m.M[3][1] = 0.0;
    m.M[3][2] = 0.0;
    m.M[3][3] = 1.0;
    
    return m;
}

Matrix44 Entity::defineRotationMatrix(double alpha, double beta, double gamma) {
    Matrix44 m;
    
    m.M[0][0] = cos(alpha) * cos(beta);
    m.M[0][1] = cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma);
    m.M[0][2] = cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma);
    m.M[0][3] = 0.0;
    
    m.M[1][0] = sin(alpha) * cos(beta);
    m.M[1][1] = sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma);
    m.M[1][2] = sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma);
    m.M[0][3] = 0.0;
    
    m.M[0][0] = - sin(beta);
    m.M[0][1] = cos(beta) * sin(gamma);
    m.M[0][2] = cos(beta) * cos(gamma);
    m.M[0][3] = 0.0;
    
    m.M[0][0] = 0.0;
    m.M[0][1] = 0.0;
    m.M[0][2] = 0.0;
    m.M[0][3] = 1.0;
    
    return m;
}

Matrix44 Entity::defineScaleMatrix(double sx, double sy, double sz) {
    Matrix44 m;
    
    m.M[0][0] = sx;
    m.M[0][1] = 0.0;
    m.M[0][2] = 0.0;
    m.M[0][3] = 0.0;
    
    m.M[1][0] = 0.0;
    m.M[1][1] = sy;
    m.M[1][2] = 0.0;
    m.M[1][3] = 0.0;
    
    m.M[2][0] = 0.0;
    m.M[2][1] = 0.0;
    m.M[2][2] = sz;
    m.M[2][3] = 0.0;
    
    m.M[3][0] = 0.0;
    m.M[3][1] = 0.0;
    m.M[3][2] = 0.0;
    m.M[3][3] = 1.0;
    
    return m;
}

void Entity::rasterizeEntityMeshes(const Color& c) {
    /*
     The steps are the following:
        1. Get the vertices of the mesh and iterate them
        2. In each iteration:
            - Transform the local space of the vertices to world space using the model matrix of the entity
            - Project each of the world space vertices to clip space positions using your current camera
            - Before drawing each of the triangle lines, convert the clip space positions to screen space using the framebuffer width and height.

     While iterating through all the mesh vertices and projecting to clip space,  be sure to use the bool parameter of the Camera::ProjectVector(Vector3 pos, bool& negZ) to prevent the triangles from being rendered. If negZ is true in one of the triangle projected vertices, it is outside the camera frustum and the whole triangle must be discarded.*/
    
    std::vector<Vector3> vertices = this->mesh->GetVertices();
    
    
    
}


void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
    
}

