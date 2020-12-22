#include "pch.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
//#pragma comment(lib, "GL\\glut32.lib")
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif // !_USE_MATH_DEFINES
#include <math.h>

#define SPHERE_X(r, alpha, beta) r * cos(alpha) * cos(beta)
#define SPHERE_Y(r, alpha) r * sin(alpha)
#define SPHERE_Z(r, alpha, beta) r * cos(alpha) * sin(beta)
#define CIRCLE_X(r, alpha) r * cos(alpha)
#define CIRCLE_Z(r, alpha) r * sin(alpha)

CGLRenderer::CGLRenderer()
{
	
}

CGLRenderer::~CGLRenderer(void)
{
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (!bResult) return false;

	m_hrc = wglCreateContext(pDC->m_hDC);

	if (!m_hrc) return false;

	return true;
}

void CGLRenderer::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClearColor(0.3, 0.7, 0.9, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	gluLookAt(20.0, 20.0, 0.,
		0.0, 2.0, 0.0,
		0.0, 1.0, 0.0);

	//glTranslatef(5., 0, 0);
	
	/*glColor3f(1.0, 1.0, 1.0);
	drawSphere(1.);
	glColor3f(1.0, 0.0, 0.0);
	drawCone(1., 2.);*/

	glRotatef(xAxisRotateGlobal, 1., 0., 0.);
	glRotatef(yAxisRotateGlobal, 0., 1., 0.);

	glLineWidth(0.5);
	glPointSize(0.1);

	glBegin(GL_LINES);
	{
		glColor3f(1.0, 0.0, 0.0); //x
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(10.0, 0.0, 0.0);

		glColor3f(0.0, 1.0, 0.0); //y
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 10.0, 0.0);

		glColor3f(0.0, 0.0, 1.0); //z
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 10.0);
	}
	glEnd();

	glColor3f(1., 1., 1.);

	glPushMatrix();
	{
		drawGrid();
		glColor3f(141. / 255., 81. / 255., 26. / 255.);
		drawVase();

		glTranslatef(0., 3. * unit, 0.);
		glRotatef(xAxisRotate, 1., 0., 0.);
		glRotatef(yAxisRotate, 0., 1., 0.);

		
		// whole cactus is rotated:
		drawCactus();
	}
	glPopMatrix();


	glFlush();
	//---------------------------------
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	double aspect = (double)w / (double)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 
	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void CGLRenderer::drawSphere(float radius)
{
	glBegin(GL_QUAD_STRIP);
	{
		for (int i = -90; i < 90; i++)
		{
			float alphaOdd = (i)*M_PI / 180.; // angle for odd vertices
			float alphaEven = (i + 1) * M_PI / 180.; // angle for even vertices
			for (int k = 0; k < 360; k++)
			{
				float betaOdd = k * M_PI / 180.; // angle for odd vertices
				float betaEven = k * M_PI / 180.; // angle for even vertices

				glVertex3f(SPHERE_X(radius, alphaOdd, betaOdd),
					SPHERE_Y(radius, alphaOdd),
					SPHERE_Z(radius, alphaOdd, betaOdd));
				glVertex3f(SPHERE_X(radius, alphaEven, betaEven),
					SPHERE_Y(radius, alphaEven),
					SPHERE_Z(radius, alphaEven, betaEven));
			}
		}
	}
	glEnd();
}

