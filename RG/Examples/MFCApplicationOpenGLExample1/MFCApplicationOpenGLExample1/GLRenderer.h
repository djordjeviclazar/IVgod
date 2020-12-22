#pragma once

#define PI 3.14159
#define SPHERE_X(r, alpha, beta) r * cos(alpha) * cos(beta)
#define SPHERE_Y(r, alpha) r * sin(alpha)
#define SPHERE_Z(r, alpha, beta) r * cos(alpha) * sin(beta)
#define CIRCLE_X(r, alpha) r * cos(alpha)
#define CIRCLE_Z(r, alpha) r * sin(alpha)

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

private:
	void drawSphere(float radius);
	void drawCylinder(float radius, float height);
	void drawPrism(float radius, float height, int sides);
};
