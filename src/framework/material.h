#include <string.h>
#include <stdio.h>
#include <iostream>
#include "framework.h"
#include "shader.h"
#include "texture.h"
 #define MAX_LIGHTS 2

typedef struct sLight {
	Vector3 pos;
	Vector3 Id;
	Vector3 Is;
} Light;


struct sUniformData {
	Vector3 Ia;						//variable of application
	Matrix44 model_matrix;
	Matrix44 viewprojection_matrix;	//variable of camara
	Vector3 eye;
	Vector2 task;
	Light light[MAX_LIGHTS];
	int nlights;
};


class Material{

    private:
        Shader* shader;
        Texture* texture;
        Vector3 ka;
        Vector3 kd;
        Vector3 ks;
        float shininess;
    
    public:
        Material();
        Material(Shader* s, Texture* t, Vector3 ka, Vector3 kd, Vector3 ks, float shininess);
        void Enable(const sUniformData& uniformData);
        void Disable();
};
