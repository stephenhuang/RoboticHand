// ================================================================

// OPENGL Source File

// ================================================================

#include "stdafx.h"
#include <Windows.h>
#include "Form1.h"

#pragma comment (lib, "user32.lib")

// Temporary value initialization
GLfloat angle = 0.0f; 

// All vertex information
c_p_v f_p[12];

// Temporary coordinate/vertex variable
c_p_v temp;

// Flag so that only one phalanx is handled at a time
bool FLAG_PHALANX_BUSY;

// State of mouse: leftButton, rightButton, middleButton (not used), x, y, old_x, old_y
g_mouseState  MouseState; 

// Rotation values
float g_xRotation, g_yRotation, g_xViewRot;

// ================================================================
// COpenGL: 
// Default constructor (completely empty) (not used)
// ================================================================
OpenGLForm::COpenGL::COpenGL(){};

// ================================================================
// COpenGL_one: 
// Calculates number of uController cycles for required degrees
// ================================================================
 int OpenGLForm::COpenGL::COpenGL_one(GLsizei iWidth, GLsizei iHeight){
			CreateParams^ cp = gcnew CreateParams;

			// Create model objects
			palmHand -> Model_init();
			phalanx1Hand -> Model_init();
			phalanx2Hand -> Model_init();
			phalanx3Hand -> Model_init();
			
			// Load model files (make sure they exist)
			palmHand -> loadModel("palm.obj");
			phalanx1Hand -> loadModel("phalanx1.obj");
			phalanx2Hand -> loadModel("phalanx2.obj");
			phalanx3Hand -> loadModel("phalanx3.obj");

			// Set the position on the form
			cp->X = 0;
			cp->Y = 0;
			cp->Height = iHeight;
			cp->Width = iWidth;

			// Pointer to panel on the form
			System::Windows::Forms::Panel ^ tinyPanel = f_one -> return_panel();
			
			// Specify the form as the parent
			cp->Parent = tinyPanel -> Handle;
			tinyPanel->Focus();
			
			// Create as a child of the specified parent and make OpenGL compliant (no clipping)
			cp->Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_DISABLED;

			// Create the actual window
			this->CreateHandle(cp);

			m_hDC = GetDC((HWND)this->Handle.ToPointer());

			if(m_hDC)
			{
				MySetPixelFormat(m_hDC);
				ReSizeGLScene(iWidth, iHeight);
				InitGL();
			}

			// Initialize
			f_p[0].theta = 90.0f;
			f_p[1].theta = 90.0f;
			f_p[2].theta = 90.0f;

			f_p[4].theta = 90.0f;
			f_p[5].theta = 90.0f;
			f_p[6].theta = 90.0f;

			f_p[8].theta = 90.0f;
			f_p[9].theta = 90.0f;
			f_p[10].theta = 90.0f;

			// Initialize the track bars
			for (int i = 0; i < 3; i++)
			{
				f_one -> update_TrackBar(i);
			}
			for (int i = 4; i < 7; i++)
			{
				f_one -> update_TrackBar(i);
			}
			for (int i = 8; i < 11; i++)
			{
				f_one -> update_TrackBar(i);
			}

	return TRUE;
}

// ================================================================
// dt: 
// Calculates determinant of a matrix
// | a b |
// | c d |
// ================================================================
 GLfloat OpenGLForm::COpenGL::dt(GLfloat a, GLfloat b, GLfloat c, GLfloat d)
		{
			return (a*d-b*c);
		}

