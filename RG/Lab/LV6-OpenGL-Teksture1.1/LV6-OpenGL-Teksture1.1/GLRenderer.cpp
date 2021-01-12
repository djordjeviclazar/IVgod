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
	glDisable(GL_LIGHTING);
	glLoadIdentity();

	gluLookAt(eyeX, eyeY, eyeZ,
		0.0, 0., 0.0,
		0.0, 1.0, 0.0);


	glLineWidth(0.5);
	glPointSize(0.1);

	glBegin(GL_LINES);
	{
		glColor3f(1.0, 0.0, 0.0); //x
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(unit * 16.0, 0.0, 0.0);

		glColor3f(0.0, 1.0, 0.0); //y
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, unit * 16.0, 0.0);

		glColor3f(0.0, 0.0, 1.0); //z
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, unit * 16.0);
	}
	glEnd();

	glColor3f(1., 1., 1.);

	CGLMaterial materialDefault;
	materialDefault.Select();

	// set global
	GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1. };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	float light_ambient[] = { 0.5, 0.5, 0.5, 1. };
	float light_diffuse[] = { 1., 1., 1., 1. };
	float light_emission[] = { 1., 1., 1., 1. };
	float light_specular[] = { 0., 0., 0., 1. };
	float light_position[] = { unit, unit, 0., 0. };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_EMISSION, light_emission);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	// draw:
	drawTruck(14, 7, 5, unit / 2.);
	drawGround(unit / 2.);


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
	gluPerspective(65.0, aspect, 0.1, 100);
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

void CGLRenderer::drawTruck(int height, int width, int depth, int localUnit)
{
	glEnable(GL_TEXTURE_2D);
	UINT texId = LoadTexture("res/tekstura1.bmp");

	drawBody(height, width, depth, localUnit);
	glPushMatrix();
	{
		glTranslatef(2 * localUnit, 5 * localUnit, 0.);
		drawElipsoid(5 * localUnit, 2 * localUnit, 3 * localUnit);
	}
	glPopMatrix();

	glColor3f(1., 1., 1.);

	glDisable(GL_LIGHTING);

	glPushMatrix();
	{
		glTranslatef(-4.5 * localUnit, 0.5 * localUnit, localUnit);
		glRotatef(90., 1., 0., 0.);
		drawWheel(1.4 * localUnit, localUnit, 6. * textureUnit, 14.5 * textureUnit, 1.5 * textureUnit);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(1.5 * localUnit, 0.5 * localUnit, localUnit);
		glRotatef(90., 1., 0., 0.);
		drawWheel(1.4 * localUnit, localUnit, 6. * textureUnit, 14.5 * textureUnit, 1.5 * textureUnit);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-4.5 * localUnit, 0.5 * localUnit, -localUnit * 2);
		glRotatef(90., 1., 0., 0.);
		drawWheel(1.4 * localUnit, localUnit, 6. * textureUnit, 14.5 * textureUnit, 1.5 * textureUnit);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(1.5 * localUnit, 0.5 * localUnit, -localUnit * 2);
		glRotatef(90., 1., 0., 0.);
		drawWheel(1.4 * localUnit, localUnit, 6. * textureUnit, 14.5 * textureUnit, 1.5 * textureUnit);
	}
	glPopMatrix();

	glEnable(GL_LIGHTING);

	glDeleteTextures(1, &texId);
	glDisable(GL_TEXTURE_2D);
}

