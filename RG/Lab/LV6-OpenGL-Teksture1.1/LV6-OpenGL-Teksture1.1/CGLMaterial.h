#pragma once
class CGLMaterial
{
public:

	CGLMaterial();
	~CGLMaterial();

	void Select();
	void SetAmbient(float r, float g, float b, float alpha);
	void SetDiffuse(float r, float g, float b, float alpha);
	void SetSpecular(float r, float g, float b, float alpha);
	void SetEmission(float r, float g, float b, float alpha);
	void SetShininess(float s);
private:
	float ambientv[4];
	float diffusev[4];
	float specularv[4];
	float emissionv[4];
	float shininessf;
};