void CGLRenderer::drawCone(float radius, float height)
{
	const int elements = (3 * 362);
	float verticesDown[elements], verticesUp[elements];
	u_short baseIndices[elements];

	//center points
	verticesDown[0] = 0; verticesDown[1] = 0; verticesDown[2] = 0;
	verticesUp[0] = 0; verticesUp[1] = height; verticesUp[2] = 0;
	baseIndices[0] = 0; baseIndices[1] = 1; baseIndices[2] = 2;

	for (int i = 1; i <= 361; i++)
	{
		float alpha = (i)*PI / 180.;

		// vertices:
		verticesDown[i * 3] = CIRCLE_X(radius, alpha);
		verticesDown[i * 3 + 1] = 0;
		verticesDown[i * 3 + 2] = CIRCLE_Z(radius, alpha);

		verticesUp[i * 3] = CIRCLE_X(radius, alpha);
		verticesUp[i * 3 + 1] = 0;
		verticesUp[i * 3 + 2] = CIRCLE_Z(radius, alpha);

		baseIndices[i] = i;
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	{
		glVertexPointer(3, GL_FLOAT, 0, verticesDown);
		glDrawElements(GL_TRIANGLE_FAN, 362, GL_UNSIGNED_SHORT, baseIndices);

		glVertexPointer(3, GL_FLOAT, 0, verticesUp);
		glDrawElements(GL_TRIANGLE_FAN, 362, GL_UNSIGNED_SHORT, baseIndices);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}

void CGLRenderer::drawCylinder(float radius, float height)
{
	//const int elements = (3 * 362);
	//float verticesDown[elements], verticesUp[elements], verticesAll[(elements * 2) - 6];
	//u_short baseIndices[362];
	//u_short sideIndices[362 * 2 - 2];

	////center points
	//verticesDown[0] = 0; verticesDown[1] = 0; verticesDown[2] = 0;
	//verticesUp[0] = 0; verticesUp[1] = height; verticesUp[2] = 0;

	//baseIndices[0] = 0;
	//baseIndices[361] = 0; 

	///*verticesAll[0] = 0; verticesAll[1] = 0; verticesAll[2] = 0;
	//verticesAll[3] = 0; verticesAll[4] = height; verticesAll[5] = 0;*/

	//for (int i = 1; i <= 361; i++)
	//{
	//	float alpha = (i)*PI / 180.;

	//	// vertices:
	//	verticesDown[i * 3] = CIRCLE_X(radius, alpha);
	//	verticesDown[i * 3 + 1] = 0;
	//	verticesDown[i * 3 + 2] = CIRCLE_Z(radius, alpha);

	//	verticesUp[i * 3] = CIRCLE_X(radius, alpha);
	//	verticesUp[i * 3 + 1] = height;
	//	verticesUp[i * 3 + 2] = CIRCLE_Z(radius, alpha);

	//	baseIndices[i] = i;

	//	/*verticesAll[360 * 6 + 5] = 5;
	//	sideIndices[360 * 2 + 1] = 10;*/

	//	verticesAll[(i - 1) * 6] = CIRCLE_X(radius, alpha);
	//	verticesAll[(i - 1) * 6 + 1] = 0;
	//	verticesAll[(i - 1) * 6 + 2] = CIRCLE_Z(radius, alpha);
	//	sideIndices[(i - 1) * 2] = (i) * 2;

	//	verticesAll[(i - 1) * 6 + 3] = CIRCLE_X(radius, alpha);
	//	verticesAll[(i - 1) * 6 + 4] = height;
	//	verticesAll[(i - 1) * 6 + 5] = CIRCLE_Z(radius, alpha);
	//	sideIndices[(i - 1) * 2 + 1] = (i - 1) * 2 + 1;
	//}

	///*for (int i = 0; i < (elements * 2) - 6; i += 6)
	//{
	//	float alpha = (i / 6)*PI / 180.;
	//	verticesAll[i] = CIRCLE_X(radius, alpha);
	//	verticesAll[i + 1] = height;
	//	verticesAll[i + 2] = CIRCLE_Z(radius, alpha);
	//	sideIndices[(i / 3)] = i / 3;

	//	verticesAll[i + 3] = CIRCLE_X(radius, alpha);
	//	verticesAll[i + 4] = height;
	//	verticesAll[i + 5] = CIRCLE_Z(radius, alpha);
	//	sideIndices[(i / 3) + 1] = (i / 3) + 1;

	//}*/

	//glEnableClientState(GL_VERTEX_ARRAY);
	//{
	//	glVertexPointer(3, GL_FLOAT, 0, verticesDown);
	//	glDrawElements(GL_TRIANGLE_FAN, 362, GL_UNSIGNED_SHORT, baseIndices);

	//	glVertexPointer(3, GL_FLOAT, 0, verticesUp);
	//	glDrawElements(GL_TRIANGLE_FAN, 362, GL_UNSIGNED_SHORT, baseIndices);

	//	/*glVertexPointer(3, GL_FLOAT, 0, verticesAll);
	//	glDrawElements(GL_QUAD_STRIP, 362 * 2 - 2, GL_UNSIGNED_SHORT, sideIndices);*/
	//}
	//glDisableClientState(GL_VERTEX_ARRAY);

	//delete[] verticesAll;

	float verticesDown[3 * 361], verticesUp[3 * 361], verticesAll[3 * 720];
	u_short baseIndices[362];
	u_short sideIndices[360 * 2 + 2];

	// koord pocetak == centar baze, za ovu gornju samo + height
	verticesDown[0] = 0;
	verticesDown[1] = 0;
	verticesDown[2] = 0;
	verticesUp[0] = 0;
	verticesUp[1] = height;
	verticesUp[2] = 0;

	float alpha = 0.0f;
	for (int i = 3; i < 361 * 3; i += 3)
	{
		// vertices:
		verticesDown[i] = CIRCLE_X(radius, alpha);
		verticesDown[i + 1] = 0;
		verticesDown[i + 2] = CIRCLE_Z(radius, alpha);

		verticesUp[i] = CIRCLE_X(radius, alpha);
		verticesUp[i + 1] = height;
		verticesUp[i + 2] = CIRCLE_Z(radius, alpha);
		alpha++;
	}

	for (int i = 0; i < 3 * 720; i += 6)
	{
		verticesAll[i] = verticesDown[i / 2];
		verticesAll[i + 1] = verticesDown[i / 2 + 1];
		verticesAll[i + 2] = verticesDown[i / 2 + 2];
		verticesAll[i + 3] = verticesUp[i / 2];
		verticesAll[i + 4] = verticesUp[i / 2 + 1];
		verticesAll[i + 5] = verticesUp[i / 2 + 2];
	}

	for (int i = 0; i < 361; i++)
		baseIndices[i] = i;
	baseIndices[361] = baseIndices[1];

	for (int i = 0; i < 360 * 2; i++)
	{
		sideIndices[i] = i;
	}
	sideIndices[360 * 2] = sideIndices[0];
	sideIndices[360 * 2 + 1] = sideIndices[1];

	glEnableClientState(GL_VERTEX_ARRAY);
	{
		glVertexPointer(3, GL_FLOAT, 0, verticesDown);
		glDrawElements(GL_TRIANGLE_FAN, 362, GL_UNSIGNED_SHORT, baseIndices);

		glVertexPointer(3, GL_FLOAT, 0, verticesUp);
		glDrawElements(GL_TRIANGLE_FAN, 362, GL_UNSIGNED_SHORT, baseIndices);

		glVertexPointer(3, GL_FLOAT, 0, verticesAll);
		glDrawElements(GL_QUAD_STRIP, 360 * 2 + 2, GL_UNSIGNED_SHORT, sideIndices);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}

void CGLRenderer::drawPrism(float radius, float height, int numberOfSides)
{
	float verticesDown[3 * 361], verticesUp[3 * 361], verticesAll[3 * 720];
	u_short baseIndices[362];
	u_short sideIndices[360 * 2 + 2];

	// koord pocetak == centar baze, za ovu gornju samo + height
	verticesDown[0] = 0;
	verticesDown[1] = 0;
	verticesDown[2] = 0;
	verticesUp[0] = 0;
	verticesUp[1] = height;
	verticesUp[2] = 0;

	float alpha = 0.0f;
	for (int i = 3; i < 361 * 3; i += 3)
	{
		// vertices:
		verticesDown[i] = CIRCLE_X(radius, alpha);
		verticesDown[i + 1] = 0;
		verticesDown[i + 2] = CIRCLE_Z(radius, alpha);

		verticesUp[i] = CIRCLE_X(radius, alpha);
		verticesUp[i + 1] = height;
		verticesUp[i + 2] = CIRCLE_Z(radius, alpha);
		alpha += (PI / 2);
	}

	for (int i = 0; i < 3 * 720; i += 6)
	{
		verticesAll[i] = verticesDown[i / 2];
		verticesAll[i + 1] = verticesDown[i / 2 + 1];
		verticesAll[i + 2] = verticesDown[i / 2 + 2];
		verticesAll[i + 3] = verticesUp[i / 2];
		verticesAll[i + 4] = verticesUp[i / 2 + 1];
		verticesAll[i + 5] = verticesUp[i / 2 + 2];
	}

	for (int i = 0; i < 361; i++)
		baseIndices[i] = i;
	baseIndices[361] = baseIndices[1];

	for (int i = 0; i < 360 * 2; i++)
	{
		sideIndices[i] = i;
	}
	sideIndices[360 * 2] = sideIndices[0];
	sideIndices[360 * 2 + 1] = sideIndices[1];

	glEnableClientState(GL_VERTEX_ARRAY);
	{
		glVertexPointer(3, GL_FLOAT, 0, verticesDown);
		glDrawElements(GL_TRIANGLE_FAN, 362, GL_UNSIGNED_SHORT, baseIndices);

		glVertexPointer(3, GL_FLOAT, 0, verticesUp);
		glDrawElements(GL_TRIANGLE_FAN, 362, GL_UNSIGNED_SHORT, baseIndices);

		glVertexPointer(3, GL_FLOAT, 0, verticesAll);
		glDrawElements(GL_QUAD_STRIP, 360 * 2 + 2, GL_UNSIGNED_SHORT, sideIndices);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}

void CGLRenderer::drawPyramid(float radius, float height, int numberOfSides)
{
	const int elements = (3 * 362);
	float verticesDown[elements], verticesUp[elements];
	u_short baseIndices[elements];

	//center points
	verticesDown[0] = 0; verticesDown[1] = 0; verticesDown[2] = 0;
	verticesUp[0] = 0; verticesUp[1] = height; verticesUp[2] = 0;
	baseIndices[0] = 0; baseIndices[1] = 1; baseIndices[2] = 2;

	float alpha = 0;
	for (int i = 1; i <= 361; i++)
	{
		

		// vertices:
		verticesDown[i * 3] = CIRCLE_X(radius, alpha);
		verticesDown[i * 3 + 1] = 0;
		verticesDown[i * 3 + 2] = CIRCLE_Z(radius, alpha);

		verticesUp[i * 3] = CIRCLE_X(radius, alpha);
		verticesUp[i * 3 + 1] = 0;
		verticesUp[i * 3 + 2] = CIRCLE_Z(radius, alpha);

		baseIndices[i] = i;

		alpha += PI / 3;
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	{
		glVertexPointer(3, GL_FLOAT, 0, verticesDown);
		glDrawElements(GL_TRIANGLE_FAN, 362, GL_UNSIGNED_SHORT, baseIndices);

		glVertexPointer(3, GL_FLOAT, 0, verticesUp);
		glDrawElements(GL_TRIANGLE_FAN, 362, GL_UNSIGNED_SHORT, baseIndices);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}

void CGLRenderer::drawOctagonalPrism(float radius, float height)
{
	float verticesDown[3 * 361], verticesUp[3 * 361], verticesAll[3 * 720];
	u_short baseIndices[362];
	u_short sideIndices[360 * 2 + 2];

	// koord pocetak == centar baze, za ovu gornju samo + height
	verticesDown[0] = 0;
	verticesDown[1] = 0;
	verticesDown[2] = 0;
	verticesUp[0] = 0;
	verticesUp[1] = height;
	verticesUp[2] = 0;

	float alpha = 0.0f;
	for (int i = 3; i < 361 * 3; i += 3)
	{
		// vertices:
		verticesDown[i] = CIRCLE_X(radius, alpha);
		verticesDown[i + 1] = 0;
		verticesDown[i + 2] = CIRCLE_Z(radius, alpha);

		verticesUp[i] = CIRCLE_X(radius, alpha);
		verticesUp[i + 1] = height;
		verticesUp[i + 2] = CIRCLE_Z(radius, alpha);
		alpha += (PI / 4);
	}

	for (int i = 0; i < 3 * 720; i += 6)
	{
		verticesAll[i] = verticesDown[i / 2];
		verticesAll[i + 1] = verticesDown[i / 2 + 1];
		verticesAll[i + 2] = verticesDown[i / 2 + 2];
		verticesAll[i + 3] = verticesUp[i / 2];
		verticesAll[i + 4] = verticesUp[i / 2 + 1];
		verticesAll[i + 5] = verticesUp[i / 2 + 2];
	}

	for (int i = 0; i < 361; i++)
		baseIndices[i] = i;
	baseIndices[361] = baseIndices[1];

	for (int i = 0; i < 360 * 2; i++)
	{
		sideIndices[i] = i;
	}
	sideIndices[360 * 2] = sideIndices[0];
	sideIndices[360 * 2 + 1] = sideIndices[1];

	glEnableClientState(GL_VERTEX_ARRAY);
	{
		glVertexPointer(3, GL_FLOAT, 0, verticesDown);
		glDrawElements(GL_TRIANGLE_FAN, 362, GL_UNSIGNED_SHORT, baseIndices);

		glVertexPointer(3, GL_FLOAT, 0, verticesUp);
		glDrawElements(GL_TRIANGLE_FAN, 362, GL_UNSIGNED_SHORT, baseIndices);

		glVertexPointer(3, GL_FLOAT, 0, verticesAll);
		glDrawElements(GL_QUAD_STRIP, 360 * 2 + 2, GL_UNSIGNED_SHORT, sideIndices);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}

void CGLRenderer::drawVaseBottom(float bottomRadius, float upRadius, float height)
{
	float verticesDown[3 * 361], verticesUp[3 * 361], verticesAll[3 * 720];
	u_short baseIndices[362];
	u_short sideIndices[360 * 2 + 2];

	// koord pocetak == centar baze, za ovu gornju samo + height
	verticesDown[0] = 0;
	verticesDown[1] = 0;
	verticesDown[2] = 0;
	verticesUp[0] = 0;
	verticesUp[1] = height;
	verticesUp[2] = 0;

	float alpha = 0.0f;
	for (int i = 3; i < 361 * 3; i += 3)
	{
		// vertices:
		verticesDown[i] = CIRCLE_X(bottomRadius, alpha);
		verticesDown[i + 1] = 0;
		verticesDown[i + 2] = CIRCLE_Z(bottomRadius, alpha);

		verticesUp[i] = CIRCLE_X(upRadius, alpha);
		verticesUp[i + 1] = height;
		verticesUp[i + 2] = CIRCLE_Z(upRadius, alpha);
		alpha += (PI / 4);
	}

	for (int i = 0; i < 3 * 720; i += 6)
	{
		verticesAll[i] = verticesDown[i / 2];
		verticesAll[i + 1] = verticesDown[i / 2 + 1];
		verticesAll[i + 2] = verticesDown[i / 2 + 2];
		verticesAll[i + 3] = verticesUp[i / 2];
		verticesAll[i + 4] = verticesUp[i / 2 + 1];
		verticesAll[i + 5] = verticesUp[i / 2 + 2];
	}

	for (int i = 0; i < 361; i++)
		baseIndices[i] = i;
	baseIndices[361] = baseIndices[1];

	for (int i = 0; i < 360 * 2; i++)
	{
		sideIndices[i] = i;
	}
	sideIndices[360 * 2] = sideIndices[0];
	sideIndices[360 * 2 + 1] = sideIndices[1];

	glEnableClientState(GL_VERTEX_ARRAY);
	{
		glVertexPointer(3, GL_FLOAT, 0, verticesDown);
		glDrawElements(GL_TRIANGLE_FAN, 362, GL_UNSIGNED_SHORT, baseIndices);

		glVertexPointer(3, GL_FLOAT, 0, verticesUp);
		glDrawElements(GL_TRIANGLE_FAN, 362, GL_UNSIGNED_SHORT, baseIndices);

		glVertexPointer(3, GL_FLOAT, 0, verticesAll);
		glDrawElements(GL_QUAD_STRIP, 360 * 2 + 2, GL_UNSIGNED_SHORT, sideIndices);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}

void CGLRenderer::drawGrid()
{
	for (int i = 0; i < 11; i++)
	{
		glBegin(GL_LINES);
		{
			
			glVertex3f(-5.0 * unit * 2, 0.0, (-5.0 * unit * 2 + unit * 2 * i));
			glVertex3f(5.0 * unit * 2, 0.0, (-5.0 * unit * 2 + unit * 2 * i));// x axis

			glVertex3f((-5.0 * unit * 2 + unit * 2 * i), 0.0, -5.0 * unit * 2);
			glVertex3f((-5.0 * unit * 2 + unit * 2 * i), 0.0, 5.0 * unit * 2);// z axis
		}
		glEnd();
	}
}

void CGLRenderer::drawCactus()
{
	// lower part:
	glColor3f(0.9, 0.9, 0.2);
	drawCylinder(unit, unit * 2.);
	//drawCone(unit, unit * 2.);
	glTranslatef(0., unit * 2., 0);

	glColor3f(0.2, 0.85, 0.2);
	glTranslatef(0., unit * 0.5, 0.);
	drawSphere(unit * 0.5);

	// right side:
	glPushMatrix();
	{
		glRotatef(-45., 1., 0., 0.);
		glTranslatef(0., unit * 0.5, 0.);
		drawCone(unit * 0.5, unit * 2.);
		glTranslatef(0., unit * 2., 0);
		glTranslatef(0., unit * 0.5, 0.);
		drawSphere(unit * 0.5);
	}
	glPopMatrix();

	// center:
	glPushMatrix();
	{
		glTranslatef(0., unit * 0.5, 0.);
		drawPrism(unit * 0.5, unit * 2., 4);

		glTranslatef(0., unit * 2., 0);
		glTranslatef(0., unit * 0.5, 0.);
		drawSphere(unit * 0.5);

		glTranslatef(0., unit * 0.5, 0.);
		drawPyramid(unit, unit * 2., 6);

		glTranslatef(0., unit * 2., 0);
		glTranslatef(0., unit * 0.5, 0.);
		drawSphere(unit * 0.5);

		glTranslatef(0., unit * 0.5, 0.);
		drawPrism(unit, unit * 2., 4);

		glTranslatef(0., unit * 2., 0);
		glTranslatef(0., unit * 0.5, 0.);
		drawSphere(unit * 0.5);
	}
	glPopMatrix();

	// left side:
	glPushMatrix();
	{
		glRotatef(45., 1., 0., 0.);

		glTranslatef(0., unit * 0.5, 0.);
		drawCylinder(unit * 0.5, unit * 2.);

		glTranslatef(0., unit * 2., 0);
		glTranslatef(0., unit * 0.5, 0.);
		drawSphere(unit * 0.5);

		// left 2:
		glPushMatrix();
		{
			glRotatef(45., 1., 0., 0.);

			glTranslatef(0., unit * 0.5, 0.);
			drawCone(unit * 0.5, unit * 2.);

			glTranslatef(0., unit * 2., 0);
			glTranslatef(0., unit * 0.5, 0.);
			drawSphere(unit * 0.5);

			glTranslatef(0., unit * 0.5, 0.);
			drawPrism(unit, unit * 2., 4);

			glTranslatef(0., unit * 2., 0);
			glTranslatef(0., unit * 0.5, 0.);
			drawSphere(unit * 0.5);
		}
		glPopMatrix();

		// center 2:
		glPushMatrix();
		{

			glTranslatef(0., unit * 0.5, 0.);
			drawCylinder(unit * 0.5, unit * 2.);

			glTranslatef(0., unit * 2., 0);
			glTranslatef(0., unit * 0.5, 0.);
			drawSphere(unit * 0.5);

			glTranslatef(0., unit * 0.5, 0.);
			drawCylinder(unit, unit * 2.);

			glTranslatef(0., unit * 2., 0);
			glTranslatef(0., unit * 0.5, 0.);
			drawSphere(unit * 0.5);
		}
		glPopMatrix();

		// right 2:
		glPushMatrix();
		{
			glRotatef(-45., 1., 0., 0.);

			glTranslatef(0., unit * 0.5, 0.);
			drawCone(unit * 0.5, unit * 2.);

			glTranslatef(0., unit * 2., 0);
			glTranslatef(0., unit * 0.5, 0.);
			drawSphere(unit * 0.5);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void CGLRenderer::drawVase()
{
	glPushMatrix();
	{
		drawVaseBottom(unit * 2., unit * 2.1, unit * 2.);

		glTranslatef(0., unit * 2., 0.);
		drawOctagonalPrism(unit * 2.5, unit);
	}
	glPopMatrix();
}
