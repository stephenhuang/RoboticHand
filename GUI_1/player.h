#ifndef H_PLAYER
#define H_PLAYER

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <process.h>

namespace GUI_1{ref class Form1;}

namespace GUI_1
{
	public ref class player{
		public:
			
			player();

			static GUI_1::Form1^ the_form;
			void motion_timer(void*);
			void play_recording(void*);

		private:

			
};
}
#endif