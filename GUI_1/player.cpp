#include "stdafx.h"
#include "player.h"

namespace GUI_1
{
			player::player(){
			
			}

			void player::motion_timer(void*)
			{
				//timer3 -> Enabled = false;
			}
			void player::play_recording(void*)
			{
				// Acquire necessary pointers
				// Timer 4:
				/*
				System::Timers::Timer ^ wait_timer = returntimer4();
				StreamReader^ myStream;
				OpenFileDialog^ openFile = gcnew OpenFileDialog;
				openFile -> Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
				openFile -> FilterIndex = 2;
				openFile -> RestoreDirectory = true;
				openFile -> InitialDirectory = textBox1 -> Text;
				System::String^ temp;
				if ( openFile -> ShowDialog() == System::Windows::Forms::DialogResult::OK )
				{
					temp = openFile -> FileName;
					motion_file_name = gcnew array<wchar_t>(temp -> Length){L' '};
					motion_file_name = temp -> ToCharArray();

					if ( (myStream = gcnew StreamReader(gcnew String(motion_file_name))) != nullptr )
					{
						System::String^ data_read;
						System::String^ substring_data;
						int data_read_length;
						array<wchar_t>^ data_letters; 
						double val;

						// Check first line, must be "MOTION"
						data_read = myStream -> ReadLine();
						if (!String::Compare(data_read, "MOTION", StringComparison::Ordinal))
						{
							while (myStream -> Peek() >= 0) // Main file reading loop
							{
								data_read = myStream -> ReadLine();
								data_read_length = data_read -> Length;
								data_letters = gcnew array<wchar_t>(data_read -> Length){L' '};
								data_letters = data_read -> ToCharArray();
								// Check mode
								if (data_letters[0] == 'W') // Wait procedure
								{
									substring_data = data_read -> Substring(2, data_read_length - 2);
									val = System::Convert::ToDouble(substring_data);
									_beginthread(motion_timer, 0, NULL );
								}
								else if (data_letters[0] == 'n') // Position procedure
								{

								}
								else
								{
									return;
								}
							}
						}
						myStream->Close();
					}
				}*/
			}


}