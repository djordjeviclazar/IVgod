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
		0.0, 5., 0.0,
		0.0, 1.0, 0.0);
	//gluLookAt(15, 15, 0, 0, 5, 0, 0, 1, 0);


	glLineWidth(0.5);
	glPointSize(0.1);

	glBegin(GL_LINES);
	{
		glColor3f(1.0, 0.0, 0.0); //x
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(unit * 6.0, 0.0, 0.0);

		glColor3f(0.0, 1.0, 0.0); //y
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, unit * 6.0, 0.0);

		glColor3f(0.0, 0.0, 1.0); //z
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, unit * 6.0);
	}
	glEnd();

	glColor3f(1., 1., 1.);

	// draw:
	glPushMatrix();
	{
		// set global
		GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1. };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
		//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
		//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

		float light_ambient[] = { 0.1, 0.1, 0.1, 1. };
		float light_diffuse[] = { 1., 1., 1., 1. };
		float light_emission[] = { 1., 1., 1., 1. };
		float light_specular[] = { 0., 0., 0., 1. };
		float light_position[] = { unit * 10 / 2, unit * 10. / 2, unit * 10 / 2, 0. };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_EMISSION, light_emission);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);

		CGLMaterial materialDefault;
		materialDefault.Select();


		drawWalls();

		materialDefault.Select();

		drawHalfSphere(unit);
		glTranslatef(0., unit - unit * 0.1, 0.);
		drawCylinderSide(2., 2., 2.);
		glTranslatef(0., 2, 0.);
		drawPrism(1.5 * unit, 1.5 * unit, unit / 2);
		// draw vase:
		glTranslatef(0., unit / 3, 0.);

		CGLMaterial materialVase;

		
		materialVase.SetAmbient(0.5, 0.5, 0.9, 1.);
		materialVase.SetDiffuse(0.2, 0.2, 0.9, 1.);
		materialVase.SetShininess(50.);
		materialVase.SetSpecular(1., 1., 1., 1.);
		materialVase.Select();


		float height = unit / 5.;
		// begin
		drawConeSide(unit * 0.8, unit * 0.6, height); // 1
		glTranslatef(0., height, 0.);
		drawConeSide(unit * 0.6, unit * 0.4, height); // 2
		glTranslatef(0., height, 0.);
		// cylinder
		drawConeSide(unit * 0.4, unit * 0.4, height); // 3
		glTranslatef(0., height, 0.);
		drawConeSide(unit * 0.4, unit * 0.4, height); // 4
		glTranslatef(0., height, 0.);
		// symetric
		drawConeSide(unit * 0.4, unit * 0.6, height); // 5
		glTranslatef(0., height, 0.);
		drawConeSide(unit * 0.6, unit * 0.4, height); // 6
		glTranslatef(0., height, 0.);
		drawConeSide(unit * 0.4, unit * 0.6, height); // 7
		glTranslatef(0., height, 0.);
		drawConeSide(unit * 0.6, unit * 0.4, height); // 8
		// down:
		drawConeSide(unit * 0.4, unit * 0.6, height); // 9
		glTranslatef(0., height, 0.);
		drawConeSide(unit * 0.6, unit * 0.8, height); // 10
		// symetric2:
		drawConeSide(unit * 0.8, unit * 1., height); // 11
		glTranslatef(0., height, 0.);
		drawConeSide(unit * 1., unit * 0.8, height); // 12
		glTranslatef(0., height, 0.);
		drawConeSide(unit * 0.8, unit * 1., height); // 13
		glTranslatef(0., height, 0.);
		drawConeSide(unit * 1., unit * 0.8, height); // 14
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
	gluPerspective(55.0, aspect, 3., 70);
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

