#ifndef common
#define common

#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <vcclr.h>
#include <stdio.h>
#include <stdlib.h>

#include "Form1.h"
#include "calculations.h"
#include "serialcom.h"

namespace form_pointer{

	using namespace GUI_1;

	ref class Form1;
	ref class COpenGL;
	
	public ref class form_pt {
		public:
			GUI_1::Form1 ^ form1;
			OpenGLForm::COpenGL ^ o_gl;
			static GUI_1::Form1 ^ frm;
		};
}

#endif