// ================================================================
// rotatePointAboutLine: 
// Rotates point at (a,b,c) around vector (u,v,w) that goes
// through point (x,yz) about (angle)
// ================================================================
void OpenGLForm::COpenGL::rotatePointAboutLine(GLfloat a, GLfloat b, GLfloat c, GLfloat u, GLfloat v, GLfloat w, GLfloat x, GLfloat y, GLfloat z, GLfloat angle)
		{
			GLfloat bv = b*v;
			GLfloat cw = c*w;
			GLfloat ux = u*x;
			GLfloat vy = v*y;
			GLfloat wz = w*z;
			GLfloat cv = c*v;
			GLfloat bw = b*w;
			GLfloat wy = w*y;
			GLfloat vz = v*z;
			GLfloat au = a*u;
			GLfloat cu = c*u;
			GLfloat aw = a*w;
			GLfloat wx = w*x;
			GLfloat uz = u*z;
			GLfloat bu = b*u;
			GLfloat av = a*v;
			GLfloat vx = v*x;
			GLfloat uy = u*y;
			GLfloat ta = angle/180.0f * 3.14159f;

			temp.x = (a*(pow(v,2)+pow(w,2)) - u*(bv+cw-ux-vy-wz))*(1.0f-cos(ta)) + x*cos(ta) + (-1.0f*cv+bw-wy+vz)*sin(ta);
			temp.y = (b*(pow(u,2)+pow(w,2)) - v*(au+cw-ux-vy-wz))*(1.0f-cos(ta)) + y*cos(ta) + (cu-aw+wx-uz)*sin(ta);
			temp.z = (c*(pow(u,2)+pow(v,2)) - w*(au+bv-ux-vy-wz))*(1.0f-cos(ta)) + z*cos(ta) + (-1.0f*bu+av-vx+uy)*sin(ta);
		}

// ================================================================
// dotProduct: 
// Dot product of vectors (a) and (b)
// ================================================================
GLfloat OpenGLForm::COpenGL::dotProduct(c_p_v a, c_p_v b)
		{
			return ((a.x*b.x)+(a.y*b.y)+(a.z*b.z));
		}

// ================================================================
// findOrthogonalAxis: 
// Orthogonal axis at vertex (v)
// ================================================================
void OpenGLForm::COpenGL::findOrthogonalAxis(int v)
		{
				c_p_v a, b, ref, nv;
				GLfloat mag, tang, t_d, mod;

				ref.x = 0.0f; ref.y = 1.0f; ref.z = 0.0f;

				if ((v == 0)|(v == 4)|(v == 8))
				{	
					temp.x = 0.0f;
					temp.y = 0.0f;
					temp.z = 0.0f;
				}
				else
				{
					temp = f_p[v-1];
				}

				// Calculate vectors around axis
				a.x = temp.x - f_p[v].x;
				a.y = temp.y - f_p[v].y;
				a.z = temp.z - f_p[v].z;

				b.x = f_p[v+1].x - f_p[v].x;
				b.y = f_p[v+1].y - f_p[v].y;
				b.z = f_p[v+1].z - f_p[v].z;

				if (f_p[v].theta > 180){
					mod = -1.0f;
				}
				else
				{
					mod = 1.0f;			
				}

				// Determinant
				nv.x = a.y*b.z - a.z*b.y;
				nv.y = a.z*b.x - a.x*b.z;
				nv.z = a.x*b.y - a.y*b.x; 

				mag = sqrt(pow(nv.x,2) + pow(nv.y,2) + pow(nv.z,2));

				tang = atan2(mag, dotProduct(a,b));

				t_d = dotProduct(nv, ref);
				// Write orthogonal vector into temp
				temp.x = mod * nv.x/mag;
				temp.y = mod * nv.y/mag;
				temp.z = mod * nv.z/mag;
		}

// ================================================================
// spinAroundPoint: 
// Change theta at (vertex) by (angle)
// ================================================================
void OpenGLForm::COpenGL::spinAroundPoint(int vertex, GLfloat angle)
		{
			GLfloat a, b, c, u, v, w, limit;

			a = f_p[vertex].x;
			b = f_p[vertex].y;
			c = f_p[vertex].z;

			u = f_p[vertex].n_x;
			v = f_p[vertex].n_y;
			w = f_p[vertex].n_z;

			if ((vertex == 0)|(vertex == 4)|(vertex == 8)) // If at finger origin, whole finger rotates
			{
				limit = 3;
			}
			else if ((vertex == 1)|(vertex == 5)|(vertex == 9))
			{
				limit = 2;
			}
			else if ((vertex == 2)|(vertex == 6)|(vertex == 10))
			{
				limit = 1;
			}
			else
			{
				limit = 0;
			}

			GLfloat t_a_1 = addAngle(vertex, angle);
			GLfloat t_a_2 =  t_a_1 - f_p[vertex].theta;
			f_p[vertex].theta = t_a_1;
			for (int i = 0; i < limit; i++)
			{
				rotatePointAboutLine(a, b, c, u, v, w, f_p[vertex+1].x,f_p[vertex+1].y, f_p[vertex+1].z, t_a_2);

				f_p[vertex+1].x = temp.x;
				f_p[vertex+1].y = temp.y;
				f_p[vertex+1].z = temp.z;
				vertex++;				
			}	

		}

