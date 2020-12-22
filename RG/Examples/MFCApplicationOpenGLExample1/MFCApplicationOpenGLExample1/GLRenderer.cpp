#include "pch.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"

//#pragma comment(lib, "GL\\glut32.lib")
//#pragma comment(lib, "GL\\GLAUX.lib")
//#pragma comment(lib, "GL\\GLU32.lib")

CGLRenderer::CGLRenderer(void)
{
}

CGLRenderer::~CGLRenderer(void)
{
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd ;
   	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
   	pfd.nSize  = sizeof(PIXELFORMATDESCRIPTOR);
   	pfd.nVersion   = 1; 
   	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;   
   	pfd.iPixelType = PFD_TYPE_RGBA; 
   	pfd.cColorBits = 32;
   	pfd.cDepthBits = 24; 
   	pfd.iLayerType = PFD_MAIN_PLANE;
	
	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);
	
	if (nPixelFormat == 0) return false; 

	BOOL bResult = SetPixelFormat (pDC->m_hDC, nPixelFormat, &pfd);
  	
	if (!bResult) return false; 

   	m_hrc = wglCreateContext(pDC->m_hDC); 

	if (!m_hrc) return false; 

	return true;	
}

void CGLRenderer::PrepareScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClearColor(0.3, 0.7, 0.9, 0.0);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	// drawing:
	
	glMatrixMode(GL_MODELVIEW);
	//glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	gluLookAt(0., 0., 2., 0., 0., 0., 0., 1., 0.);
	//glTranslatef(0.0, 0., 0.0);
	//glRotatef(0., 0., 0., 0.);
	
	//axis
	glShadeModel(GL_FLAT);
	glLineWidth(0.5);
	glPointSize(0.1);
	
	glBegin(GL_LINES);
	{
		glColor3f(1.0, 0.0, 0.0); //x
		glVertex3f(0.0, 0.0, -1.0);
		glVertex3f(10.0, 0.0, -1.0);

		glColor3f(0.0, 1.0, 0.0); //y
		glVertex3f(0.0, 0.0, -1.0);
		glVertex3f(0.0, 10.0, -1.0);

		glColor3f(0.0, 0.0, 1.0); //z
		glVertex3f(0.0, 0.0, -1.0);
		glVertex3f(0.0, 0.0, -10.0);

		glColor3f(1.0, 0.0, 0.0); // x
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(10.0, 0.0, 0.0);
		glColor3f(0.0, 1.0, 0.0); // y
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 10.0, 0.0);
		glColor3f(0.0, 0.0, 1.0); // z
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 10.0);
	}
	glEnd();

	glLineWidth(3.0);
	glPointSize(10);
	glBegin(GL_POINTS);
	{
		glColor3f(0.5, 0.0, 0.0);
		glVertex3f(0.3, 0.2, -1.0);
		glVertex3f(0.2, 0.3, -1.0);
		glVertex3f(0.0, 0.0, -1.0);
		glVertex3f(2., -3.0, -1.0);

	}
	glEnd();

	drawSphere(1.);

	glFlush();
	//---------------------------------
	
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC *pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45., (double)w / (double)h, 0.1, 100.);
	glMatrixMode(GL_MODELVIEW);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 
	wglMakeCurrent(NULL,NULL); 
	if(m_hrc) 
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void CGLRenderer::drawSphere(float radius)
{
	glBegin(GL_QUAD_STRIP);
	{
		for (int i = 0; i < 180; i++)
		{
			float alphaOdd = (i - 90) * PI / 180.; // angle for odd vertices
			float alphaEven = (i - 90 + 1) * PI / 180.; // angle for even vertices
			for (int k = 0; k < 360; k++)
			{
				float betaOdd = k * PI / 180.; // angle for odd vertices
				float betaEven = k * PI / 180.; // angle for even vertices

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

void CGLRenderer::drawCylinder(float radius, float height)
{
	int elements = (3 * 361) * 2;
	float* vertices = new float[elements];
	u_short* downBaseIndices = new u_short[elements >> 1], * upperBaseIndices = new u_short[elements >> 1];
	u_short*sideIndices = new u_short[elements - 2];
	
	//center points
	vertices[0] = 0; vertices[1] = 0; vertices[2] = 0;
	downBaseIndices[0] = 0;
	downBaseIndices[1] = 1;
	downBaseIndices[2] = 2;
	int upperBaseFirstIndex = elements >> 1;
	vertices[upperBaseFirstIndex] = 0; 
	vertices[upperBaseFirstIndex + 1] = height; 
	vertices[upperBaseFirstIndex + 2] = 0;
	upperBaseIndices[0] = upperBaseFirstIndex;
	upperBaseIndices[1] = upperBaseFirstIndex + 1;
	upperBaseIndices[2] = upperBaseFirstIndex + 2;

	for (int i = 1; i <= 360; i++)
	{
		float alpha = i * PI / 180.;

		// vertices:
		vertices[i * 3] = CIRCLE_X(radius, alpha);
		vertices[i * 3 + 1] = 0;
		vertices[i * 3 + 2] = CIRCLE_Z(radius, alpha);

		vertices[upperBaseFirstIndex + i * 3] = CIRCLE_X(radius, alpha);
		vertices[upperBaseFirstIndex + i * 3 + 1] = height;
		vertices[upperBaseFirstIndex + i * 3 + 2] = CIRCLE_Z(radius, alpha);

		// indices:
		downBaseIndices[i * 3] = i * 3;
		downBaseIndices[i * 3 + 1] = i * 3 + 1;
		downBaseIndices[i * 3 + 2] = i * 3 + 2;

		upperBaseIndices[i * 3] = upperBaseFirstIndex + i * 3;
		upperBaseIndices[i * 3 + 1] = upperBaseFirstIndex + i * 3 + 1;
		upperBaseIndices[i * 3 + 2] = upperBaseFirstIndex + i * 3 + 2;

		sideIndices[(i - 1) * 6] = i * 3;
		sideIndices[(i - 1) * 6 + 1] = i * 3 + 1;
		sideIndices[(i - 1) * 6 + 2] = i * 3 + 2;
		sideIndices[(i - 1) * 6] = upperBaseFirstIndex + i * 3;
		sideIndices[(i - 1) * 6 + 1] = upperBaseFirstIndex + i * 3 + 1;
		sideIndices[(i - 1) * 6 + 2] = upperBaseFirstIndex + i * 3 + 2;
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	{
		glVertexPointer(3, GL_FLOAT, 0, vertices);

		glDrawElements(GL_TRIANGLE_FAN, elements >> 1, GL_UNSIGNED_SHORT, downBaseIndices);
		glDrawElements(GL_TRIANGLE_FAN, elements >> 1, GL_UNSIGNED_SHORT, upperBaseIndices);
		glDrawElements(GL_QUAD_STRIP, elements - 2, GL_UNSIGNED_SHORT, upperBaseIndices);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}
