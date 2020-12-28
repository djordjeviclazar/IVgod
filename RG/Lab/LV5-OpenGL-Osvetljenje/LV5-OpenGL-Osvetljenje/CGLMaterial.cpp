#include "pch.h"
#include "CGLMaterial.h"
#include "GL/GL.H"

CGLMaterial::CGLMaterial()
{
	ambientv[0] = 0.2; 
	ambientv[1] = 0.2;
	ambientv[2] = 0.2;
	ambientv[3] = 1.;

	diffusev[0] = 0.8;
	diffusev[1] = 0.8;
	diffusev[2] = 0.8;
	diffusev[3] = 1.;

	specularv[0] = 0.;
	specularv[1] = 0.;
	specularv[2] = 0.;
	specularv[3] = 1.;

	emissionv[0] = 0.;
	emissionv[1] = 0.;
	emissionv[2] = 0.;
	emissionv[3] = 1.;

	shininessf = 64.;
}

CGLMaterial::~CGLMaterial()
{
}

void CGLMaterial::Select()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientv);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffusev);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularv);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininessf);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionv);
}

void CGLMaterial::SetAmbient(float r, float g, float b, float alpha)
{
	ambientv[0] = r;
	ambientv[1] = g;
	ambientv[2] = b;
	ambientv[3] = alpha;
}

void CGLMaterial::SetDiffuse(float r, float g, float b, float alpha)
{
	diffusev[0] = r;
	diffusev[1] = g;
	diffusev[2] = b;
	diffusev[3] = alpha;
}

void CGLMaterial::SetSpecular(float r, float g, float b, float alpha)
{
	specularv[0] = r;
	specularv[1] = g;
	specularv[2] = b;
	specularv[3] = alpha;
}

void CGLMaterial::SetEmission(float r, float g, float b, float alpha)
{
	emissionv[0] = r;
	emissionv[1] = g;
	emissionv[2] = b;
	emissionv[3] = alpha;
}

void CGLMaterial::SetShininess(float s)
{
	shininessf = s;
}