// ================================================================
// addAngle: 
// Add (angle) to value of theta at vertex
// f_p is not directly updated
// Returns a value
// ================================================================
GLfloat OpenGLForm::COpenGL::addAngle(int vertex, GLfloat angle)
		{	
			GLfloat temp = f_p[vertex].theta + angle;

			if ((vertex == 0)|(vertex == 1)|(vertex == 2)|(vertex == 5)|(vertex == 6)|(vertex == 9)|(vertex == 10))
			{
					if (temp <= 0.0f){temp = 0.0f;}
					else if (temp >= 180.0f){temp = 180.0f;}
			}
			else if (vertex == 4)
			{
					if (temp <= 70.0f){temp = 70.0f;}
					else if (temp >= 180.0f){temp = 180.0f;}
			}
			else if (vertex == 8)
			{
					if (temp <= 0.0f){temp = 0.0f;}
					else if (temp >= 110.0f){temp = 110.0f;}
			}
			
			return temp;
		}

// ================================================================
// updateAngle: 
// Add (angle) to theta at vertex. Update model values (f_p)
// ================================================================
void OpenGLForm::COpenGL::updateAngle(int vertex, GLfloat angle)
{	
		GLfloat temp = f_p[vertex].theta + angle;

		if ((vertex == 0)|(vertex == 1)|(vertex == 2)|(vertex == 5)|(vertex == 6)|(vertex == 9)|(vertex == 10))
		{
				if (temp <= 0.0f){f_p[vertex].theta = 0.0f;}
				else if (temp >= 180.0f){f_p[vertex].theta = 180.0f;}
				else {f_p[vertex].theta = temp;}
		}
		else if (vertex == 4)
		{
				if (temp <= 70.0f){f_p[vertex].theta = 70.0f;}
				else if (temp >= 180.0f){f_p[vertex].theta = 180.0f;}
				else {f_p[vertex].theta = temp;}
		}
		else if (vertex == 8)
		{
				if (temp <= 0.0f){f_p[vertex].theta = 0.0f;}
				else if (temp >= 110.0f){f_p[vertex].theta = 110.0f;}
				else {f_p[vertex].theta = temp;}
		}
}

// ================================================================
// DrawGLScene: 
// Draw objects in the scene
// ================================================================
int OpenGLForm::COpenGL::DrawGLScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // Clear screen and depth buffer
	glLoadIdentity();
	gluLookAt(eyex+3.0f, eyey+3.0f, eyez+3.0f, focusx, focusy, focusz, 0,1,0);
									
	glRotatef(g_xRotation, 0,1,0); // Update mouse rotations
	glRotatef(g_yRotation, 1,0,0);

	// Draw objects in the GL Scene
	DrawPalm();
	DrawFinger1();
	DrawFinger2();
	DrawFinger3();
			
	return TRUE;
}

// ================================================================
// DrawPalm: 
// Draw palm from stored mesh
// ================================================================
void OpenGLForm::COpenGL::DrawPalm(void)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f); // Use proper color - white
	palmHand -> draw();
	glPopMatrix(); // Return to origin
}

