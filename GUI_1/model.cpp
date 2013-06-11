// ================================================================

// MODEL Source File

// ================================================================

#include "stdafx.h"
#include "Model.h"
#include <GL/GL.h>
#include <GL/GLU.h>

namespace ModelSpace
{

// ================================================================
// Model: 
// Creates instance of object (completely empty)
// ================================================================
Model::Model(){}

// ================================================================
// Model_init: 
// Initialize model. Make arrays, clear counts.
// ================================================================
void Model::Model_init()
{
	// Set counts to 0
	verticesCount = 0;
	triangleCount = 0;
    normalCount = 0;
	
	// Assign new space on heap for mesh element arrays
	this->triangles = gcnew array<Triangle>(MAX_POLYGONS);
	this->normals = gcnew array<Normal>(MAX_NORMALS);
	this->vertices = gcnew array<Vertex>(MAX_VERTICES);
}

// ================================================================
// ~Model: 
// Delete object
// ================================================================
Model::~Model(void)
{
}

// ================================================================
// loadModel: 
// Reads file and populates mesh arrays
// ================================================================
int Model::loadModel(char *mFilename)
{
	FILE *f;
	char buffer[256];
	
	// Open file
	if((f = fopen(mFilename, "r"))==NULL) return 0;

	// Read until end of file
	while(!feof(f))
	{
		memset(buffer,0,255);
		fgets(buffer, 256, f);

		// Read into proper arrays
		if( strncmp("vn ",buffer,3) == 0 )
		{
			sscanf((buffer+2),"%f%f%f",
							&(normals[normalCount].i),
							&(normals[normalCount].j),
							&(normals[normalCount].k));
			++normalCount;
		}
		else if(strncmp("v ",buffer,2) == 0 )
		{

			sscanf((buffer+1),"%f%f%f",
							&vertices[verticesCount].x,
							&vertices[verticesCount].y,
							&vertices[verticesCount].z);
			++verticesCount;
		}
		else if(strncmp("f ",buffer,2) == 0 )
		{
			sscanf((buffer+1),"%d//%d%d//%d%d//%d",
				&triangles[triangleCount].v0, &triangles[triangleCount].n0,
				&triangles[triangleCount].v1, &triangles[triangleCount].n1,
				&triangles[triangleCount].v2, &triangles[triangleCount].n2);
			++triangleCount;			
		}
	
	}
	fclose(f);
	return 1;
}

// ================================================================
// draw: 
// Draws object using vertex and normal data
// ================================================================
void Model::draw()
{
	// Set up light source
	const GLfloat lightfvarray[]= {0.5f,0.5f,0.5f,1.0f};
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightfvarray);

	glBegin(GL_TRIANGLES);
	for(int i = 0; i < triangleCount; i++)
	{
		// Vertex 1
		glNormal3f( normals[triangles[i].n0-1].i,
					normals[triangles[i].n0-1].j,
					normals[triangles[i].n0-1].k);
		glVertex3f( vertices[triangles[i].v0-1].x,
					vertices[triangles[i].v0-1].y,
					vertices[triangles[i].v0-1].z);

		// Vertex 2
		glNormal3f( normals[triangles[i].n1-1].i,
					normals[triangles[i].n1-1].j,
					normals[triangles[i].n1-1].k);
		glVertex3f( vertices[triangles[i].v1-1].x,
					vertices[triangles[i].v1-1].y,
					vertices[triangles[i].v1-1].z);

		// Vertex 3
		glNormal3f( normals[triangles[i].n2-1].i,
					normals[triangles[i].n2-1 ].j,
					normals[triangles[i].n2-1 ].k);
		glVertex3f( vertices[triangles[i].v2-1].x,
					vertices[triangles[i].v2-1].y,
					vertices[triangles[i].v2-1].z);
	}
	glEnd();
}

}