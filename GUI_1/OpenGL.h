// ================================================================

// OPENGL Header File

// ================================================================

#ifndef H_OPENGL
#define H_OPENGL

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#pragma comment (lib, "user32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")


// Declare globals

#ifndef M_PI // Pi
#define M_PI  3.14159265358979323846f
#endif

// Degrees per pixel conversion for motion
#define DEGREES_PER_PIXEL 0.6f

// Temporary angle for functions
extern GLfloat angle;

// Point struct used for hand vertices
struct c_p_v{
		GLfloat n_x;
		GLfloat n_y;
		GLfloat n_z;
		GLfloat x;
		GLfloat y;
		GLfloat z;
		GLfloat theta;
};

// Struct for control of mouse clicks and motion
struct g_mouseState{
	bool leftButton;
	bool rightButton;
	bool middleButton;
	int x;
	int y;
	int old_x;
	int old_y;
	int clicked_element;
};

// Create 12 vertices for the entire hand
extern c_p_v f_p[12]; 

// Temporary vertex (useful in calculations)
extern c_p_v temp;

// Flag set when user manipulates phalanx
extern bool FLAG_PHALANX_BUSY;

// Create struct to hold mouse click and motion information
extern g_mouseState  MouseState;

// Rotation degree values
extern float g_xRotation, g_yRotation, g_xViewRot;

static float eyex, eyey, eyez;  // eye x,y,z values for gluLookAt (location of eye)
static float focusx, focusy, focusz; // the point the eye is looking at

// Forward declaration of classes
namespace GUI_1{ref class Form1;}
namespace ModelSpace{ref class Model;}
	
namespace OpenGLForm 
{
	using namespace System::Windows::Forms;

	public ref class COpenGL: public System::Windows::Forms::NativeWindow
	{
	public:

		static GUI_1::Form1^ f_one; // Pointer to the form

		// Pointers to meshes for hand parts
		static ModelSpace::Model^ palmHand;
		static ModelSpace::Model^ phalanx1Hand; // Proximal phalanx: Only one instance needed!
		static ModelSpace::Model^ phalanx2Hand; // Intermediate phalanx: Only one instance needed!
		static ModelSpace::Model^ phalanx3Hand; // Distal phalanx: Only one instance needed!
		
		// Empty constructor
		COpenGL();

		// Second constructor: panel width and height <-- This is used
		int COpenGL_one(GLsizei iWidth, GLsizei iHeight);
		
		// ================================================================ 
		// MATHEMATICAL FUNCTIONS (not all are used right now)
		// ================================================================
		
		// Determinant of a matrix
		GLfloat dt(GLfloat a, GLfloat b, GLfloat c, GLfloat d);

		// Rotates point at (a,b,c) around vector (u,v,w) that goes through point (x,y,z) through (angle)
		void rotatePointAboutLine(GLfloat a, GLfloat b, GLfloat c, GLfloat u, GLfloat v, GLfloat w, GLfloat x, GLfloat y, GLfloat z, GLfloat angle);

		// Dot product of two vectors
		GLfloat dotProduct(c_p_v a, c_p_v b);

		// Finds orthogal axis to the two vectors at vertex (v)
		void findOrthogonalAxis(int v);

		// Change angle between two vectors at (vertex) by (angle)
		void spinAroundPoint(int vertex, GLfloat angle);

		// Change current angle at (vertex) by (angle)
		GLfloat addAngle(int vertex, GLfloat angle);

		// Change current angle at (vertex) by (angle)
		void updateAngle(int vertex, GLfloat angle);
	

		// ================================================================
		// RENDERING STUFF
		// ================================================================

		// Draw OpenGL objects
		int DrawGLScene(void);

		// Four objects to draw
		void DrawPalm(void);
		void DrawFinger1(void);
		void DrawFinger2(void);
		void DrawFinger3(void);

		// Draw OpenGL objects for picking purposes
		int DrawGLSceneSelect(void);

		// Exchange front and back buffers
		void SwapOpenGLBuffers(void);

		// Kill OpenGL window
		GLvoid KILLGLWindow(GLvoid);

		// Controls view rotation
		GLvoid updateRotations(GLvoid);

		// Controls picking
		GLvoid selectGL(int x, int y);

		// Figure out what object was clicked (by name stack value)
		GLvoid list_hits(GLint hits, GLuint *names);

		// Controls object rotation
		GLvoid update_rotation_phalanx();

		// Update sliders on the form to user changes
		GLvoid update_sliders(GLint vertex);

		// Update model's (vertex) theta value to (new_angle)
		GLvoid update_model_angles(GLint vertex, GLfloat new_angle);

	private:

		// Handles for OpenGL panel
		HDC m_hDC;
		HGLRC m_hglrc;

	protected:

		// Destructor
		~COpenGL(System::Void)
		{
			this->DestroyHandle();
		}

		// Pretty straight forward
		GLint MySetPixelFormat(HDC hdc);

		// Initialize view
		bool InitGL(GLvoid);

		// Resize and initialize the OpenGL panel
		GLvoid ReSizeGLScene(GLsizei width, GLsizei height);	

};
}
#endif
