// ================================================================

// FORM1 Source File

// ================================================================


#include "stdafx.h"
#include <Windows.h>
#include "Form1.h"
#include "serialcom.h"
#include "calculations.h"

#pragma comment (lib, "user32.lib")

// Number of cycles to complete motion
int g_num_cycles;

// Max number of cycles
int g_most_cycles;

// Progress bar increments
double g_pb_1, g_pb_2, g_pb_3;

// Flag: 20 ms counter is done
bool FLAG_20MS_DONE;

// Flag: file reader is closed
bool FLAG_READER_CLOSED;

// Flag: update is in progress
bool FLAG_UPDATE_IN_PROGRESS;

namespace GUI_1{
	
	// ================================================================
	// Form1: 
	// Initialize form related variables and elements
	// ================================================================
	Form1::Form1(void)
	{
		InitializeComponent();

		// Initialize arrays
		this -> final_values = gcnew array<double>(9);
		this -> increments = gcnew array<double>(9);
		this -> angles_to_AVR = gcnew array<double>(9);
		this -> read_values = gcnew array<double>(18);
		
		// Flags for increment updates
		this -> FLAG_NEW_VALUES = FALSE;
		this -> flags_new_value = gcnew array<double>(9);

		// Disable timers 2 and 3
		this -> timer2 -> Enabled = false;
		this -> timer3 -> Enabled = false;
		// Timer 1 updates OpenGL continuously

		// Initialize individual speed track bars
		this -> tr11s -> Value = (int)(100);
		this -> lbl11s -> Text = "100%";
		this -> tr12s -> Value = (int)(100);
		this -> lbl12s -> Text = "100%";
		this -> tr13s -> Value = (int)(100);
		this -> lbl13s -> Text = "100%";
		this -> tr21s -> Value = (int)(100);
		this -> lbl21s -> Text = "100%";
		this -> tr22s -> Value = (int)(100);
		this -> lbl22s -> Text = "100%";
		this -> tr23s -> Value = (int)(100);
		this -> lbl23s -> Text = "100%";
		this -> tr31s -> Value = (int)(100);
		this -> lbl31s -> Text = "100%";
		this -> tr32s -> Value = (int)(100);
		this -> lbl32s -> Text = "100%";
		this -> tr33s -> Value = (int)(100);
		this -> lbl33s -> Text = "100%";

		// Initialize common speed track bars
		this -> trSpeed1 -> Value = (int)(100);
		this -> lblSpeed1 -> Text = "100%";
		this -> trSpeed2 -> Value = (int)(100);
		this -> lblSpeed2 -> Text = "100%";
		this -> trSpeed3 -> Value = (int)(100);
		this -> lblSpeed3 -> Text = "100%";

		// Speed check boxes are checked by default
		chk1s -> Checked = true;
		chk2s -> Checked = true;
		chk3s -> Checked = true;

		// COM port is COM1 by default
		g_com_channel = 0;
		cbComPort -> SelectedIndex = 0;

		// Communication baud rate is 19200 by default
		g_com_baud = 2;
		cbBaudRate -> SelectedIndex = 2;

		// Enable/Disable certain buttons
		button7 -> Enabled = true; button7 -> BackColor = System::Drawing::Color::LightSteelBlue;
		bPlayRecording -> Enabled = false; bPlayRecording -> BackColor = System::Drawing::Color::DarkOliveGreen;
		button3 -> Enabled = true; button3 -> BackColor = System::Drawing::Color::LightSteelBlue;
		btnSaveConfig -> Enabled = true; btnSaveConfig -> BackColor = System::Drawing::Color::LightSteelBlue;
		btnLoadConfig -> Enabled = true; btnLoadConfig -> BackColor = System::Drawing::Color::LightSteelBlue;

		// Angles to AVR by default are 90 degrees
		for (int i = 0; i < 9; i++)
		{
			angles_to_AVR[i] = 90.0f;
		}
	}

	// ================================================================
	// return_panel: 
	// Returns handle to OpenGL panel
	// ================================================================
	System::Windows::Forms::Panel ^ Form1::return_panel(){
		return this->panelgl;
	}

	// ================================================================
	// return_timer4: 
	// Returns handle to timer4
	// ================================================================
	System::Timers::Timer ^ Form1::return_timer4()
	{
		return timer4;
	}

	// ================================================================
	// update_TrackBar: 
	// Calls private update_TrackBars function
	// ================================================================
	void Form1::update_TrackBar(int vertex)
	{
		update_TrackBars(vertex);
	}

