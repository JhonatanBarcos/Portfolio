#include "entity.h"
#include "image.h"


Entity::Entity() {}

Entity::Entity(const char* filename, Matrix44 modelMatrix) { //La entity llegir� un fitxer del qual crear� la seva propia mesh i inicialitzar� una matri de 4x4
    this->mesh.LoadOBJ(filename);
    this->modelMatrix = Matrix44();
}

bool negZ1 = true;
bool negZ2 = true;
bool negZ3 = true;

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
  
    Vector3 w_toc_aux_x;
    Vector3 w_toc_aux_y;
    Vector3 w_toc_aux_z;

    for (int i = 0; i < mesh.GetVertices().size(); i += 3)
    {
        // World coordinates
        w_toc_aux_x = this->modelMatrix * mesh.GetVertices()[i];
        w_toc_aux_y = this->modelMatrix * mesh.GetVertices()[i + 1];
        w_toc_aux_z = this->modelMatrix * mesh.GetVertices()[i + 2];


        // World to Clip
        Vector3 w_toc_x = camera->ProjectVector(w_toc_aux_x, negZ1);
        Vector3 w_toc_y = camera->ProjectVector(w_toc_aux_y, negZ2);
        Vector3 w_toc_z = camera->ProjectVector(w_toc_aux_z, negZ3);
        //camera->ProjectVector(v, negZ);
        if (negZ1 || negZ2 || negZ3) {
            continue;
        }
        int x1 = (w_toc_x.x + 1) * framebuffer->width / 2;
        int y1 = (w_toc_x.y + 1) * framebuffer->height / 2;
        int x2 = (w_toc_y.x + 1) * framebuffer->width / 2;
        int y2 = (w_toc_y.y + 1) * framebuffer->height / 2;
        int x3 = (w_toc_z.x + 1) * framebuffer->width / 2;
        int y3 = (w_toc_z.y + 1) * framebuffer->height / 2;

        // Draw the vertex on the framebuffer using the given color
        framebuffer->DrawLineDDA(x1, y1, x2, y2, c);
        framebuffer->DrawLineDDA(x2, y2, x3, y3, c);
        framebuffer->DrawLineDDA(x3, y3, x1, y1, c);
    }
}
void Entity::SetMatrix(float x, float y, float z) {
    this->modelMatrix.SetTranslation(x, y, z);
}

void Entity::Update(float seconds_elapsed, int axis, bool translation) {
   if (axis == 0) { // girar� al voltant de l'eix vertical
        modelMatrix.Rotate(PI/100, Vector3(0, 1, 0));
        if (translation == true) {
            modelMatrix.Translate(0.01, 0, 0);
        }
    }
   else if (axis == 1) {
       modelMatrix.Rotate(PI / 100, Vector3(0, 0, 1));
       if (translation == true) {
           modelMatrix.Translate(0, 0, 0.01);
       }
   }
    else if (axis == 2) {
        modelMatrix.Rotate(PI / 50, Vector3(1, 1, 0));
        if (translation == true) {
            modelMatrix.Translate(0.01, 0, 0);
        }

    }
}