// ================================================================
// DrawFinger1: 
// Draw blue finger (1), return to origin after
// ================================================================
void OpenGLForm::COpenGL::DrawFinger1(void)
{
	glPushMatrix();
		// CONSTANT: Move to first vertex
		glTranslatef(0.0f, 0.0f, 1.87f); 
									
		glRotatef(f_p[0].theta, 0, 0, 1); // Do rotation for phalanx 1 with specified angle
		glColor3f(0.0627f, 0.306f, 0.545f); // Use proper color - blue
		phalanx1Hand -> draw(); 
						
		// CONSTANT: Necessary adjustment because of model file offset (nobody's perfect, okay?)
		glTranslatef(0.0f, 0.03f, 0.0f);
						
		// CONSTANT: Move to second vertex
		glTranslatef(1.3f, 0.0f, 0.0f); 
			
		glRotatef(f_p[1].theta, 0, 1, 0); // Do rotation for phalanx 2 with specified angle
		phalanx2Hand -> draw();

		// CONSTANT: Rotate to third vertex
		glRotatef(-90.0f, 0, 1, 0);
			
		// CONSTANT: Move to third vertex
		glTranslatef(2.0f, 0.0f, 0.0f);
			
		glRotatef(f_p[2].theta, 0, 1, 0); // Do rotation for phalanx 3 with specified angle
		phalanx3Hand -> draw();

	glPopMatrix();
}

// ================================================================
// DrawFinger2: 
// Draw red finger (2), return to origin after
// ================================================================
void OpenGLForm::COpenGL::DrawFinger2(void)
{
	glPushMatrix();

			// CONSTANT: Keep parts right side up
			glRotatef(90.0f, 0, 0, 1);							
			// CONSTANT: Rotate 60 degrees because of palm orientation
			glRotatef(60.0f, 0, 1, 0);
			// CONSTANT: Rotate part 180 degrees to match prototype
			glRotatef(180.0f, 1, 0, 0);

			// CONSTANT: Move to first vertex
			glTranslatef(0.0f, 0.6f, 1.6f);
			glRotatef((f_p[4].theta-90.0f), 0, 0, 1); // Do rotation for phalanx 1 with specified angle
			glColor3f(205.0f/255.0f, 51.0f/255.0f, 51.0f/255.0f); // Use proper color - red
			phalanx1Hand -> draw();

			// CONSTANT: Necessary adjustment because of model file offset
			glTranslatef(0.0f, 0.03f, 0.0f);
						
			// CONSTANT: Move to second vertex
			glTranslatef(1.3f, 0.0f, 0.0f);
			glRotatef(f_p[5].theta, 0, 1, 0); // Do rotation for phalanx 2 with specified angle
			phalanx2Hand -> draw();

			// CONSTANT: Rotate to third vertex
			glRotatef(-90.0f, 0, 1, 0);

			// CONSTANT: Move to third vertex
			glTranslatef(2.0f, 0.0f, 0.0f);
			
			glRotatef(f_p[6].theta, 0, 1, 0); // Do rotation for phalanx 3 with specified angle
			phalanx3Hand -> draw();

	glPopMatrix();
}

// ================================================================
// DrawFinger3: 
// Draw green finger (3), return to origin after
// ================================================================
void OpenGLForm::COpenGL::DrawFinger3(void)
{
	glPushMatrix();

		// CONSTANT: Keep parts right side up
		glRotatef(90.0f, 0, 0, 1);
		// CONSTANT: Rotate 60 degrees because of palm orientation
		glRotatef(60.0f, 0, 1, 0);
		// CONSTANT: Rotate part 180 degrees to match prototype
		glRotatef(180.0f, 1, 0, 0);

		// Move to next finger - FINGER 3
		glTranslatef(-0.0f, -0.6f, 1.6f);
		glColor3f((34.0f/255.0f), (139.0f/255.0f), (34.0f/255.0f)); // Use proper color - green
		glRotatef((f_p[8].theta-90.0f), 0, 0, 1); // Do rotation for phalanx 1 with specified angle
		phalanx1Hand -> draw();

		// CONSTANT: Necessary adjustment because of model file offset
		glTranslatef(0.0f, 0.03f, 0.0f);
						
		// CONSTANT: Move to second vertex
		glTranslatef(1.3f, 0.0f, 0.0f);
		glRotatef(f_p[9].theta, 0, 1, 0); // Do rotation for phalanx 2 with specified angle
		phalanx2Hand -> draw();

		// CONSTANT: Rotate to third vertex
		glRotatef(-90.0f, 0, 1, 0);

		// CONSTANT: Move to third vertex
		glTranslatef(2.0f, 0.0f, 0.0f);
			
		glRotatef(f_p[10].theta, 0, 1, 0); // Do rotation for phalanx 3 with specified angle
		phalanx3Hand -> draw();

	glPopMatrix();
}