	// ================================================================
	// update_Hand: 
	// Update hand hardware
	// ================================================================
	int Form1::update_Hand(int source){

			double *data_angles = new double[9];

			// New serial communication instance
			SerialCommunication comm1;

			// Check source: 1 = GUI, 2 = Emergency Button
			// GUI
			if (source == 1){
				for (int i = 0; i < 9; i++)
				{
					data_angles[i] = angles_to_AVR[i];
				}

				unsigned int * data = _produce_counts_all(data_angles);
				data[18] = 'B';
				comm1.SerialWrite(data);

				delete[] data;
				delete[] data_angles;
			}
			// Emergency Button
			else if (source == 2){ 
				unsigned int * data = new unsigned int[19];
				for (int i = 0; i < 19; i++)
				{
					data[i] = 'R';
				}
				comm1.SerialWrite(data);

				delete[] data;
				delete[] data_angles;
			}
			return 1;
	}

	// ================================================================
	// read_file_function: 
	// Reads motion file and decides which function to call
	// ================================================================
	void Form1::read_file_function(){
		int func_to_call;
		System::String^ data_read;
		System::String^ substring_data;
		int data_read_length;
		array<wchar_t>^ data_letters;
		double val;

		// Check if file has ended
		if ((myStreamReader -> Peek() >= 0)&!FLAG_READER_CLOSED)
		{
			// Read next line
			data_read = myStreamReader -> ReadLine();
			data_read_length = data_read -> Length;
			data_letters = gcnew array<wchar_t>(data_read -> Length){L' '};
			data_letters = data_read -> ToCharArray();

			// Cancel both background workers
			bw -> CancelAsync();
			bw_motion -> CancelAsync();
			
			// Check if next command is for MOTION
			if (data_letters[0] == 'n')
			{
				// Find spaces in the string
				array<int>^ space_positions = gcnew array<int>(18);
				int space_c = 0;
				for (int i = 0; i < data_read_length; i++)
				{
					if (data_read[i] == ' ')
					{
						space_positions[space_c] = i;
						space_c ++;
					}
				}
				// Parse string into doubles
				// Phalanx 0
				System::String^  substring_data = data_read -> Substring(2, space_positions[1] - space_positions[0] - 1);
				read_values[0] = System::Convert::ToDouble(substring_data);
				this -> trFinger1Ph1 -> Value = (int)(read_values[0] * 10.0f);
				this -> lblFinger1Phalanx1 -> Text = ""+ read_values[0];
				
				substring_data = data_read -> Substring(space_positions[1] + 1, space_positions[2] - space_positions[1] - 1);
				read_values[9] = System::Convert::ToDouble(substring_data);
				this -> tr11s -> Value = (int)(read_values[9]);
				this -> lbl11s -> Text = ""+ read_values[9];

				// Phalanx 1
				substring_data = data_read -> Substring(space_positions[2] + 1, space_positions[3] - space_positions[2] - 1);
				read_values[1] = System::Convert::ToDouble(substring_data);
				this -> trFinger1Ph2 -> Value = (int)(read_values[1] * 10.0f);
				this -> lblFinger1Phalanx2 -> Text = ""+ read_values[1];

				substring_data = data_read -> Substring(space_positions[3] + 1, space_positions[4] - space_positions[3] - 1);
				read_values[10] = System::Convert::ToDouble(substring_data);
				this -> tr12s -> Value = (int)(read_values[10]);
				this -> lbl12s -> Text = ""+ read_values[10];

				// Phalanx 2
				substring_data = data_read -> Substring(space_positions[4] + 1, space_positions[5] - space_positions[4] - 1);
				read_values[2] = System::Convert::ToDouble(substring_data);
				this -> trFinger1Ph3 -> Value = (int)(read_values[2] * 10.0f);
				this -> lblFinger1Phalanx3 -> Text = ""+ read_values[2];

				substring_data = data_read -> Substring(space_positions[5] + 1, space_positions[6] - space_positions[5] - 1);
				read_values[11] = System::Convert::ToDouble(substring_data);
				this -> tr13s -> Value = (int)(read_values[11]);
				this -> lbl13s -> Text = ""+ read_values[11];
				
				// Phalanx 3
				substring_data = data_read -> Substring(space_positions[6] + 1, space_positions[7] - space_positions[6] - 1);
				read_values[3] = System::Convert::ToDouble(substring_data);
				this -> trFinger2Ph1 -> Value = (int)(read_values[3] * 10.0f);
				this -> lblFinger2Phalanx1 -> Text = ""+ read_values[3];

				substring_data = data_read -> Substring(space_positions[7] + 1, space_positions[8] - space_positions[7] - 1);
				read_values[12] = System::Convert::ToDouble(substring_data);
				this -> tr21s -> Value = (int)(read_values[12]);
				this -> lbl21s -> Text = ""+ read_values[12];

				// Phalanx 4
				substring_data = data_read -> Substring(space_positions[8] + 1, space_positions[9] - space_positions[8] - 1);
				read_values[4] = System::Convert::ToDouble(substring_data);
				this -> trFinger2Ph2 -> Value = (int)(read_values[4] * 10.0f);
				this -> lblFinger2Phalanx2 -> Text = ""+ read_values[4];

				substring_data = data_read -> Substring(space_positions[9] + 1, space_positions[10] - space_positions[9] - 1);
				read_values[13] = System::Convert::ToDouble(substring_data);
				this -> tr22s -> Value = (int)(read_values[13]);
				this -> lbl22s -> Text = ""+ read_values[13];

				// Phalanx 5
				substring_data = data_read -> Substring(space_positions[10] + 1, space_positions[11] - space_positions[10] - 1);
				read_values[5] = System::Convert::ToDouble(substring_data);
				this -> trFinger2Ph3 -> Value = (int)(read_values[5] * 10.0f);
				this -> lblFinger2Phalanx3 -> Text = ""+ read_values[5];

				substring_data = data_read -> Substring(space_positions[11] + 1, space_positions[12] - space_positions[11] - 1);
				read_values[14] = System::Convert::ToDouble(substring_data);
				this -> tr23s -> Value = (int)(read_values[14]);
				this -> lbl23s -> Text = ""+ read_values[14];

				// Phalanx 6
				substring_data = data_read -> Substring(space_positions[12] + 1, space_positions[13] - space_positions[12] - 1);
				read_values[6] = System::Convert::ToDouble(substring_data);
				this -> trFinger3Ph1 -> Value = (int)(read_values[6] * 10.0f);
				this -> lblFinger3Phalanx1 -> Text = ""+ read_values[6];

				substring_data = data_read -> Substring(space_positions[13] + 1, space_positions[14] - space_positions[13] - 1);
				read_values[15] = System::Convert::ToDouble(substring_data);
				this -> tr31s -> Value = (int)(read_values[15]);
				this -> lbl31s -> Text = ""+ read_values[15];

				// Phalanx 7
				substring_data = data_read -> Substring(space_positions[14] + 1, space_positions[15] - space_positions[14] - 1);
				read_values[7] = System::Convert::ToDouble(substring_data);
				this -> trFinger3Ph2 -> Value = (int)(read_values[7] * 10.0f);
				this -> lblFinger3Phalanx2 -> Text = ""+ read_values[7];

				substring_data = data_read -> Substring(space_positions[15] + 1, space_positions[16] - space_positions[15] - 1);
				read_values[16] = System::Convert::ToDouble(substring_data);
				this -> tr32s -> Value = (int)(read_values[16]);
				this -> lbl32s -> Text = ""+ read_values[16];

				// Phalanx 8
				substring_data = data_read -> Substring(space_positions[16] + 1, space_positions[17] - space_positions[16] - 1);
				read_values[8] = System::Convert::ToDouble(substring_data);
				this -> trFinger3Ph3 -> Value = (int)(read_values[8] * 10.0f);
				this -> lblFinger3Phalanx3 -> Text = ""+ read_values[8];

				substring_data = data_read -> Substring(space_positions[17] + 1, data_read_length - space_positions[17] - 1);
				read_values[17] = System::Convert::ToDouble(substring_data);
				this -> tr33s -> Value = (int)(read_values[17]);
				this -> lbl33s -> Text = ""+ read_values[17];
				
				// Call background worker for motion
				func_to_call = 1;
			}
			// Check if next action is for WAITING
			else if (data_letters[0] == 'W')
			{
				// Extract wait period (in ms)
				substring_data = data_read -> Substring(2, data_read_length - 2);
				val = System::Convert::ToDouble(substring_data);

				// Call background worker for pause
				func_to_call = 2;
			}
		}
		else 
		{
			// If stream over, close it
			myStreamReader -> Close();
			myStreamReader = gcnew StreamReader(gcnew String(motion_file_name));
			data_read = myStreamReader -> ReadLine();

			// Set closed flag to true, so it can be reopened without reloading
			FLAG_READER_CLOSED = true;
		}
		if (func_to_call == 1)
		{
			motion_config();
		}
		else if (func_to_call == 2)
		{
			motion_pause(val);
		}
		else
		{
			return;
		}
}

