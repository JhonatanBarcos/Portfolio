
#include "material.h"

Material::Material() {
    
}

Material::Material(Shader* s,Texture* c, Texture* n, Vector3 ka, Vector3 kd, Vector3 ks, float alpha) {
    this->shader = s;
	this->color = c;
    this->normal = n;
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    this->shininess = alpha;
}

void Material::Enable(const sUniformData& uniformData, int lightIndex) {
	//init
	shader->Enable();
	shader->SetMatrix44("u_model", uniformData.model_matrix);

	//material
	shader->SetVector3("u_ka", ka);
	shader->SetVector3("u_kd", kd);
	shader->SetVector3("u_ks", ks);
	shader->SetFloat("u_shininess", shininess);

	//textures
    shader->SetTexture("u_texture", color);
	shader->SetTexture("u_normal", normal);

	//light
    if (lightIndex < uniformData.numLights) {
        Light light = uniformData.lights[lightIndex];
        shader->SetVector3("u_lightPos", light.pos);
        shader->SetVector3("u_Id", light.Id);
        shader->SetVector3("u_Is", light.Is);
		if (lightIndex == 0) {
			shader->SetVector3("u_Ia", uniformData.Ia);
		}
    }

	//camera
	shader->SetMatrix44("u_viewprojection", uniformData.viewprojection_matrix);
	shader->SetVector3("u_eye", uniformData.eye);
}

void Material::Disable() {
    this->shader->Disable();
}

void Material::SetShader(Shader* s) {
	this->shader = s;
}