// ================================================================
// DrawGLSceneSelect: 
// Draw part of scene for picking purposes
// This isn't split into separate objects as DrawGLScene is
// ================================================================
int OpenGLForm::COpenGL::DrawGLSceneSelect(void)
		{
			glLoadIdentity();
			
			gluLookAt(eyex+3.0f, eyey+3.0f, eyez+3.0f, focusx, focusy, focusz, 0,1,0);
			glPushMatrix();
						
			glRotatef(g_xRotation, 0,1,0); // Rotate with mouse
			glRotatef(g_yRotation, 1,0,0);

			// --------------------------------------------------------------------------------------
			// DRAW PALM
			glColor3f(1.0f, 1.0f, 1.0f); // Use proper color - white
			palmHand -> draw();
			// --------------------------------------------------------------------------------------
			// --------------------------------------------------------------------------------------
			// DRAW FINGER 1
			// CONSTANT: Move to first vertex
			glTranslatef(0.0f, 0.0f, 1.87f); 
									
			glRotatef(f_p[0].theta, 0, 0, 1); // Do rotation for phalanx 1 with specified angle
			glColor3f(0.0f, 0.0f, 1.0f); // Use proper color - blue
			glLoadName(1);
			phalanx1Hand -> draw(); 
						
			// CONSTANT: Necessary adjustment because of model file offset (nobody's perfect, okay?)
			glTranslatef(0.0f, 0.03f, 0.0f);
						
			// CONSTANT: Move to second vertex
			glTranslatef(1.3f, 0.0f, 0.0f); 
			
			glRotatef(f_p[1].theta, 0, 1, 0); // Do rotation for phalanx 2 with specified angle
			glLoadName(2);
			phalanx2Hand -> draw();

			// CONSTANT: Rotate to third vertex
			glRotatef(-90.0f, 0, 1, 0);
			
			// CONSTANT: Move to third vertex
			glTranslatef(2.0f, 0.0f, 0.0f);
			
			glRotatef(f_p[2].theta, 0, 1, 0); // Do rotation for phalanx 3 with specified angle
			glLoadName(3);
			phalanx3Hand -> draw();
			
			// CONSTANT: Return to origin
			// Undo rotations and translations in proper order
			glRotatef((-1.0f*f_p[2].theta), 0, 1, 0); // Phalanx 3 rotation
			glTranslatef(-2.0f, 0.0f, 0.0f); // Phalanx 3 translation
			glRotatef(90.0f, 0, 1, 0); // Rotation to Phalanx 3
			glRotatef((-1.0f*f_p[1].theta), 0, 1, 0); // Phalanx 2
			glTranslatef(-1.3f, -0.03f, 0.0f); // Phalanx 2 translation and adjustment
			glRotatef((-1.0f*f_p[0].theta), 0, 0, 1); // Rotation to Phalanx 1
			glTranslatef(0.0f, 0.0f, -1.87f); // Phalanx 1 translation
			// --------------------------------------------------------------------------------------

			// CONSTANT: Keep parts right side up
			glRotatef(90.0f, 0, 0, 1);
			
			// --------------------------------------------------------------------------------------
			// DRAW FINGER 2
					
			// CONSTANT: Rotate 60 degrees because of palm orientation
			glRotatef(60.0f, 0, 1, 0);
			// CONSTANT: Rotate part 180 degrees to match prototype
			glRotatef(180.0f, 1, 0, 0);

			// CONSTANT: Move to first vertex
			glTranslatef(0.0f, 0.6f, 1.45f);
			glRotatef((f_p[4].theta-90.0f), 0, 0, 1); // Do rotation for phalanx 1 with specified angle
			glColor3f(1.0f, 0.0f, 0.0f); // Use proper color - red
			glLoadName(5);
			phalanx1Hand -> draw();

			// CONSTANT: Necessary adjustment because of model file offset
			glTranslatef(0.0f, 0.03f, 0.0f);
						
			// CONSTANT: Move to second vertex
			glTranslatef(1.3f, 0.0f, 0.0f);
			glRotatef(f_p[5].theta, 0, 1, 0); // Do rotation for phalanx 2 with specified angle
			glLoadName(6);
			phalanx2Hand -> draw();

			// CONSTANT: Rotate to third vertex
			glRotatef(-90.0f, 0, 1, 0);

			// CONSTANT: Move to third vertex
			glTranslatef(2.0f, 0.0f, 0.0f);
			
			glRotatef(f_p[6].theta, 0, 1, 0); // Do rotation for phalanx 3 with specified angle
			glLoadName(7);
			phalanx3Hand -> draw();
			
			// CONSTANT: Return to origin
			// Undo rotations and translations in proper order
			glRotatef((-1.0f*f_p[6].theta), 0, 1, 0); // Phalanx 3 rotation
			glTranslatef(-2.0f, 0.0f, 0.0f); // Phalanx 3 translation
			glRotatef(90.0f, 0, 1, 0); // Rotation to Phalanx 3
			glRotatef((-1.0f*f_p[5].theta), 0, 1, 0); // Phalanx 2
			glTranslatef(-1.3f, -0.03f, 0.0f); // Phalanx 2 translation and adjustment
			glRotatef((-1.0f*(f_p[4].theta-90.0f)), 0, 0, 1); // Rotation to Phalanx 1
			glTranslatef(0.2f, -0.6f, -1.6f); // Phalanx 1 translation
			// --------------------------------------------------------------------------------------
			// --------------------------------------------------------------------------------------
			// DRAW FINGER 3

			// Move to next finger - FINGER 3
			glTranslatef(-0.2f, -0.6f, 1.6f);
			glColor3f(0.0f, 1.0f, 0.0f); // Use proper color - green
			glRotatef((f_p[8].theta-90.0f), 0, 0, 1); // Do rotation for phalanx 1 with specified angle
			glLoadName(9);
			phalanx1Hand -> draw();

			// CONSTANT: Necessary adjustment because of model file offset
			glTranslatef(0.0f, 0.03f, 0.0f);
						
			// CONSTANT: Move to second vertex
			glTranslatef(1.3f, 0.0f, 0.0f);
			glRotatef(f_p[9].theta, 0, 1, 0); // Do rotation for phalanx 2 with specified angle
			glLoadName(10);
			phalanx2Hand -> draw();

			// CONSTANT: Rotate to third vertex
			glRotatef(-90.0f, 0, 1, 0);

			// CONSTANT: Move to third vertex
			glTranslatef(2.0f, 0.0f, 0.0f);
			
			glRotatef(f_p[10].theta, 0, 1, 0); // Do rotation for phalanx 3 with specified angle
			glLoadName(11);
			phalanx3Hand -> draw();
			
			// CONSTANT: Return to origin
			// Undo rotations and translations in proper order
			glRotatef((-1.0f*f_p[10].theta), 0, 1, 0); // Phalanx 3 rotation
			glTranslatef(-2.0f, 0.0f, 0.0f); // Phalanx 3 translation
			glRotatef(90.0f, 0, 1, 0); // Rotation to Phalanx 3
			glRotatef((-1.0f*f_p[9].theta), 0, 1, 0); // Phalanx 2
			glTranslatef(-1.3f, -0.03f, 0.0f); // Phalanx 2 translation and adjustment
			glRotatef((-1.0f*(f_p[8].theta-90.0f)), 0, 0, 1); // Rotation to Phalanx 1
			glTranslatef(0.2f, -0.6f, -1.6f); // Phalanx 1 translation

		glPopMatrix();
		
		return TRUE;
		}