	// ================================================================
	// motion_config: 
	// Start bw_motion worker
	// ================================================================
	void Form1::motion_config()
	{	
		// Loop below copies angle values
		for (int i = 0; i < 9; i++)
		{
			final_values[i] = read_values[i];
			flags_new_value[i] = 1;
		}
		FLAG_NEW_VALUES = false;

		// Calculate increments for motion
		calc_motion_intervals();

		// Start thread
		bw_motion->RunWorkerAsync();
	}
	
	// ================================================================
	// motion_DoWork: 
	// Every 20 ms update angles until motion complete
	// ================================================================
	void Form1::motion_DoWork(System::Object^ sender, DoWorkEventArgs^ e)
	{
		// Make a new thread for timer
		TimerCallback^ tcb_1 = gcnew TimerCallback(this, &GUI_1::Form1::tmr_Tick);
		AutoResetEvent^ autoEvent = gcnew AutoResetEvent(false);
		tmr_1 = gcnew System::Threading::Timer(tcb_1, 0, 1000, 1000);

		while (1)
		{
			int flag_counter = 0;
			if (FLAG_NEW_VALUES)
			{
				for (int i = 0; i < 9; i++)
				{
					if (flags_new_value[i])
					{
						if (angles_to_AVR[i] == final_values[i]) // If desired and current angles equal
						{
							increments[i] = 0;
							flags_new_value[i] = 0;
							flag_counter ++;
						}
						else
						{
							if ((abs(angles_to_AVR[i]-final_values[i])) < (abs(increments[i]))) // If this is the last step
							{
								angles_to_AVR[i] = final_values[i];
								if (i < 3)
								{
									f_p[i].theta = final_values[i];
								}
								else if (i < 6)
								{
									f_p[i+1].theta = final_values[i];
								}
								else
								{
									f_p[i+2].theta = final_values[i];
								}
								increments[i] = 0;
								flags_new_value[i] = 0;
								flag_counter ++;
							}
							else // One or more steps remaining after this update
							{
								angles_to_AVR[i] += increments[i];
								if (i < 3)
								{
									f_p[i].theta = angles_to_AVR[i];
								}
								else if (i < 6)
								{
									f_p[i+1].theta = angles_to_AVR[i];
								}
								else
								{
									f_p[i+2].theta = angles_to_AVR[i];
								}
							}
						}
					}
					else
					{
						// If no update needed for phalanx, +1 to flag counter
						flag_counter ++;
					}
				}
			}

			// Wait for timer to count 20ms
			autoEvent->WaitOne(20, false);

			// Update hardware
			update_Hand(1);

			// If motion is complete
			if ((flag_counter >= 9)|(!FLAG_NEW_VALUES))
			{
				FLAG_NEW_VALUES = FALSE;

				// End background worker
				break;
			}
		}
	}

