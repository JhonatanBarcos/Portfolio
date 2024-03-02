
#include "material.h"

Material::Material() {
    
}

Material::Material(Shader* s, Texture* t, Vector3 ka, Vector3 kd, Vector3 ks, float shininess) {
    this->shader = s;
    this->texture = t;
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    this->shininess = shininess;
}

void Material::Enable(const sUniformData& uniformData) {
	shader->Enable();

	shader->SetMatrix44("u_model", uniformData.model_matrix);
	shader->SetMatrix44("u_viewprojection", uniformData.viewprojection_matrix);

	shader->SetVector3("u_ka", ka);
	shader->SetVector3("u_kd", kd);
	shader->SetVector3("u_ks", ks);

	shader->SetFloat("u_shininess", shininess);

	shader->SetVector3("u_lightPos", uniformData.light->pos);
	shader->SetVector3("u_Id", uniformData.light->Id);
	shader->SetVector3("u_Is", uniformData.light->Is);						
	shader->SetVector3("u_Ia", uniformData.Ia);
	
	shader->SetVector3("u_eye", uniformData.eye);
	shader->SetVector2("u_task", uniformData.task);

    shader->SetTexture("u_texture", texture);
}

void Material::Disable() {
    this->shader->Disable();
}