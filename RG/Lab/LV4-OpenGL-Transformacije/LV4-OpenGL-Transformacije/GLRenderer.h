#pragma once

#define PI 3.14159
class CGLRenderer
{
public:
	float xAxisRotate = 0;
	float yAxisRotate = 0;
	float angle = 10.;
	float angleGlobal = 2.;
	float unit = 1.;

	float xAxisRotateGlobal = 0;
	float yAxisRotateGlobal = 0;

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

private:
	void drawSphere(float radius);
	void drawCone(float radius, float height);
	void drawCylinder(float radius, float height);
	void drawPrism(float radius, float height, int numberOfSides);
	void drawPyramid(float radius, float height, int numberOfSides);
	void drawOctagonalPrism(float radius, float height);
	void drawVaseBottom(float bottomRadius, float upRadius, float height);
	void drawGrid();

	void drawCactus();
	void drawVase();
};