	// ================================================================
	// motion_RunWorkerCompleted: 
	// Read next line in file
	// ================================================================
	void Form1::motion_RunWorkerCompleted(System::Object^ sender, RunWorkerCompletedEventArgs^ e)
	{
		read_file_function();
	}

	// ================================================================
	// motion_ProgressChanged: 
	// Sends updates to main thread periodically (does nothing here)
	// ================================================================
	void Form1::motion_ProgressChanged(System::Object^ sender, ProgressChangedEventArgs^ e)
	{}

	// ================================================================
	// motion_pause: 
	// Start bw (pause) worker
	// ================================================================
	void Form1::motion_pause(int pause_duration)
	{
			bw->RunWorkerAsync(pause_duration); 
	}

	// ================================================================
	// bw_DoWork: 
	// Pause for set amount of time
	// ================================================================
	void Form1::bw_DoWork(System::Object^  sender, DoWorkEventArgs^ e )
	{
		// Extract pause duration
		int val = (int)e->Argument;
		int i = 0;

		// Create a timer to wait out the pause
		TimerCallback^ tcb = gcnew TimerCallback(this, &GUI_1::Form1::tmr_Tick);
		AutoResetEvent^ autoEvent     = gcnew AutoResetEvent(false);
		tmr = gcnew System::Threading::Timer(tcb, 0, 1000, 1000);

		// Wait until pause is complete
		autoEvent->WaitOne(val, false);
	}

