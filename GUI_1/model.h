// ================================================================

// MODEL Header File

// ================================================================

#ifndef H_MODEL
#define H_MODEL

#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_VERTICES 8000 // Max vertices read from a model file
#define MAX_POLYGONS 8000 // Max polygons read from a model file
#define MAX_NORMALS  8000 // Max normals read from a model file

// Structs for mesh elements
value struct Vertex{
	float x, y, z;
};
value struct Texcoor{
	float u, v;
};
value struct Normal{
	float i, j, k;
};
value struct Triangle{
	int n0, n1, n2;
	int v0, v1, v2;
};

namespace ModelSpace
{
public ref class Model
{
	public:
		// Default constructor 
		Model();

		// Model initializer
		void Model_init();

		// Destructor
		~Model(void);

		// Load the model from .obj mesh file
		int loadModel(char *mFilename);
		
		// Draw the model
		void draw();
		
	private:

		// Mesh element arrays
		array<Triangle>^ triangles;
		array<Normal>^ normals;
		array<Vertex>^ vertices;

		// Mesh element array counters
		int triangleCount; 
		int verticesCount;
		int normalCount;
		
};
}

#endif
