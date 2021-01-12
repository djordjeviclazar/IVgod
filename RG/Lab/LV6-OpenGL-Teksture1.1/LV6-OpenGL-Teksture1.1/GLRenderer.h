/*
* Refferences: 
*  https://learnopengl.com/Getting-started/Camera
*/

#include "DImage.h"
#include "CGLMaterial.h"

#pragma once

#define PI 3.14159
class CGLRenderer
{
public:
	CGLRenderer(void);
	virtual ~CGLRenderer(void);
		
	bool CreateGLContext(CDC* pDC);			// kreira OpenGL Rendering Context
	void PrepareScene(CDC* pDC);			// inicijalizuje scenu,
	void Reshape(CDC* pDC, int w, int h);	// kod koji treba da se izvrsi svaki put kada se promeni velicina prozora ili pogleda i
	void DrawScene(CDC* pDC);				// iscrtava scenu
	void DestroyScene(CDC* pDC);			// dealocira resurse alocirane u drugim funkcijama ove klase,

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 

public:
	bool firstRotation = true;

	void moveEye(CPoint point);

private:
	CPoint startPoint;
	float cameraSensitivity = 0.5;
	
	float currentLength;
	// angles:
	float yaw;
	float pitch;
	// eye:
	float eyeX, eyeY, eyeZ;

	float unit = 2.5;
	float textureUnit = 1. / 16.;


	void drawTruck(int height, int width, int depth, int unit);
	void drawBody(int height, int width, int depth, int localUnit);
	void drawElipsoid(int radiusX, int radiusY, int radiusZ);
	void drawWheel(float radius, float height, float textureCenterX, float textureCenterY, float textureRadius);
	void drawGround(int localUnit);

	UINT LoadTexture(char* fileName);
	UINT LoadTextureRepeat(char* fileName);
};