	// ================================================================
	// bw_ProgressChanged: 
	// Sends updates to main thread periodically (does nothing here)
	// ================================================================
	void Form1::bw_ProgressChanged(System::Object^  sender , ProgressChangedEventArgs^ e )
	{}

	// ================================================================
	// bw_RunWorkerCompleted: 
	// Return to main thread - read next line in file
	// ================================================================
	void Form1::bw_RunWorkerCompleted(System::Object^  sender, RunWorkerCompletedEventArgs^ e )
	{
		read_file_function();
	}

	// ================================================================
	// tmr_Tick: 
	// Empty (but necessary) timer tick function for BW timers
	// ================================================================
	void Form1::tmr_Tick(System::Object^ sender){}

	// ================================================================
	// update_TrackBars: 
	// Put current angle values to track bars
	// ================================================================
	void Form1::update_TrackBars(int vertex)
	{		
		GLfloat dbtheta = f_p[vertex].theta;
			switch (vertex)
			{
			case 0: {
					this -> trFinger1Ph1 -> Value = (int)(dbtheta * 10.0f);
					this -> lblFinger1Phalanx1 -> Text = ""+ dbtheta;
					break;
					}
			case 1: {
					this -> trFinger1Ph2 -> Value = (int)(dbtheta * 10.0f);
					this -> lblFinger1Phalanx2 -> Text = ""+ dbtheta;
					break;
					}
			case 2: {
					this -> trFinger1Ph3 -> Value = (int)(dbtheta * 10.0f);
					this -> lblFinger1Phalanx3 -> Text = ""+ dbtheta;
					break;
					}
			case 4: {
					this -> trFinger2Ph1 -> Value = (int)(dbtheta * 10.0f);
					this -> lblFinger2Phalanx1 -> Text = ""+ dbtheta;
					break;
					}
			case 5: {
					this -> trFinger2Ph2 -> Value = (int)(dbtheta * 10.0f);
					this -> lblFinger2Phalanx2 -> Text = ""+ dbtheta;
					break;
					}
			case 6: {
					this -> trFinger2Ph3 -> Value = (int)(dbtheta * 10.0f);
					this -> lblFinger2Phalanx3 -> Text = ""+ dbtheta;
					break;
					}
			case 8: {
					this -> trFinger3Ph1 -> Value = (int)(dbtheta * 10.0f);
					this -> lblFinger3Phalanx1 -> Text = ""+ dbtheta;
					break;
					}
			case 9: {
					this -> trFinger3Ph2 -> Value = (int)(dbtheta * 10.0f);
					this -> lblFinger3Phalanx2 -> Text = ""+ dbtheta;
					break;
					}
			case 10: {
					this -> trFinger3Ph3 -> Value = (int)(dbtheta * 10.0f);
					this -> lblFinger3Phalanx3 -> Text = ""+ dbtheta;
					break;
					}
			default: break;
			}
	}

	// ================================================================
	// reset_Hand: 
	// Resets all degrees to 90 degrees. No effect on speed
	// ================================================================
	void Form1::reset_Hand(){

			// Reset track bars to 90 degrees
			trFinger1Ph1 -> Value = 900;
			trFinger1Ph2 -> Value = 900;
			trFinger1Ph3 -> Value = 900;
			trFinger2Ph1 -> Value = 900;
			trFinger2Ph2 -> Value = 900;
			trFinger2Ph3 -> Value = 900;
			trFinger3Ph1 -> Value = 900;
			trFinger3Ph2 -> Value = 900;
			trFinger3Ph3 -> Value = 900;

			// Reset labels for track bars to 90 degrees
			this -> lblFinger1Phalanx1 -> Text = "90.0";
			this -> lblFinger1Phalanx2 -> Text = "90.0";
			this -> lblFinger1Phalanx3 -> Text = "90.0";
			this -> lblFinger2Phalanx1 -> Text = "90.0";
			this -> lblFinger2Phalanx2 -> Text = "90.0";
			this -> lblFinger2Phalanx3 -> Text = "90.0";
			this -> lblFinger3Phalanx1 -> Text = "90.0";
			this -> lblFinger3Phalanx2 -> Text = "90.0";
			this -> lblFinger3Phalanx3 -> Text = "90.0";

			// Update model angles
			for (int m = 0; m < 11; m++)
			{
				o_gl -> update_model_angles(m, 90.0f);
			}

			// Set angles to AVR to 90 degrees
			for (int i = 0; i < 9; i++)
			{
				angles_to_AVR[i] = 90.0f;
			}
			
			// Send values to hardware
			int i = update_Hand(1);
	}