void CGLRenderer::drawWalls()
{
	float smallEdge = unit / 5., longEdge = 10 * unit;

	const int nodes = 2 + 100 * 2;
	float leftWall[nodes * 6], rightWall[nodes * 6];
	float frontWall[nodes * 6], backtWall[nodes * 6];
	float bottomWall[nodes * 6];

	//start points:
	float coord = longEdge / 2;
	float downLeft[3] = { coord, 0., coord };
	float downRight[3] = { coord, 0., -coord };
	float downFarLeft[3] = { -coord, 0., coord };
	
	int index = 0;

	int indices[nodes];
	for (int i = 0; i < nodes; i++)
	{
		indices[i] = i;
	}

	for (float i = 0; i < nodes/2; i++) // move up
	{
		index = 0;

		for (float k = 0; k < nodes / 2; k++) // set row
		{
			// bottom wall; y = 0, z = k, x = i
			bottomWall[index] = downLeft[0] - i * smallEdge;
			bottomWall[index + 1] = 0;
			bottomWall[index + 2] = downLeft[2] - k * smallEdge;
			bottomWall[index + 3] = 0;
			bottomWall[index + 4] = 1;
			bottomWall[index + 5] = 0;
			bottomWall[index + 6] = bottomWall[index] - (i + 1) * smallEdge;
			bottomWall[index + 7] = 0;
			bottomWall[index + 8] = bottomWall[index + 2];
			bottomWall[index + 9] = 0;
			bottomWall[index + 10] = 1;
			bottomWall[index + 11] = 0;

			// left wall; z = 0, x = k, y = i
			leftWall[index] = downLeft[0] - k * smallEdge;
			leftWall[index + 1] = downLeft[1] + i * smallEdge;
			leftWall[index + 2] = downLeft[2];
			leftWall[index + 3] = 0;
			leftWall[index + 4] = 0;
			leftWall[index + 5] = 1;
			leftWall[index + 6] = leftWall[index];
			leftWall[index + 7] = leftWall[index + 1] + (i + 1) * smallEdge;
			leftWall[index + 8] = downLeft[2];
			leftWall[index + 9] = 0;
			leftWall[index + 10] = 0;
			leftWall[index + 11] = 1;

			// right wall; z = 0, x = k, y = i
			rightWall[index] = downRight[0] - k * smallEdge;
			rightWall[index + 1] = downRight[1] + i * smallEdge;
			rightWall[index + 2] = downRight[2];
			rightWall[index + 3] = 0;
			rightWall[index + 4] = 0;
			rightWall[index + 5] = -1;
			rightWall[index + 6] = rightWall[index];
			rightWall[index + 7] = rightWall[index + 1] + (i + 1) * smallEdge;
			rightWall[index + 8] = downRight[2];
			rightWall[index + 9] = 0;
			rightWall[index + 10] = 0;
			rightWall[index + 11] = -1;

			// front wall; x = 0, z = k, y = i
			frontWall[index] = downFarLeft[0];
			frontWall[index + 1] = downFarLeft[1] + i * smallEdge;
			frontWall[index + 2] = downFarLeft[2] - k * smallEdge;
			frontWall[index + 3] = 1;
			frontWall[index + 4] = 0;
			frontWall[index + 5] = 0;
			frontWall[index + 6] = frontWall[index];
			frontWall[index + 7] = frontWall[index + 1] + (i + 1) * smallEdge;
			frontWall[index + 8] = frontWall[index + 2];
			frontWall[index + 9] = 1;
			frontWall[index + 10] = 0;
			frontWall[index + 11] = 0;

			// back wall; x = 0, z = k, y = i
			backtWall[index] = downLeft[0];
			backtWall[index + 1] = downLeft[1] + i * smallEdge;
			backtWall[index + 2] = downLeft[2] - k * smallEdge;
			backtWall[index + 3] = -1;
			backtWall[index + 4] = 0;
			backtWall[index + 5] = 0;
			backtWall[index + 6] = backtWall[index];
			backtWall[index + 7] = backtWall[index + 1] + (i + 1) * smallEdge;
			backtWall[index + 8] = backtWall[index + 2];
			backtWall[index + 9] = -1;
			backtWall[index + 10] = 0;
			backtWall[index + 11] = 0;

			index += 12;
		}
		CGLMaterial bottom, right, left, front, back;
		bottom.SetAmbient(0.5, 0.5, 0.5, 1.);
		bottom.SetDiffuse(0.8, 0.8, 0.8, 1.);
		
		right.SetAmbient(0.5, 0.5, 0.5, 1.);
		right.SetDiffuse(0.8, 0.8, 0.8, 1.);

		left.SetAmbient(0.25, 0.25, 0.25, 1.);
		left.SetDiffuse(0.3, 0.3, 0.3, 1.);

		front.SetAmbient(0.4, 0.4, 0.4, 1.);
		front.SetDiffuse(0.8, 0.8, 0.8, 1.);

		back.SetAmbient(0.3, 0.3, 0.3, 1.);
		back.SetDiffuse(0.2, 0.2, 0.2, 1.);
		// draw row:
		glEnableClientState(GL_VERTEX_ARRAY);
		{
			bottom.Select();
			glVertexPointer(3, GL_FLOAT, 6 * sizeof(float), &bottomWall[0]);
			glNormalPointer(GL_FLOAT, 6 * sizeof(float), &bottomWall[3]);
			glDrawElements(GL_QUAD_STRIP, nodes, GL_UNSIGNED_SHORT, indices);

			left.Select();
			glVertexPointer(3, GL_FLOAT, 6 * sizeof(float), &leftWall[0]);
			glNormalPointer(GL_FLOAT, 6 * sizeof(float), &leftWall[3]);
			glDrawElements(GL_QUAD_STRIP, nodes, GL_UNSIGNED_SHORT, indices);

			right.Select();
			glVertexPointer(3, GL_FLOAT, 6 * sizeof(float), &rightWall[0]);
			glNormalPointer(GL_FLOAT, 6 * sizeof(float), &rightWall[3]);
			glDrawElements(GL_QUAD_STRIP, nodes, GL_UNSIGNED_SHORT, indices);

			front.Select();
			glVertexPointer(3, GL_FLOAT, 6 * sizeof(float), &frontWall[0]);
			glNormalPointer(GL_FLOAT, 6 * sizeof(float), &frontWall[3]);
			glDrawElements(GL_QUAD_STRIP, nodes, GL_UNSIGNED_SHORT, indices);

			back.Select();
			glVertexPointer(3, GL_FLOAT, 6 * sizeof(float), &backtWall[0]);
			glNormalPointer(GL_FLOAT, 6 * sizeof(float), &backtWall[3]);
			glDrawElements(GL_QUAD_STRIP, nodes, GL_UNSIGNED_SHORT, indices);
		}
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void CGLRenderer::drawHalfSphere(float radius)
{
	glBegin(GL_QUAD_STRIP);
	{
		for (int i = 0; i < 90; i++)
		{
			float alphaOdd = (i)*M_PI / 180.; // angle for odd vertices
			float alphaEven = (i + 1) * M_PI / 180.; // angle for even vertices
			for (int k = 0; k < 360; k++)
			{
				float betaOdd = k * M_PI / 180.; // angle for odd vertices
				float betaEven = k * M_PI / 180.; // angle for even vertices

				glNormal3f(SPHERE_NX(alphaOdd, betaOdd), SPHERE_NY(alphaOdd), SPHERE_NZ(alphaOdd, betaOdd));
				glVertex3f(SPHERE_X(radius, alphaOdd, betaOdd),
					SPHERE_Y(radius, alphaOdd),
					SPHERE_Z(radius, alphaOdd, betaOdd));

				glNormal3f(SPHERE_NX(alphaEven, betaEven), SPHERE_NY(alphaEven), SPHERE_NZ(alphaEven, betaEven));
				glVertex3f(SPHERE_X(radius, alphaEven, betaEven),
					SPHERE_Y(radius, alphaEven),
					SPHERE_Z(radius, alphaEven, betaEven));
			}
		}
	}
	glEnd();
}

void CGLRenderer::drawCylinderSide(float radiusDown, float radiusUp, float height)
{

	float verticesAll[6 * 720];
	u_short sideIndices[360 * 2 + 2];

	float alpha = 0.0f;
	for (int i = 0; i < 6 * 720; i += 12)
	{
		verticesAll[i] = CIRCLE_X(radiusDown, alpha);
		verticesAll[i + 1] = 0;
		verticesAll[i + 2] = CIRCLE_Z(radiusDown, alpha);
		verticesAll[i + 3] = CYLINDER_SIDE_NX(alpha);
		verticesAll[i + 4] = CYLINDER_SIDE_NY;
		verticesAll[i + 5] = CYLINDER_SIDE_NZ(alpha);


		verticesAll[i + 6] = CIRCLE_X(radiusUp, alpha);
		verticesAll[i + 7] = height;
		verticesAll[i + 8] = CIRCLE_Z(radiusUp, alpha);
		verticesAll[i + 9] = CYLINDER_SIDE_NX(alpha);
		verticesAll[i + 10] = CYLINDER_SIDE_NY;
		verticesAll[i + 11] = CYLINDER_SIDE_NZ(alpha);

		alpha++;
	}

	for (int i = 0; i < 360 * 2; i++)
	{
		sideIndices[i] = i;
	}
	sideIndices[360 * 2] = sideIndices[0];
	sideIndices[360 * 2 + 1] = sideIndices[1];

	glEnableClientState(GL_VERTEX_ARRAY);
	{
		glVertexPointer(3, GL_FLOAT, 6 * sizeof(float), &verticesAll[0]);
		glNormalPointer(GL_FLOAT, 6 * sizeof(float), &verticesAll[3]);

		glDrawElements(GL_QUAD_STRIP, 360 * 2 + 2, GL_UNSIGNED_SHORT, sideIndices);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}

void CGLRenderer::drawPrism(float radiusDown, float radiusUp, float height)
{
	float verticesAll[6 * 8];
	u_short sideIndices[4 * 2 + 2];

	float alpha = PI / 4.;
	for (int i = 0; i < 6 * 8; i += 12)
	{
		verticesAll[i] = CIRCLE_X(radiusDown, alpha);
		verticesAll[i + 1] = 0;
		verticesAll[i + 2] = CIRCLE_Z(radiusDown, alpha);
		verticesAll[i + 3] = CYLINDER_SIDE_NX(alpha);
		verticesAll[i + 4] = CYLINDER_SIDE_NY;
		verticesAll[i + 5] = CYLINDER_SIDE_NZ(alpha);


		verticesAll[i + 6] = CIRCLE_X(radiusUp, alpha);
		verticesAll[i + 7] = height;
		verticesAll[i + 8] = CIRCLE_Z(radiusUp, alpha);
		verticesAll[i + 9] = CYLINDER_SIDE_NX(alpha);
		verticesAll[i + 10] = CYLINDER_SIDE_NY;
		verticesAll[i + 11] = CYLINDER_SIDE_NZ(alpha);

		alpha += PI / 2.;
	}

	glBegin(GL_QUADS);
	{
		glNormal3f(0., -1, 0.);
		glVertex3f(verticesAll[0], 0, verticesAll[3]);
		glNormal3f(0., -1, 0.);
		glVertex3f(-verticesAll[0], 0, verticesAll[0]);
		glNormal3f(0., -1, 0.);
		glVertex3f(-verticesAll[0], 0, -verticesAll[0]);
		glNormal3f(0., -1, 0.);
		glVertex3f(verticesAll[0], 0, -verticesAll[0]);

		glNormal3f(0., 1, 0.);
		glVertex3f(verticesAll[0], height, verticesAll[0]);
		glNormal3f(0., 1, 0.);
		glVertex3f(-verticesAll[0], height, verticesAll[0]);
		glNormal3f(0., 1, 0.);
		glVertex3f(-verticesAll[0], height, -verticesAll[0]);
		glNormal3f(0., 1, 0.);
		glVertex3f(verticesAll[0], height, -verticesAll[0]);
	}
	glEnd();

	for (int i = 0; i < 4 * 2; i++)
	{
		sideIndices[i] = i;
	}
	sideIndices[4 * 2] = sideIndices[0];
	sideIndices[4 * 2 + 1] = sideIndices[1];

	glEnableClientState(GL_VERTEX_ARRAY);
	{
		glVertexPointer(3, GL_FLOAT, 6 * sizeof(float), &verticesAll[0]);
		glNormalPointer(GL_FLOAT, 6 * sizeof(float), &verticesAll[3]);

		glDrawElements(GL_QUAD_STRIP, 4 * 2 + 2, GL_UNSIGNED_SHORT, sideIndices);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}

void CGLRenderer::drawConeSide(float radiusDown, float radiusUp, float height)
{
	

	float verticesAll[6 * 720];
	u_short sideIndices[360 * 2 + 2];

	if (radiusDown != radiusUp)
	{
		// Big cone units:

		float BigH = (height * radiusUp) / (radiusDown - radiusUp);
		float UpperH = BigH - height;
		float BigL = CONE_L(BigH, radiusDown), UpperL = CONE_L(UpperH, radiusUp);
		float Bignr = CONE_NR(BigH, BigL), Uppernr = CONE_NR(UpperH, UpperL);
		float Bigny = CONE_NY(radiusDown, BigL), Upperny = CONE_NY(radiusUp, UpperL);

		float alpha = 0.0f;
		for (int i = 0; i < 6 * 720; i += 12)
		{
			verticesAll[i] = CIRCLE_X(radiusDown, alpha);
			verticesAll[i + 1] = 0;
			verticesAll[i + 2] = CIRCLE_Z(radiusDown, alpha);
			verticesAll[i + 3] = Bignr * CYLINDER_SIDE_NX(alpha);
			verticesAll[i + 4] = Bigny;
			verticesAll[i + 5] = Bignr * CYLINDER_SIDE_NZ(alpha);


			verticesAll[i + 6] = CIRCLE_X(radiusUp, alpha);
			verticesAll[i + 7] = height;
			verticesAll[i + 8] = CIRCLE_Z(radiusUp, alpha);
			verticesAll[i + 9] = Uppernr * CYLINDER_SIDE_NX(alpha);
			verticesAll[i + 10] = Upperny;
			verticesAll[i + 11] = Uppernr * CYLINDER_SIDE_NZ(alpha);

			// draw normals:
			if (normalsOn)
			{
				glDisable(GL_LIGHTING);

				glColor3f(0., 1., 0.);
				glBegin(GL_LINES);
				{
					glVertex3f(verticesAll[i], verticesAll[i + 1], verticesAll[i + 2]);
					glVertex3f(verticesAll[i + 3], verticesAll[i + 4], verticesAll[i + 5]);

					glVertex3f(verticesAll[i + 6], verticesAll[i + 7], verticesAll[i + 8]);
					glVertex3f(verticesAll[i + 9], verticesAll[i + 10], verticesAll[i + 11]);
				}
				glEnd();

				glEnable(GL_LIGHTING);
			}

			alpha++;
		}
	}
	else
	{
		float alpha = 0.0f;
		for (int i = 0; i < 6 * 720; i += 12)
		{
			verticesAll[i] = CIRCLE_X(radiusDown, alpha);
			verticesAll[i + 1] = 0;
			verticesAll[i + 2] = CIRCLE_Z(radiusDown, alpha);
			verticesAll[i + 3] = CYLINDER_SIDE_NX(alpha);
			verticesAll[i + 4] = CYLINDER_SIDE_NY;
			verticesAll[i + 5] = CYLINDER_SIDE_NZ(alpha);


			verticesAll[i + 6] = CIRCLE_X(radiusUp, alpha);
			verticesAll[i + 7] = height;
			verticesAll[i + 8] = CIRCLE_Z(radiusUp, alpha);
			verticesAll[i + 9] = CYLINDER_SIDE_NX(alpha);
			verticesAll[i + 10] = CYLINDER_SIDE_NY;
			verticesAll[i + 11] = CYLINDER_SIDE_NZ(alpha);

			// draw normals:
			if (normalsOn)
			{
				glDisable(GL_LIGHTING);

				glColor3f(0., 1., 0.);
				glBegin(GL_LINES);
				{
					float inten = (VECTOR_LENGTH(verticesAll[i + 3], verticesAll[i + 4], verticesAll[i + 5]));
					glVertex3f(verticesAll[i], verticesAll[i + 1], verticesAll[i + 2]);
					glVertex3f(verticesAll[i] * inten, verticesAll[i + 1] * inten, verticesAll[i + 2] * inten);

					inten = (VECTOR_LENGTH(verticesAll[i + 9], verticesAll[i + 10], verticesAll[i + 11]));
					glVertex3f(verticesAll[i + 6], verticesAll[i + 7], verticesAll[i + 8]);
					glVertex3f(verticesAll[i + 6] * inten, verticesAll[i + 7] * inten, verticesAll[i + 8] * inten);
				}
				glEnd();

				glEnable(GL_LIGHTING);
			}

			alpha++;
		}
	}

	for (int i = 0; i < 360 * 2; i++)
	{
		sideIndices[i] = i;
	}
	sideIndices[360 * 2] = sideIndices[0];
	sideIndices[360 * 2 + 1] = sideIndices[1];

	glEnableClientState(GL_VERTEX_ARRAY);
	{
		glVertexPointer(3, GL_FLOAT, 6 * sizeof(float), &verticesAll[0]);
		glNormalPointer(GL_FLOAT, 6 * sizeof(float), &verticesAll[3]);

		glDrawElements(GL_QUAD_STRIP, 360 * 2 + 2, GL_UNSIGNED_SHORT, sideIndices);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}
