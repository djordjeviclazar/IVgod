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

#define CONE_L(h, r) h * h + r * r
#define CONE_NR(h, L) h / L
#define CONE_NY(r, L) r / L
#define CONE_NX(nr, alpha) nr * cos(alpha)
#define CONE_NZ(nr, alpha) nr * sin(alpha)
#define SPHERE_NX(alpha, beta) cos(alpha) * cos(beta)
#define SPHERE_NY(alpha) sin(alpha)
#define SPHERE_NZ(alpha, beta) cos(alpha) * sin(beta)
#define CYLINDER_BASE_NX 0
#define CYLINDER_BASE_NZ 0
#define CYLINDER_UP_NY 1
#define CYLINDER_DOWN_NY -1
#define CYLINDER_SIDE_NX(alpha) cos(alpha)
#define CYLINDER_SIDE_NY 0
#define CYLINDER_SIDE_NZ(alpha) sin(alpha)

#define VECTOR_LENGTH(x, y, z) sqrt(x * x + y * y + z * z)

#define RADIANS(angle) angle * PI / 180
CGLRenderer::CGLRenderer()
{
	eyeZ = 0.;
	eyeX = eyeY = 4 * unit;

	// start angle:
	yaw = asinf(eyeZ);
	pitch = asinf(RADIANS(eyeY / sqrt(eyeX * eyeX + eyeY * eyeY)));

	currentLength = VECTOR_LENGTH(eyeX, eyeY, eyeZ);
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
	glClearColor(0.3, 0.7, 0.9, 0.0);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	//glClearColor(0.3, 0.7, 0.9, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	gluLookAt(eyeX, eyeY, eyeZ,
		0.0, unit, 0.0,
		0.0, 1.0, 0.0);
	//gluLookAt(15, 15, 0, 0, 5, 0, 0, 1, 0);


	glLineWidth(0.5);
	glPointSize(0.1);

	glBegin(GL_LINES);
	{
		glColor3f(1.0, 0.0, 0.0); //x
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(unit * 4.0, 0.0, 0.0);

		glColor3f(0.0, 1.0, 0.0); //y
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, unit * 4.0, 0.0);

		glColor3f(0.0, 0.0, 1.0); //z
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, unit * 4.0);
	}
	glEnd();

	glColor3f(1., 1., 1.);

	// draw:
	glPushMatrix();
	{
		
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
	gluPerspective(45.0, aspect, 10., 50);
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

void CGLRenderer::moveEye(CPoint point)
{
	if (firstRotation)
	{
		startPoint.x = point.x;
		startPoint.y = point.y;
		firstRotation = false;
	}

	float offsetX = (startPoint.x - point.x) * cameraSensitivity;
	float offsetY = (startPoint.y - point.y) * cameraSensitivity;
	startPoint.x = point.x;
	startPoint.y = point.y;

	float newPitch = pitch + offsetY;
	yaw = yaw + offsetX;

	pitch = newPitch > 89.0 ? 89. : (newPitch < -89.0 ? -89.0 : newPitch);

	// new coordinates:
	// oposite sign;  mouse right -> look left:
	double newEyeX = -cos(RADIANS(yaw)) * cos(RADIANS(pitch));
	double newEyeZ = sin(RADIANS(yaw))* cos(RADIANS(pitch));

	// mouse up -> look down:
	double newEyeY = -sin(RADIANS(pitch));

	// normalize:

	eyeX = newEyeX * currentLength;
	eyeY = newEyeY * currentLength;
	eyeZ = newEyeZ * currentLength;
}