	// ================================================================
	// calc_motion_intervals: 
	// Calculate intervals for motion based on angles and speed
	// ================================================================
	void Form1::calc_motion_intervals()
	{
			g_most_cycles = 0;
			int n = 0;
			for (n = 0; n < 3; n ++)
			{
					increments[n] = calculate_servo_intervals(read_values[n+9], (final_values[n] - (GLfloat)angles_to_AVR[n]));
					if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}
			}
			g_pb_1 = 100000.0f / g_most_cycles;
			if (g_most_cycles!=0){this -> timer4 -> Enabled = true; pbarMF1 -> Value = 0; FLAG_NEW_VALUES = true;}
		
			g_most_cycles = 0;
			for (int n = 3; n < 6; n ++)
			{
					increments[n] = calculate_servo_intervals(read_values[n+9], (final_values[n] - (GLfloat)angles_to_AVR[n]));
					if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}
			}
			g_pb_2 = 100000.0f / g_most_cycles;
			if (g_most_cycles!=0){this -> timer4 -> Enabled = true; pbarMF2 -> Value = 0; FLAG_NEW_VALUES = true;}

			g_most_cycles = 0;
			for (int n = 6; n < 9; n ++)
			{
					increments[n] = calculate_servo_intervals(read_values[n+9], (final_values[n] - (GLfloat)angles_to_AVR[n]));
					if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}
			}
			g_pb_3 = 100000.0f / g_most_cycles;
			if (g_most_cycles!=0){this -> timer4 -> Enabled = true; pbarMF3 -> Value = 0; FLAG_NEW_VALUES = true;}
	}

	// ================================================================
	// calculate_servo_intervals: 
	// Calculate increments for angles to achieve desired speed
	// ================================================================
	double Form1::calculate_servo_intervals(GLfloat speed, GLfloat angle)
	{
		double pulse_width = angle * 1000.0f / 180.0f; // Pulse width in us
		double time_for_action_hundred = abs(pulse_width) / 10.0f;
		double time_for_action_specified = time_for_action_hundred / (speed / 100.0f);
		g_num_cycles = (int)ceil(time_for_action_specified / 20.0f);

		double increment = pulse_width / g_num_cycles;
		increment = increment * 180.0f / 1000.0f;
		return increment;
	}

	// ================================================================
	// intervals_set1:
	// Responsible for calculating increments for motion of Finger 1
	// ================================================================
	void Form1::intervals_set1()
	{
		FLAG_NEW_VALUES = TRUE;
		if (chk1s -> Checked) // Use one speed for all
		{
			GLfloat val = (GLfloat)(trFinger1Ph1 -> Value)/10;
			GLfloat speed = (GLfloat)(trSpeed1 -> Value);
			increments[0] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[0]));
			g_most_cycles = g_num_cycles;
			
			val = (GLfloat)(trFinger1Ph2 -> Value)/10;
			speed = (GLfloat)(trSpeed1 -> Value);
			increments[1] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[1]));
			if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}

			val = (GLfloat)(trFinger1Ph3 -> Value)/10;
			speed = (GLfloat)(trSpeed1 -> Value);
			increments[2] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[2]));
			if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}
		}
		else // Use individual speeds
		{
			GLfloat val = (GLfloat)(trFinger1Ph1 -> Value)/10;
			GLfloat speed = (GLfloat)(tr11s -> Value);
			increments[0] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[0]));
			g_most_cycles = g_num_cycles;
			
			val = (GLfloat)(trFinger1Ph2 -> Value)/10;
			speed = (GLfloat)(tr12s -> Value);
			increments[1] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[1]));
			if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}

			val = (GLfloat)(trFinger1Ph3 -> Value)/10;
			speed = (GLfloat)(tr13s -> Value);
			increments[2] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[2]));
			if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}
		}
		g_pb_1 = 100000.0f / g_most_cycles;
		pbarMF1 -> Value = 0;
		if (g_most_cycles!=0){this -> timer3 -> Enabled = true;}		 
	}

	// ================================================================
	// intervals_set1:
	// Responsible for calculating increments for motion of Finger 2
	// ================================================================
	void Form1::intervals_set2()
	{
		FLAG_NEW_VALUES = TRUE;
		if (chk2s -> Checked) // Use one speed for all
		{
			GLfloat val = (GLfloat)(trFinger2Ph1 -> Value)/10;
			GLfloat speed = (GLfloat)(trSpeed2 -> Value);
			increments[3] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[3]));
			g_most_cycles = g_num_cycles;

			val = (GLfloat)(trFinger2Ph2 -> Value)/10;
			speed = (GLfloat)(trSpeed2 -> Value);
			increments[4] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[4]));
			if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}

			val = (GLfloat)(trFinger2Ph3 -> Value)/10;
			speed = (GLfloat)(trSpeed2 -> Value);
			increments[5] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[5]));
			if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}
		}
		else // Use individual speeds
		{
			GLfloat val = (GLfloat)(trFinger2Ph1 -> Value)/10;
			GLfloat speed = (GLfloat)(tr21s -> Value);
			increments[3] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[3]));
			g_most_cycles = g_num_cycles;
			
			val = (GLfloat)(trFinger2Ph2 -> Value)/10;
			speed = (GLfloat)(tr22s -> Value);
			increments[4] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[4]));
			if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}

			val = (GLfloat)(trFinger2Ph3 -> Value)/10;
			speed = (GLfloat)(tr23s -> Value);
			increments[5] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[5]));
			if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}
		}
		g_pb_2 = 100000.0f / g_most_cycles;
		pbarMF2 -> Value = 0;
		if (g_most_cycles!=0){this -> timer3 -> Enabled = true;}
	}

	// ================================================================
	// intervals_set1:
	// Responsible for calculating increments for motion of Finger 3
	// ================================================================
	void Form1::intervals_set3()
	{
		FLAG_NEW_VALUES = TRUE;
		if (chk3s -> Checked) // Use one speed for all
		{
			GLfloat val = (GLfloat)(trFinger3Ph1 -> Value)/10;
			GLfloat speed = (GLfloat)(trSpeed3 -> Value);
			increments[6] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[6]));
			g_most_cycles = g_num_cycles;
			
			val = (GLfloat)(trFinger3Ph2 -> Value)/10;
			speed = (GLfloat)(trSpeed3 -> Value);
			increments[7] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[7]));
			if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}

			val = (GLfloat)(trFinger3Ph3 -> Value)/10;
			speed = (GLfloat)(trSpeed3 -> Value);
			increments[8] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[8]));
			if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}
		}
		else // Use individual speeds
		{
			GLfloat val = (GLfloat)(trFinger3Ph1 -> Value)/10;
			GLfloat speed = (GLfloat)(tr31s -> Value);
			increments[6] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[6]));
			g_most_cycles = g_num_cycles;
			
			val = (GLfloat)(trFinger3Ph2 -> Value)/10;
			speed = (GLfloat)(tr32s -> Value);
			increments[7] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[7]));
			if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}

			val = (GLfloat)(trFinger3Ph3 -> Value)/10;
			speed = (GLfloat)(tr33s -> Value);
			increments[8] = calculate_servo_intervals(speed, (val - (GLfloat)angles_to_AVR[8]));
			if (g_most_cycles < g_num_cycles){g_most_cycles = g_num_cycles;}
		}
		g_pb_3 = 100000.0f / g_most_cycles;
		pbarMF3 -> Value = 0;
		if (g_most_cycles!=0){this -> timer3 -> Enabled = true;} 
	}
	void Form1::update_progress_bars(){
			if ((int)(pbarMF1 -> Value + g_pb_1) > 100000.0f ){ pbarMF1 -> Value = 100000;}
			else {pbarMF1 -> Value = pbarMF1 -> Value + (int)g_pb_1;}
			if ((int)(pbarMF2 -> Value + g_pb_2) > 100000.0f ){ pbarMF2 -> Value = 100000;}
			else {pbarMF2 -> Value = pbarMF2 -> Value + (int)g_pb_2;}
			if ((int)(pbarMF3 -> Value + g_pb_3) > 100000.0f ){ pbarMF3 -> Value = 100000;}
			else {pbarMF3 -> Value = pbarMF3 -> Value + (int)g_pb_3;}	
	}
}