// ================================================================
// SwapOpenGLBuffers: 
// Swap front and back buffers
// ================================================================
void OpenGLForm::COpenGL::SwapOpenGLBuffers(void)
		{
			SwapBuffers(m_hDC) ;
		}

// ================================================================
// MySetPixelFormat: 
// Set pixel format for current handle
// ================================================================
GLint OpenGLForm::COpenGL::MySetPixelFormat(HDC hdc)
	{
		static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
			{
				sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
				1,											// Version Number
				PFD_DRAW_TO_WINDOW |						// Format Must Support Window
				PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
				PFD_DOUBLEBUFFER,							// Must Support Double Buffering
				PFD_TYPE_RGBA,								// Request An RGBA Format
				16,										// Select Our Color Depth
				0, 0, 0, 0, 0, 0,							// Color Bits Ignored
				0,											// No Alpha Buffer
				0,											// Shift Bit Ignored
				0,											// No Accumulation Buffer
				0, 0, 0, 0,									// Accumulation Bits Ignored
				16,											// 16Bit Z-Buffer (Depth Buffer)  
				0,											// No Stencil Buffer
				0,											// No Auxiliary Buffer
				PFD_MAIN_PLANE,								// Main Drawing Layer
				0,											// Reserved
				0, 0, 0										// Layer Masks Ignored
			};
			
		GLint  iPixelFormat; 
		 
		// get the device context's best, available pixel format match 
		if((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
		{
			MessageBox::Show("ChoosePixelFormat Failed");
			return 0;
		}
			 
		// make that match the device context's current pixel format 
		if(SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
		{
			MessageBox::Show("SetPixelFormat Failed");
			return 0;
		}

		if((m_hglrc = wglCreateContext(m_hDC)) == NULL)
		{
			MessageBox::Show("wglCreateContext Failed");
			return 0;
		}

		if((wglMakeCurrent(m_hDC, m_hglrc)) == NULL)
		{
			MessageBox::Show("wglMakeCurrent Failed");
			return 0;
		}


		return 1;
	}

// ================================================================
// InitGL: 
// Initialize model shading, view, depth
// ================================================================
bool OpenGLForm::COpenGL::InitGL(GLvoid)										
		{
			glShadeModel(GL_SMOOTH);							// Enable smooth shading
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			    // Black background
			glClearDepth(1.0f);		
			
			// Initialize the mouse state
			MouseState.leftButton = MouseState.rightButton = MouseState.middleButton = false;
			MouseState.x = MouseState.y = 0;

			// Initialize view
			eyex = 0;
			eyey = 0;
			eyez = 5;
			focusx = focusy = focusz = 0.0f;

			glEnable(GL_DEPTH_TEST);							// Enables depth testing
			glDepthFunc(GL_LEQUAL);	
			// The type of depth testing to do
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really nice perspective calculations
			return TRUE;										// Initialisation went ok
		}

// ================================================================
// ReSizeGLScene: 
// Resize scene (never used really)
// ================================================================
GLvoid OpenGLForm::COpenGL::ReSizeGLScene(GLsizei width, GLsizei height)		// Resize and initialise the gl window
		{
			if (height==0)										// Prevent A Divide By Zero By
			{
				height=1;										// Making Height Equal One
			}

			glViewport(0,0,width,height);						// Reset The Current Viewport

			glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
			glLoadIdentity();		
			
			// Calculate The Aspect Ratio Of The Window
			gluPerspective(60.0f,785.0f/528.0f,0.1f,1000.0f);

			glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
			glLoadIdentity();									// Reset The Modelview Matrix
		}

// ================================================================
// KILLGLWindow: 
// Kill the rendering (never used)
// ================================================================
GLvoid OpenGLForm::COpenGL::KILLGLWindow(GLvoid)
{
}

// ================================================================
// updateRotations: 
// Changes view only (no model rotations)
// ================================================================
GLvoid OpenGLForm::COpenGL::updateRotations(GLvoid){
	// Calculate change in mouse position
	int yDelta = MouseState.old_y - MouseState.y;
	int xDelta = MouseState.old_x - MouseState.x;

	// Rotate if right mouse button is down
	if(MouseState.rightButton && !MouseState.leftButton && !MouseState.middleButton)
	{
		g_xRotation -= xDelta * DEGREES_PER_PIXEL; // Scale values
		g_yRotation -= yDelta * DEGREES_PER_PIXEL;
	}
}

// ================================================================
// selectGL: 
// Handles picking (clicking on specific object)
// ================================================================
GLvoid OpenGLForm::COpenGL::selectGL(int x, int y)
{
	GLuint buffer[16] = {0};
 	GLint hits, view[4];
 		
	// Establish a buffer for selection mode values
	glSelectBuffer(16, buffer);

	// Get viewport
	glGetIntegerv(GL_VIEWPORT, view);

	// Switch to SELECT
	glRenderMode(GL_SELECT);

	// Clear names stack
	glInitNames();

	// Add one name (or error occurs)
	glPushName(0);

	// Switch to projection mode
	glMatrixMode(GL_PROJECTION);

 	glPushMatrix();

 		glLoadIdentity();
 
		// Draw area around cursor only
 		gluPickMatrix(x, y, 1.0, 1.0, view);
 		gluPerspective(60.0f,785.0f/528.0f,0.1f,1000.0f); // Same perspective as before
 
		// Draw objects onto screen
 		glMatrixMode(GL_MODELVIEW);
 
		// Draw objects in names buffer
 		SwapOpenGLBuffers();
 		DrawGLSceneSelect();
 
		// do pushmatrix in Projection mode
 		glMatrixMode(GL_PROJECTION);

 	glPopMatrix();

	// Gets number of elements drawn
	hits = glRenderMode(GL_RENDER);

	// Enter if statement if phalanx isn't already being manipulated (new click only)
	if (!FLAG_PHALANX_BUSY){
		list_hits(hits, buffer);} // Figure out what's being clicked

	// Update phalanx position
	update_rotation_phalanx();
 
	// Back to Modelview
 	glMatrixMode(GL_MODELVIEW);
	
	// Render scene
	DrawGLScene();
}

// ================================================================
// update_rotation_phalanx: 
// Update phalanx position during picking
// ================================================================
GLvoid OpenGLForm::COpenGL::update_rotation_phalanx()
{
	int yDelta = MouseState.old_y - MouseState.y;
	int xDelta = MouseState.old_x - MouseState.x;

	// Move object if left button is down
	if(MouseState.leftButton && !MouseState.rightButton && !MouseState.middleButton)
	{
		g_xViewRot = (float)(sqrt(pow((double)xDelta, 2) + pow((double)yDelta, 2)));
		if (xDelta < 0){g_xViewRot = -1.0f * g_xViewRot;}
	}
	
	// Update model directly
	updateAngle(MouseState.clicked_element, g_xViewRot);

	// Update form sliders
	update_sliders(MouseState.clicked_element);

}

// ================================================================
// list_hits: 
// Get element that was clicked
// Convert value to regular array index
// ================================================================
GLvoid OpenGLForm::COpenGL::list_hits(GLint hits, GLuint *names)
 {
 	/*
 		For each hit in the buffer are allocated 4 bytes:
 		1. Number of hits selected (always one,
 									beacuse when we draw each object
 									we use glLoadName, so we replace the
 									prevous name in the stack)
 		2. Min Z
 		3. Max Z
 		4. Name of the hit (glLoadName)
 	*/

	MouseState.clicked_element = (int)names[3] - 1;
}

// ================================================================
// update_sliders: 
// Update track bars on the form
// ================================================================
GLvoid OpenGLForm::COpenGL::update_sliders(GLint vertex)
{	
	f_one -> update_TrackBar(vertex);
}

// ================================================================
// update_model_angles: 
// Change model angles directly to (new_angle)
// ================================================================
GLvoid OpenGLForm::COpenGL::update_model_angles(GLint vertex, GLfloat new_angle)
{
	updateAngle(vertex, (new_angle - f_p[vertex].theta));
	//f_p[vertex].theta = new_angle;

}

