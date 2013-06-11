// ================================================================

// MAIN Header File

// Program written by Mila Gorobets
// Summer 2012
// University of Calgary
// http://milagorobets.com/handcontroller/control.php

// ================================================================

#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <vcclr.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Form1.h"
#include "calculations.h"
#include "serialcom.h"

#pragma comment (lib, "user32.lib")

// Include these to initialize their pointers
namespace GUI_1{ref class Form1;}
namespace OpenGLForm{ ref class COpenGL; }
namespace ModelSpace{ ref class Model ;}

using namespace GUI_1;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create new Form
	Form1 ^ mainform = gcnew Form1();

	// Create new OpenGL object
	OpenGLForm::COpenGL ^ open_gl = gcnew OpenGLForm::COpenGL();

	// Create a set of models for the hand
	ModelSpace::Model ^ pHand = gcnew ModelSpace::Model();
	ModelSpace::Model ^ p1Hand = gcnew ModelSpace::Model();
	ModelSpace::Model ^ p2Hand = gcnew ModelSpace::Model();
	ModelSpace::Model ^ p3Hand = gcnew ModelSpace::Model();
	
	// Link pointers together between objects (so that they can access each other)
	mainform -> o_gl = open_gl;	
	open_gl->f_one = mainform;
	open_gl->palmHand = pHand;
	open_gl->phalanx1Hand = p1Hand;
	open_gl->phalanx2Hand = p2Hand;
	open_gl->phalanx3Hand = p3Hand;

	// Initialize the OpenGL panel
	mainform -> o_gl -> COpenGL_one(785, 528);
	
	// Run application
	Application::Run(mainform);
	
	return 0;
}