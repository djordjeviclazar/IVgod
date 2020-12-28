/*
* Refferences: 
*  https://learnopengl.com/Getting-started/Camera
*/

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
	

	void moveEye(CPoint point);

private:
	CPoint startPoint;
	float cameraSensitivity = 0.5;
	bool firstRotation;
	float currentLength;
	// angles:
	float yaw;
	float pitch;
	// eye:
	float eyeX, eyeY, eyeZ;

	float unit = 5.;

	// materials:
	CGLMaterial material;
};
