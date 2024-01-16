#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <random>

#include "framework.h"

//remove unsafe warnings
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif

/*
3.1 Create a new Entity class (1 point)
At some point in this lab, we will render a mesh. In case we want to translate, rotate or apply any other transformation, we would need a model matrix. The idea of this task is to create an encapsulation of both things so we can simplify and organize our code.

Here comes the Entity concept. An entity will represent a mesh in the space using a model matrix. By now we only need those two attributes:

    - Create an entity class which contains a mesh and a model matrix (in separate entity.h, entity.cpp files and be sure that you put them in the src/framework folder).
    - Instantiate a new entity and assign a model matrix.
    - Assign a mesh to your entity.
    - Ideally, your Entity class should have different constructors depending on what parameters you ask.
 */

class Entity {
    // OpenGL methods to fill matrices
    // Only to test Draw3DEntity
    void SetExampleViewMatrix();
    void SetExampleProjectionMatrix();
public:
    Mesh *mesh;
    Matrix44 modelMatrix;       // changes mesh from local space to world space
    
    // Constructors
    Entity();
    Entity(Mesh *mesh);
    Entity(Mesh *mesh, Matrix44 viewMatrix);

    // Destructor
    ~Entity();
    
    // Model Matrix
    Matrix44 defineTraslationMatrix(double tx, double ty, double tz);
    Matrix44 defineRotationMatrix(double alpha, double beta, double gamma);
    Matrix44 defineScaleMatrix(double sx, double sy, double sz);
    void defineModelMatrix();
    
    // Rasterize entity meshes
    void rasterizeEntityMeshes(const Color& c);

    //
    void Render(Image* framebuffer, Camera* camera, const Color& c);
};