void CGLRenderer::drawBody(int height, int width, int depth, int localUnit)
{
	const int n = 19 << 4;
	float vertices[n];
	//float indices[38];
	float textureStart = 0.5;

	int vertex, p;

	for (int i = 0; i < 2; i ++)
	{
		int ind = i * (n >> 1);
		int pom = i == 0 ? 1 : -1;
		p = ind;

		// vertex 1:
		{
			// coord.
			vertices[ind++] = -7. * localUnit;
			vertices[ind++] = 0;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = -0.33;
			vertices[ind++] = -0.33;
			vertices[ind++] = 0.33 * pom;

			// texture
			vertices[ind++] = 0;
			vertices[ind++] = textureStart + textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 2:
		{
			// coord.
			vertices[ind++] = -6. * localUnit;
			vertices[ind++] = 0;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.;
			vertices[ind++] = -0.5;
			vertices[ind++] = -0.5 * pom;

			// texture
			vertices[ind++] = textureUnit;
			vertices[ind++] = textureStart + textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 3:
		{
			// coord.
			vertices[ind++] = -6. * localUnit;
			vertices[ind++] = localUnit;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.;
			vertices[ind++] = -0.5;
			vertices[ind++] = -0.5 * pom;

			// texture
			vertices[ind++] = textureUnit;
			vertices[ind++] = textureStart + 2 * textureUnit;


			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 4:
		{
			// coord.
			vertices[ind++] = -5. * localUnit;
			vertices[ind++] = 2 * localUnit;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.;
			vertices[ind++] = -0.5;
			vertices[ind++] = -0.5 * pom;

			// texture
			vertices[ind++] = 2 * textureUnit;
			vertices[ind++] = textureStart + 3 * textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 5:
		{
			// coord.
			vertices[ind++] = -4. * localUnit;
			vertices[ind++] = 2 * localUnit;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.;
			vertices[ind++] = -0.5;
			vertices[ind++] = -0.5 * pom;

			// texture
			vertices[ind++] = 3 * textureUnit;
			vertices[ind++] = textureStart + 3 * textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 6:
		{
			// coord.
			vertices[ind++] = -3. * localUnit;
			vertices[ind++] = localUnit;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.;
			vertices[ind++] = -0.5;
			vertices[ind++] = -0.5 * pom;

			// texture
			vertices[ind++] = 4 * textureUnit;
			vertices[ind++] = textureStart + 2 * textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 7:
		{
			// coord.
			vertices[ind++] = -3. * localUnit;
			vertices[ind++] = 0;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.;
			vertices[ind++] = -0.5;
			vertices[ind++] = -0.5 * pom;

			// texture
			vertices[ind++] = 4 * textureUnit;
			vertices[ind++] = textureStart + textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 8:
		{
			// coord.
			vertices[ind++] = 0.;
			vertices[ind++] = 0;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.;
			vertices[ind++] = -0.5;
			vertices[ind++] = -0.5 * pom;

			// texture
			vertices[ind++] = 7 * textureUnit;
			vertices[ind++] = textureStart + textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 9:
		{
			// coord.
			vertices[ind++] = 0.;
			vertices[ind++] = localUnit;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.;
			vertices[ind++] = -0.5;
			vertices[ind++] = -0.5 * pom;

			// texture
			vertices[ind++] = 7 * textureUnit;
			vertices[ind++] = textureStart + 2 * textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 10:
		{
			// coord.
			vertices[ind++] = localUnit;
			vertices[ind++] = 2 * localUnit;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.;
			vertices[ind++] = -0.5;
			vertices[ind++] = -0.5 * pom;

			// texture
			vertices[ind++] = 8 * textureUnit;
			vertices[ind++] = textureStart + 3 * textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 11:
		{
			// coord.
			vertices[ind++] = 2. * localUnit;
			vertices[ind++] = 2 * localUnit;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.;
			vertices[ind++] = -0.5;
			vertices[ind++] = -0.5 * pom;

			// texture
			vertices[ind++] = 9 * textureUnit;
			vertices[ind++] = textureStart + 3 * textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 12:
		{
			// coord.
			vertices[ind++] = 3. * localUnit;
			vertices[ind++] = localUnit;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.;
			vertices[ind++] = -0.5;
			vertices[ind++] = -0.5 * pom;

			// texture
			vertices[ind++] = 10 * textureUnit;
			vertices[ind++] = textureStart + 2 * textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 13:
		{
			// coord.
			vertices[ind++] = 3. * localUnit;
			vertices[ind++] = 0;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.;
			vertices[ind++] = -0.5;
			vertices[ind++] = -0.5 * pom;

			// texture
			vertices[ind++] = 10 * textureUnit;
			vertices[ind++] = textureStart + textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 14:
		{
			// coord.
			vertices[ind++] = 7. * localUnit;
			vertices[ind++] = 0;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.33;
			vertices[ind++] = -0.33;
			vertices[ind++] = 0.33 * pom;

			// texture
			vertices[ind++] = 14 * textureUnit;
			vertices[ind++] = textureStart + textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 15:
		{
			// coord.
			vertices[ind++] = 7. * localUnit;
			vertices[ind++] = 3. * localUnit;
			vertices[ind++] = depth / 2. * pom;

		// normal
		vertices[ind++] = 0.33;
		vertices[ind++] = 0.33;
		vertices[ind++] = 0.33 * pom;

		// texture
		vertices[ind++] = 14 * textureUnit;
		vertices[ind++] = textureStart + 4 * textureUnit;

		//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
		//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
		//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 16:
		{
		// coord.
		vertices[ind++] = -3. * localUnit;
		vertices[ind++] = 3. * localUnit;
		vertices[ind++] = depth / 2. * pom;

		// normal
		vertices[ind++] = 0.33;
		vertices[ind++] = 0.33;
		vertices[ind++] = 0.33 * pom;

		// texture
		vertices[ind++] = 4 * textureUnit;
		vertices[ind++] = textureStart + 4 * textureUnit;

		//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
		//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
		//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 17:
		{
			// coord.
			vertices[ind++] = -3. * localUnit;
			vertices[ind++] = 7. * localUnit;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.33;
			vertices[ind++] = 0.33;
			vertices[ind++] = 0.33 * pom;

			// texture
			vertices[ind++] = 4 * textureUnit;
			vertices[ind++] = textureStart + 8 * textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 18:
		{
			// coord.
			vertices[ind++] = -5. * localUnit;
			vertices[ind++] = 7. * localUnit;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.33;
			vertices[ind++] = 0.33;
			vertices[ind++] = 0.33 * pom;

			// texture
			vertices[ind++] = 2 * textureUnit;
			vertices[ind++] = textureStart + 8 * textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// vertex 19:
		{
			// coord.
			vertices[ind++] = -7. * localUnit;
			vertices[ind++] = 5. * localUnit;
			vertices[ind++] = depth / 2. * pom;

			// normal
			vertices[ind++] = 0.33;
			vertices[ind++] = 0.33;
			vertices[ind++] = 0.33 * pom;

			// texture
			vertices[ind++] = 0 * textureUnit;
			vertices[ind++] = textureStart + 6 * textureUnit;

			//glNormal3d(vertices[ind - 5], vertices[ind - 4], vertices[ind - 3]);
			//glTexCoord2f(vertices[ind - 2], vertices[ind - 1]);
			//glVertex3d(vertices[ind - 8], vertices[ind - 7], vertices[ind - 6]);
		}

		// draw all polygons with textures:
		{
			vertex = 0;
			glBegin(GL_POLYGON);
			{
				vertex = p + 0;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 2;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 18;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);
			}
			glEnd();

			glBegin(GL_POLYGON);
			{
				vertex = p + 8 * 2;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 3;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 17;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 18;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);
			}
			glEnd();

			glBegin(GL_POLYGON);
			{
				vertex = p + 8 * 4;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 5;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 8;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 9;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);
			}
			glEnd();

			glBegin(GL_POLYGON);
			{
				vertex = p + 8 * 5;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 6;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 7;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 8;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);
			}
			glEnd();

			glBegin(GL_POLYGON);
			{
				vertex = p + 8 * 10;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 11;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 13;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 14;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);
			}
			glEnd();

			glBegin(GL_POLYGON);
			{
				vertex = p + 8 * 11;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 12;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 13;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);
			}
			glEnd();

			glBegin(GL_POLYGON);
			{
				vertex = p + 8 * 14;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 15;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 4;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 10;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);
			}
			glEnd();

			glBegin(GL_POLYGON);
			{
				vertex = p + 8 * 3;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 4;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 15;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 16;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

				vertex = p + 8 * 17;
				glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
				glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
				glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);
			}
			glEnd();
		}
	}

	// draw all polygons without textures:
	glDisable(GL_TEXTURE_2D);
	vertex = 0, p = n >> 1;
	for (int i = 0; i < 19; i++)
	{
		glBegin(GL_POLYGON);
		{
			vertex = 8 * i;
			glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
			//glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
			glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

			vertex = 8 * ((i + 1) % 19);
			glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
			//glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
			glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

			vertex = p + 8 * ((i + 1) % 19);
			glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
			//glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
			glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);

			vertex = p + 8 * i;
			glNormal3d(vertices[vertex + 3], vertices[vertex + 4], vertices[vertex + 5]);
			//glTexCoord2f(vertices[vertex + 6], vertices[vertex + 7]);
			glVertex3d(vertices[vertex], vertices[vertex + 1], vertices[vertex + 2]);
		}
		glEnd();
	}
	glEnable(GL_TEXTURE_2D);

	/*for (int i = 0; i < 38; i++)
	{
		indices[i] = i;
	}*/

	/*glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	{
		glVertexPointer(3, GL_FLOAT, 8 * sizeof(float), &vertices[0]);
		glNormalPointer(GL_FLOAT, 8 * sizeof(float), &vertices[3]);
		//glTexCoordPointer(2, GL_FLOAT, 8 * sizeof(float), &vertices[6]);

		glDrawElements(GL_POLYGON, 19, GL_UNSIGNED_SHORT, &indices[0]);

		glVertexPointer(3, GL_FLOAT, 8 * sizeof(float), &vertices[n >> 1]);
		glNormalPointer(GL_FLOAT, 8 * sizeof(float), &vertices[(n >> 1) + 3]);
		//glTexCoordPointer(2, GL_FLOAT, 8 * sizeof(float), &vertices[(n >> 1) + 6]);

		glDrawElements(GL_POLYGON, 19, GL_UNSIGNED_SHORT, &indices[0]);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);*/
}

void CGLRenderer::drawElipsoid(int radiusX, int radiusY, int radiusZ)
{
	glBegin(GL_QUAD_STRIP);
	{
		float texUnit = 1. / 360;

		for (int i = -90; i < 90; i++)
		{
			int iTexture = i + 90;

			float alphaOdd = (i)*M_PI / 180.; // angle for odd vertices
			float alphaEven = (i + 1) * M_PI / 180.; // angle for even vertices
			for (int k = 0; k < 360; k++)
			{
				float betaOdd = k * M_PI / 180.; // angle for odd vertices
				float betaEven = k * M_PI / 180.; // angle for even vertices

				glNormal3f(SPHERE_NX(alphaOdd, betaOdd), SPHERE_NY(alphaOdd), SPHERE_NZ(alphaOdd, betaOdd));
				glTexCoord2f(1. - k * texUnit, iTexture * texUnit);
				glVertex3f(SPHERE_X(radiusX, alphaOdd, betaOdd),
					SPHERE_Y(radiusY, alphaOdd),
					SPHERE_Z(radiusZ, alphaOdd, betaOdd));

				glNormal3f(SPHERE_NX(alphaEven, betaEven), SPHERE_NY(alphaEven), SPHERE_NZ(alphaEven, betaEven));
				glTexCoord2f(1. - (k + 1) * texUnit, (iTexture + 1) * texUnit);
				glVertex3f(SPHERE_X(radiusX, alphaEven, betaEven),
					SPHERE_Y(radiusY, alphaEven),
					SPHERE_Z(radiusZ, alphaEven, betaEven));
			}
		}
	}
	glEnd();
}

void CGLRenderer::drawWheel(float radius, float height, float textureCenterX, float textureCenterY, float textureRadius)
{
	float verticesDown[3 * 361]; //, verticesUp[3 * 361], verticesAll[3 * 720];
	//u_short baseIndices[362];
	//u_short sideIndices[360 * 2 + 2];
	float textureVertices[2 * 361];

	// koord pocetak == centar baze, za ovu gornju samo + height
	verticesDown[0] = 0;
	verticesDown[1] = 0;
	verticesDown[2] = 0;
	/*verticesUp[0] = 0;
	verticesUp[1] = height;
	verticesUp[2] = 0;*/

	float alpha = 0.0f;
	for (int i = 3; i < 361 * 3; i += 3)
	{
		// vertices:
		verticesDown[i] = CIRCLE_X(radius, alpha);
		verticesDown[i + 1] = 0;
		verticesDown[i + 2] = CIRCLE_Z(radius, alpha);

		alpha++;
	}

	textureVertices[0] = textureCenterX;
	textureVertices[1] = textureCenterY;

	alpha = 0.0f;
	for (int i = 2; i < 361 * 2; i += 2)
	{
		// vertices:
		textureVertices[i] = CIRCLE_X(textureRadius, alpha) + textureCenterX;
		textureVertices[i + 1] = CIRCLE_Z(textureRadius, alpha) + textureCenterY;

		alpha++;
	}

	int k = 0;
	glBegin(GL_TRIANGLE_FAN);// downbase
	for (int i = 0; i < 3 * 361; i += 3)
	{
		glTexCoord2f(textureVertices[k], textureVertices[k + 1]);
		glVertex3d(verticesDown[i], verticesDown[i + 1], verticesDown[i + 2]);

		k += 2;
	}
	glEnd();

	k = 0;
	glBegin(GL_TRIANGLE_FAN);// upbase
	for (int i = 0; i < 3 * 361; i += 3)
	{
		glTexCoord2f(textureVertices[k], textureVertices[k + 1]);
		glVertex3d(verticesDown[i], verticesDown[i + 1] + height, verticesDown[i + 2]);

		k += 2;
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
	k = 0;
	glBegin(GL_TRIANGLE_FAN);// side
	for (int i = 0; i < 3 * 361; i += 3)
	{
		glVertex3d(verticesDown[i], verticesDown[i + 1], verticesDown[i + 2]);
		glVertex3d(verticesDown[i], verticesDown[i + 1] + height, verticesDown[i + 2]);
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

void CGLRenderer::drawGround(int localUnit)
{
	glEnable(GL_TEXTURE_2D);
	UINT texId = LoadTextureRepeat("res/tekstura2.bmp");

	glBegin(GL_QUADS);
	{
		glTexCoord2f(3., 6.);
		glVertex3d(unit * 10, -0.9 * localUnit, unit * 10);

		glTexCoord2f(3., 0);
		glVertex3d(unit * 10, -0.9 * localUnit, -unit * 10);

		glTexCoord2f(0, 0);
		glVertex3d(-unit * 10, -0.9 * localUnit, -unit * 10);

		glTexCoord2f(0, 6.);
		glVertex3d(-unit * 10, -0.9 * localUnit, unit * 10);
	}
	glEnd();

	glDeleteTextures(1, &texId);
	glDisable(GL_TEXTURE_2D);
}

UINT CGLRenderer::LoadTexture(char* fileName)
{
	UINT texID;
	DImage img;
	img.Load(CString(fileName));
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(),
		GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());
	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.Width(), img.Height(), 0,
	GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());*/
	return texID;
}

UINT CGLRenderer::LoadTextureRepeat(char* fileName)
{
	UINT texID;
	DImage img;
	img.Load(CString(fileName));
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(),
		GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());
	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.Width(), img.Height(), 0,
	GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());*/
	return texID;
}
