// ================================================================

// FORM1 Header File

// ================================================================

#ifndef H_FORM1
#define H_FORM1

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

#include "OpenGL.h"
#include "model.h"
#include <Windows.h>
#include <iostream>
#include <process.h>

// COM Port on the computer
extern int g_com_channel;

// Communication baud rate
extern int g_com_baud;

// Number of cycles to complete motion
extern int g_num_cycles;

// Max number of cycles
extern int g_most_cycles;

// Progress bar increments
extern double g_pb_1, g_pb_2, g_pb_3;

// Flag: 20 ms counter is done
extern bool FLAG_20MS_DONE;

// Flag: file reader is closed
extern bool FLAG_READER_CLOSED;

// Flag: update is in progress
extern bool FLAG_UPDATE_IN_PROGRESS;


namespace GUI_1 {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	void play_recording(void*);
	void motion_timer(void*);
	/// <summary>
	/// Summary for Form1
	/// </summary>

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:

		// Constructor
		Form1(void);

		// Flag: new position values are available (update)
		bool FLAG_NEW_VALUES;
		
		// Pointer to OpenGL object
		static OpenGLForm::COpenGL^ o_gl;

		// Background worker 1 (pause)
		BackgroundWorker ^ bw;

		// Background worker 2 (20 ms timer)
		BackgroundWorker ^ bw_timer;

		// Background worker 3 (motion)
		BackgroundWorker ^ bw_motion;

		// Thread timers
		System::Threading::Timer ^ tmr;
		System::Threading::Timer ^ tmr_1;

		// StreamReader (needs to be global)
		StreamReader^ myStreamReader;

		// File name for motion recording
		static array<wchar_t>^ motion_file_name;
		
		// Returns OpenGL panel handle
		System::Windows::Forms::Panel ^ Form1::return_panel();

		// Return timer4 handle
		System::Timers::Timer ^ Form1::return_timer4();

		// Pointers to arrays
		array<double>^ final_values;
		array<double>^ read_values;
		array<double>^ increments;
		array<double>^ angles_to_AVR;
		array<double>^ flags_new_value;

		// Update track bar function
		void update_TrackBar(int);

	// ================================================================
	// FORM ELEMENTS
	// ================================================================
	private: System::Windows::Forms::Label^  lblRecLoaded;
	private: System::Timers::Timer^  timer3;
	private: System::Timers::Timer^  timer4;
	private: System::Windows::Forms::CheckBox^  chk1s;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  lbl13s;
	private: System::Windows::Forms::Label^  lbl12s;
	private: System::Windows::Forms::TrackBar^  tr12s;
	private: System::Windows::Forms::TrackBar^  tr13s;
	private: System::Windows::Forms::Label^  lbl11s;
	private: System::Windows::Forms::TrackBar^  tr11s;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::CheckBox^  chk2s;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::Label^  lbl23s;
	private: System::Windows::Forms::Label^  lbl22s;
	private: System::Windows::Forms::TrackBar^  tr22s;
	private: System::Windows::Forms::TrackBar^  tr23s;
	private: System::Windows::Forms::Label^  lbl21s;
	private: System::Windows::Forms::TrackBar^  tr21s;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::Label^  lblFinger2Phalanx3;
	private: System::Windows::Forms::Label^  lblFinger2Phalanx2;
	private: System::Windows::Forms::TrackBar^  trFinger2Ph2;
	private: System::Windows::Forms::TrackBar^  trFinger2Ph3;
	private: System::Windows::Forms::Label^  lblFinger2Phalanx1;
	private: System::Windows::Forms::TrackBar^  trFinger2Ph1;
	private: System::Windows::Forms::CheckBox^  chk3s;
	private: System::Windows::Forms::GroupBox^  groupBox9;
	private: System::Windows::Forms::Label^  lbl33s;
	private: System::Windows::Forms::Label^  lbl32s;
	private: System::Windows::Forms::TrackBar^  tr32s;
	private: System::Windows::Forms::TrackBar^  tr33s;
	private: System::Windows::Forms::Label^  lbl31s;
	private: System::Windows::Forms::TrackBar^  tr31s;
	private: System::Windows::Forms::GroupBox^  groupBox10;
	private: System::Windows::Forms::Label^  lblFinger3Phalanx3;
	private: System::Windows::Forms::Label^  lblFinger3Phalanx2;
	private: System::Windows::Forms::TrackBar^  trFinger3Ph2;
	private: System::Windows::Forms::TrackBar^  trFinger3Ph3;
	private: System::Windows::Forms::Label^  lblFinger3Phalanx1;
	private: System::Windows::Forms::TrackBar^  trFinger3Ph1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveConfigurationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openConfigurationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem1;
	private: System::Windows::Forms::GroupBox^  groupBox12;
	private: System::Windows::Forms::GroupBox^  groupBox11;
	private: System::Windows::Forms::Button^  btnSaveConfig;
	private: System::Windows::Forms::Button^  btnLoadConfig;
	private: System::Windows::Forms::FolderBrowserDialog^  browDialog;
	private: System::Windows::Forms::Label^  label34;
	private: System::Windows::Forms::TextBox^  txtPathMotion;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Label^  lblEndRec;
	private: System::Windows::Forms::Label^  lblAddConfig;
	private: System::Windows::Forms::Label^  lblAddPause;
	private: System::Windows::Forms::Label^  lblBeginRec;
	private: System::Windows::Forms::Button^  bEndRec;
	private: System::Windows::Forms::Button^  bAddConfig;
	private: System::Windows::Forms::Button^  bAddPause;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::TextBox^  txtPause;
	private: System::Windows::Forms::Label^  label33;
	private: System::Windows::Forms::TextBox^  txtPathConfig;
	private: System::Windows::Forms::Label^  lblLoadConfig;
	private: System::Windows::Forms::Label^  lblSaveConfig;
	private: System::Windows::Forms::SaveFileDialog^  saveFile;
	private: System::Windows::Forms::OpenFileDialog^  openFile;
	private: System::Windows::Forms::Button^  bPlayRecording;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::GroupBox^  gFinger1;
	private: System::Windows::Forms::ProgressBar^  pbarMF1;
	private: System::Windows::Forms::Button^  bStartMF1;
	private: System::Windows::Forms::GroupBox^  gReqF1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  lF1p3req;
	private: System::Windows::Forms::Label^  lF1p2req;
	private: System::Windows::Forms::Label^  lF1p1req;
	private: System::Windows::Forms::TrackBar^  trFinger1Ph3;
	private: System::Windows::Forms::TrackBar^  trFinger1Ph2;
	private: System::Windows::Forms::TrackBar^  trFinger1Ph1;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  lblFinger1Phalanx3;
	private: System::Windows::Forms::Label^  lblFinger1Phalanx2;
	private: System::Windows::Forms::Label^  lblFinger1Phalanx1;
	private: System::Windows::Forms::Button^  bEmergencyStop;
	private: System::Windows::Forms::Button^  bReset;
	private: System::Windows::Forms::Button^  bStartAll;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  lblSpeed3;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TrackBar^  trSpeed3;
	private: System::Windows::Forms::ProgressBar^  pbarMF3;
	private: System::Windows::Forms::Button^  bStartMF3;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::GroupBox^  groupBox7;
	private: System::Windows::Forms::Label^  lblSpeed2;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::TrackBar^  trSpeed2;
	private: System::Windows::Forms::ProgressBar^  pbarMF2;
	private: System::Windows::Forms::Button^  bStartMF2;
	private: System::Windows::Forms::GroupBox^  groupBox8;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::Label^  label30;
	private: System::Windows::Forms::Label^  lblSpeed1;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::TrackBar^  trSpeed1;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Label^  label15;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Panel^  panelgl;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Timer^  timer2;
	private: System::Windows::Forms::ComboBox^  cbBaudRate;
	private: System::Windows::Forms::ComboBox^  cbComPort;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		// Destructor
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
		
// ================================================================
// FORM ELEMENTS INITIALIZATION
// ================================================================
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->groupBox12 = (gcnew System::Windows::Forms::GroupBox());
			this->lblRecLoaded = (gcnew System::Windows::Forms::Label());
			this->bPlayRecording = (gcnew System::Windows::Forms::Button());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->txtPathMotion = (gcnew System::Windows::Forms::TextBox());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->lblEndRec = (gcnew System::Windows::Forms::Label());
			this->lblAddConfig = (gcnew System::Windows::Forms::Label());
			this->lblAddPause = (gcnew System::Windows::Forms::Label());
			this->lblBeginRec = (gcnew System::Windows::Forms::Label());
			this->bEndRec = (gcnew System::Windows::Forms::Button());
			this->bAddConfig = (gcnew System::Windows::Forms::Button());
			this->bAddPause = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->txtPause = (gcnew System::Windows::Forms::TextBox());
			this->groupBox11 = (gcnew System::Windows::Forms::GroupBox());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->txtPathConfig = (gcnew System::Windows::Forms::TextBox());
			this->lblLoadConfig = (gcnew System::Windows::Forms::Label());
			this->lblSaveConfig = (gcnew System::Windows::Forms::Label());
			this->btnSaveConfig = (gcnew System::Windows::Forms::Button());
			this->btnLoadConfig = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->bEmergencyStop = (gcnew System::Windows::Forms::Button());
			this->bReset = (gcnew System::Windows::Forms::Button());
			this->bStartAll = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->chk3s = (gcnew System::Windows::Forms::CheckBox());
			this->lblSpeed3 = (gcnew System::Windows::Forms::Label());
			this->pbarMF3 = (gcnew System::Windows::Forms::ProgressBar());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->trSpeed3 = (gcnew System::Windows::Forms::TrackBar());
			this->bStartMF3 = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl33s = (gcnew System::Windows::Forms::Label());
			this->lbl32s = (gcnew System::Windows::Forms::Label());
			this->tr32s = (gcnew System::Windows::Forms::TrackBar());
			this->tr33s = (gcnew System::Windows::Forms::TrackBar());
			this->lbl31s = (gcnew System::Windows::Forms::Label());
			this->tr31s = (gcnew System::Windows::Forms::TrackBar());
			this->groupBox10 = (gcnew System::Windows::Forms::GroupBox());
			this->lblFinger3Phalanx3 = (gcnew System::Windows::Forms::Label());
			this->lblFinger3Phalanx2 = (gcnew System::Windows::Forms::Label());
			this->trFinger3Ph2 = (gcnew System::Windows::Forms::TrackBar());
			this->trFinger3Ph3 = (gcnew System::Windows::Forms::TrackBar());
			this->lblFinger3Phalanx1 = (gcnew System::Windows::Forms::Label());
			this->trFinger3Ph1 = (gcnew System::Windows::Forms::TrackBar());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->chk2s = (gcnew System::Windows::Forms::CheckBox());
			this->lblSpeed2 = (gcnew System::Windows::Forms::Label());
			this->trSpeed2 = (gcnew System::Windows::Forms::TrackBar());
			this->pbarMF2 = (gcnew System::Windows::Forms::ProgressBar());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->bStartMF2 = (gcnew System::Windows::Forms::Button());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl23s = (gcnew System::Windows::Forms::Label());
			this->lbl22s = (gcnew System::Windows::Forms::Label());
			this->tr22s = (gcnew System::Windows::Forms::TrackBar());
			this->tr23s = (gcnew System::Windows::Forms::TrackBar());
			this->lbl21s = (gcnew System::Windows::Forms::Label());
			this->tr21s = (gcnew System::Windows::Forms::TrackBar());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->lblFinger2Phalanx3 = (gcnew System::Windows::Forms::Label());
			this->lblFinger2Phalanx2 = (gcnew System::Windows::Forms::Label());
			this->trFinger2Ph2 = (gcnew System::Windows::Forms::TrackBar());
			this->trFinger2Ph3 = (gcnew System::Windows::Forms::TrackBar());
			this->lblFinger2Phalanx1 = (gcnew System::Windows::Forms::Label());
			this->trFinger2Ph1 = (gcnew System::Windows::Forms::TrackBar());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->gFinger1 = (gcnew System::Windows::Forms::GroupBox());
			this->chk1s = (gcnew System::Windows::Forms::CheckBox());
			this->lblSpeed1 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->trSpeed1 = (gcnew System::Windows::Forms::TrackBar());
			this->pbarMF1 = (gcnew System::Windows::Forms::ProgressBar());
			this->bStartMF1 = (gcnew System::Windows::Forms::Button());
			this->gReqF1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl13s = (gcnew System::Windows::Forms::Label());
			this->lbl12s = (gcnew System::Windows::Forms::Label());
			this->tr12s = (gcnew System::Windows::Forms::TrackBar());
			this->tr13s = (gcnew System::Windows::Forms::TrackBar());
			this->lbl11s = (gcnew System::Windows::Forms::Label());
			this->tr11s = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->lblFinger1Phalanx3 = (gcnew System::Windows::Forms::Label());
			this->lblFinger1Phalanx2 = (gcnew System::Windows::Forms::Label());
			this->trFinger1Ph2 = (gcnew System::Windows::Forms::TrackBar());
			this->trFinger1Ph3 = (gcnew System::Windows::Forms::TrackBar());
			this->lblFinger1Phalanx1 = (gcnew System::Windows::Forms::Label());
			this->trFinger1Ph1 = (gcnew System::Windows::Forms::TrackBar());
			this->lF1p3req = (gcnew System::Windows::Forms::Label());
			this->lF1p2req = (gcnew System::Windows::Forms::Label());
			this->lF1p1req = (gcnew System::Windows::Forms::Label());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->cbBaudRate = (gcnew System::Windows::Forms::ComboBox());
			this->cbComPort = (gcnew System::Windows::Forms::ComboBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panelgl = (gcnew System::Windows::Forms::Panel());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer3 = (gcnew System::Timers::Timer());
			this->timer4 = (gcnew System::Timers::Timer());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveConfigurationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openConfigurationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->browDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->saveFile = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->panel1->SuspendLayout();
			this->groupBox12->SuspendLayout();
			this->groupBox11->SuspendLayout();
			this->panel2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trSpeed3))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->groupBox9->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr32s))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr33s))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr31s))->BeginInit();
			this->groupBox10->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger3Ph2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger3Ph3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger3Ph1))->BeginInit();
			this->groupBox7->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trSpeed2))->BeginInit();
			this->groupBox8->SuspendLayout();
			this->groupBox5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr22s))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr23s))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr21s))->BeginInit();
			this->groupBox6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger2Ph2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger2Ph3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger2Ph1))->BeginInit();
			this->gFinger1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trSpeed1))->BeginInit();
			this->gReqF1->SuspendLayout();
			this->groupBox4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr12s))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr13s))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr11s))->BeginInit();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger1Ph2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger1Ph3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger1Ph1))->BeginInit();
			this->panel3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->timer3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->timer4))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->panel1->Controls->Add(this->groupBox12);
			this->panel1->Controls->Add(this->groupBox11);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label14);
			this->panel1->Location = System::Drawing::Point(12, 650);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(785, 276);
			this->panel1->TabIndex = 1;
			// 
			// groupBox12
			// 
			this->groupBox12->Controls->Add(this->lblRecLoaded);
			this->groupBox12->Controls->Add(this->bPlayRecording);
			this->groupBox12->Controls->Add(this->label34);
			this->groupBox12->Controls->Add(this->txtPathMotion);
			this->groupBox12->Controls->Add(this->button7);
			this->groupBox12->Controls->Add(this->lblEndRec);
			this->groupBox12->Controls->Add(this->lblAddConfig);
			this->groupBox12->Controls->Add(this->lblAddPause);
			this->groupBox12->Controls->Add(this->lblBeginRec);
			this->groupBox12->Controls->Add(this->bEndRec);
			this->groupBox12->Controls->Add(this->bAddConfig);
			this->groupBox12->Controls->Add(this->bAddPause);
			this->groupBox12->Controls->Add(this->button3);
			this->groupBox12->Controls->Add(this->label18);
			this->groupBox12->Controls->Add(this->txtPause);
			this->groupBox12->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox12->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->groupBox12->Location = System::Drawing::Point(263, 53);
			this->groupBox12->Name = L"groupBox12";
			this->groupBox12->Size = System::Drawing::Size(498, 211);
			this->groupBox12->TabIndex = 17;
			this->groupBox12->TabStop = false;
			this->groupBox12->Text = L"Motion";
			// 
			// lblRecLoaded
			// 
			this->lblRecLoaded->AutoSize = true;
			this->lblRecLoaded->ForeColor = System::Drawing::Color::GreenYellow;
			this->lblRecLoaded->Location = System::Drawing::Point(281, 126);
			this->lblRecLoaded->Name = L"lblRecLoaded";
			this->lblRecLoaded->Size = System::Drawing::Size(104, 19);
			this->lblRecLoaded->TabIndex = 31;
			this->lblRecLoaded->Text = L"LOADED OK";
			// 
			// bPlayRecording
			// 
			this->bPlayRecording->BackColor = System::Drawing::Color::OliveDrab;
			this->bPlayRecording->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->bPlayRecording->Location = System::Drawing::Point(285, 163);
			this->bPlayRecording->Name = L"bPlayRecording";
			this->bPlayRecording->Size = System::Drawing::Size(196, 37);
			this->bPlayRecording->TabIndex = 14;
			this->bPlayRecording->Text = L"Play Recording";
			this->bPlayRecording->UseVisualStyleBackColor = false;
			this->bPlayRecording->Click += gcnew System::EventHandler(this, &Form1::bPlayRecording_Click);
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label34->Location = System::Drawing::Point(280, 37);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(46, 19);
			this->label34->TabIndex = 30;
			this->label34->Text = L"Path:";
			// 
			// txtPathMotion
			// 
			this->txtPathMotion->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F));
			this->txtPathMotion->Location = System::Drawing::Point(329, 33);
			this->txtPathMotion->Name = L"txtPathMotion";
			this->txtPathMotion->Size = System::Drawing::Size(152, 23);
			this->txtPathMotion->TabIndex = 29;
			// 
			// button7
			// 
			this->button7->BackColor = System::Drawing::Color::SlateGray;
			this->button7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)), 
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->button7->Location = System::Drawing::Point(285, 72);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(196, 37);
			this->button7->TabIndex = 20;
			this->button7->Text = L"Load Recording";
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// lblEndRec
			// 
			this->lblEndRec->AutoSize = true;
			this->lblEndRec->ForeColor = System::Drawing::Color::GreenYellow;
			this->lblEndRec->Location = System::Drawing::Point(220, 172);
			this->lblEndRec->Name = L"lblEndRec";
			this->lblEndRec->Size = System::Drawing::Size(32, 19);
			this->lblEndRec->TabIndex = 26;
			this->lblEndRec->Text = L"OK";
			// 
			// lblAddConfig
			// 
			this->lblAddConfig->AutoSize = true;
			this->lblAddConfig->ForeColor = System::Drawing::Color::GreenYellow;
			this->lblAddConfig->Location = System::Drawing::Point(220, 126);
			this->lblAddConfig->Name = L"lblAddConfig";
			this->lblAddConfig->Size = System::Drawing::Size(32, 19);
			this->lblAddConfig->TabIndex = 25;
			this->lblAddConfig->Text = L"OK";
			// 
			// lblAddPause
			// 
			this->lblAddPause->AutoSize = true;
			this->lblAddPause->ForeColor = System::Drawing::Color::GreenYellow;
			this->lblAddPause->Location = System::Drawing::Point(220, 81);
			this->lblAddPause->Name = L"lblAddPause";
			this->lblAddPause->Size = System::Drawing::Size(32, 19);
			this->lblAddPause->TabIndex = 24;
			this->lblAddPause->Text = L"OK";
			// 
			// lblBeginRec
			// 
			this->lblBeginRec->AutoSize = true;
			this->lblBeginRec->ForeColor = System::Drawing::Color::GreenYellow;
			this->lblBeginRec->Location = System::Drawing::Point(220, 37);
			this->lblBeginRec->Name = L"lblBeginRec";
			this->lblBeginRec->Size = System::Drawing::Size(32, 19);
			this->lblBeginRec->TabIndex = 23;
			this->lblBeginRec->Text = L"OK";
			// 
			// bEndRec
			// 
			this->bEndRec->BackColor = System::Drawing::Color::SlateGray;
			this->bEndRec->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)), 
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->bEndRec->Location = System::Drawing::Point(9, 163);
			this->bEndRec->Name = L"bEndRec";
			this->bEndRec->Size = System::Drawing::Size(196, 37);
			this->bEndRec->TabIndex = 22;
			this->bEndRec->Text = L"End Recording";
			this->bEndRec->UseVisualStyleBackColor = false;
			this->bEndRec->Click += gcnew System::EventHandler(this, &Form1::bEndRec_Click);
			// 
			// bAddConfig
			// 
			this->bAddConfig->BackColor = System::Drawing::Color::SlateGray;
			this->bAddConfig->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)), 
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->bAddConfig->Location = System::Drawing::Point(9, 117);
			this->bAddConfig->Name = L"bAddConfig";
			this->bAddConfig->Size = System::Drawing::Size(194, 37);
			this->bAddConfig->TabIndex = 21;
			this->bAddConfig->Text = L"Add Configuration";
			this->bAddConfig->UseVisualStyleBackColor = false;
			this->bAddConfig->Click += gcnew System::EventHandler(this, &Form1::bAddConfig_Click);
			// 
			// bAddPause
			// 
			this->bAddPause->BackColor = System::Drawing::Color::SlateGray;
			this->bAddPause->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)), 
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->bAddPause->Location = System::Drawing::Point(9, 72);
			this->bAddPause->Name = L"bAddPause";
			this->bAddPause->Size = System::Drawing::Size(115, 37);
			this->bAddPause->TabIndex = 20;
			this->bAddPause->Text = L"Add Pause:";
			this->bAddPause->UseVisualStyleBackColor = false;
			this->bAddPause->Click += gcnew System::EventHandler(this, &Form1::bAddPause_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::SlateGray;
			this->button3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)), 
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->button3->Location = System::Drawing::Point(9, 26);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(196, 37);
			this->button3->TabIndex = 19;
			this->button3->Text = L"Begin Recording";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Tahoma", 12));
			this->label18->Location = System::Drawing::Point(176, 81);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(30, 19);
			this->label18->TabIndex = 19;
			this->label18->Text = L"ms";
			// 
			// txtPause
			// 
			this->txtPause->Location = System::Drawing::Point(130, 78);
			this->txtPause->Name = L"txtPause";
			this->txtPause->Size = System::Drawing::Size(40, 27);
			this->txtPause->TabIndex = 17;
			// 
			// groupBox11
			// 
			this->groupBox11->Controls->Add(this->label33);
			this->groupBox11->Controls->Add(this->txtPathConfig);
			this->groupBox11->Controls->Add(this->lblLoadConfig);
			this->groupBox11->Controls->Add(this->lblSaveConfig);
			this->groupBox11->Controls->Add(this->btnSaveConfig);
			this->groupBox11->Controls->Add(this->btnLoadConfig);
			this->groupBox11->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox11->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->groupBox11->Location = System::Drawing::Point(18, 53);
			this->groupBox11->Name = L"groupBox11";
			this->groupBox11->Size = System::Drawing::Size(225, 211);
			this->groupBox11->TabIndex = 16;
			this->groupBox11->TabStop = false;
			this->groupBox11->Text = L"Configuration";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label33->Location = System::Drawing::Point(6, 37);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(46, 19);
			this->label33->TabIndex = 28;
			this->label33->Text = L"Path:";
			// 
			// txtPathConfig
			// 
			this->txtPathConfig->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtPathConfig->Location = System::Drawing::Point(53, 33);
			this->txtPathConfig->Name = L"txtPathConfig";
			this->txtPathConfig->Size = System::Drawing::Size(149, 23);
			this->txtPathConfig->TabIndex = 27;
			// 
			// lblLoadConfig
			// 
			this->lblLoadConfig->AutoSize = true;
			this->lblLoadConfig->ForeColor = System::Drawing::Color::GreenYellow;
			this->lblLoadConfig->Location = System::Drawing::Point(6, 184);
			this->lblLoadConfig->Name = L"lblLoadConfig";
			this->lblLoadConfig->Size = System::Drawing::Size(82, 19);
			this->lblLoadConfig->TabIndex = 18;
			this->lblLoadConfig->Text = L"LOAD OK";
			// 
			// lblSaveConfig
			// 
			this->lblSaveConfig->AutoSize = true;
			this->lblSaveConfig->ForeColor = System::Drawing::Color::GreenYellow;
			this->lblSaveConfig->Location = System::Drawing::Point(7, 113);
			this->lblSaveConfig->Name = L"lblSaveConfig";
			this->lblSaveConfig->Size = System::Drawing::Size(80, 19);
			this->lblSaveConfig->TabIndex = 17;
			this->lblSaveConfig->Text = L"SAVE OK";
			// 
			// btnSaveConfig
			// 
			this->btnSaveConfig->BackColor = System::Drawing::Color::SlateGray;
			this->btnSaveConfig->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)), 
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->btnSaveConfig->Location = System::Drawing::Point(9, 72);
			this->btnSaveConfig->Name = L"btnSaveConfig";
			this->btnSaveConfig->Size = System::Drawing::Size(193, 37);
			this->btnSaveConfig->TabIndex = 15;
			this->btnSaveConfig->Text = L"Save Configuration";
			this->btnSaveConfig->UseVisualStyleBackColor = false;
			this->btnSaveConfig->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// btnLoadConfig
			// 
			this->btnLoadConfig->BackColor = System::Drawing::Color::SlateGray;
			this->btnLoadConfig->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)), 
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->btnLoadConfig->Location = System::Drawing::Point(9, 144);
			this->btnLoadConfig->Name = L"btnLoadConfig";
			this->btnLoadConfig->Size = System::Drawing::Size(193, 37);
			this->btnLoadConfig->TabIndex = 14;
			this->btnLoadConfig->Text = L"Load Configuration";
			this->btnLoadConfig->UseVisualStyleBackColor = false;
			this->btnLoadConfig->Click += gcnew System::EventHandler(this, &Form1::btnLoadConfig_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(646, 25);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 13);
			this->label3->TabIndex = 13;
			this->label3->Text = L"label3";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Tahoma", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label14->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->label14->Location = System::Drawing::Point(14, 17);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(197, 23);
			this->label14->TabIndex = 11;
			this->label14->Text = L"PRESET CONTROLS";
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->panel2->Controls->Add(this->bEmergencyStop);
			this->panel2->Controls->Add(this->bReset);
			this->panel2->Controls->Add(this->bStartAll);
			this->panel2->Controls->Add(this->groupBox1);
			this->panel2->Controls->Add(this->groupBox7);
			this->panel2->Controls->Add(this->label20);
			this->panel2->Controls->Add(this->gFinger1);
			this->panel2->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->panel2->Location = System::Drawing::Point(814, 38);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(547, 889);
			this->panel2->TabIndex = 2;
			// 
			// bEmergencyStop
			// 
			this->bEmergencyStop->BackColor = System::Drawing::Color::Red;
			this->bEmergencyStop->Font = (gcnew System::Drawing::Font(L"Tahoma", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->bEmergencyStop->Location = System::Drawing::Point(399, 848);
			this->bEmergencyStop->Name = L"bEmergencyStop";
			this->bEmergencyStop->Size = System::Drawing::Size(130, 37);
			this->bEmergencyStop->TabIndex = 16;
			this->bEmergencyStop->Text = L"STOP";
			this->bEmergencyStop->UseVisualStyleBackColor = false;
			this->bEmergencyStop->Click += gcnew System::EventHandler(this, &Form1::bEmergencyStop_Click);
			// 
			// bReset
			// 
			this->bReset->BackColor = System::Drawing::Color::Gold;
			this->bReset->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->bReset->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->bReset->Location = System::Drawing::Point(214, 849);
			this->bReset->Name = L"bReset";
			this->bReset->Size = System::Drawing::Size(130, 37);
			this->bReset->TabIndex = 15;
			this->bReset->Text = L"Reset";
			this->bReset->UseVisualStyleBackColor = false;
			this->bReset->Click += gcnew System::EventHandler(this, &Form1::bReset_Click);
			// 
			// bStartAll
			// 
			this->bStartAll->BackColor = System::Drawing::Color::OliveDrab;
			this->bStartAll->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->bStartAll->Location = System::Drawing::Point(20, 849);
			this->bStartAll->Name = L"bStartAll";
			this->bStartAll->Size = System::Drawing::Size(130, 37);
			this->bStartAll->TabIndex = 13;
			this->bStartAll->Text = L"Start All";
			this->bStartAll->UseVisualStyleBackColor = false;
			this->bStartAll->Click += gcnew System::EventHandler(this, &Form1::bStartAll_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->chk3s);
			this->groupBox1->Controls->Add(this->lblSpeed3);
			this->groupBox1->Controls->Add(this->pbarMF3);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->trSpeed3);
			this->groupBox1->Controls->Add(this->bStartMF3);
			this->groupBox1->Controls->Add(this->groupBox2);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox1->ForeColor = System::Drawing::Color::ForestGreen;
			this->groupBox1->Location = System::Drawing::Point(20, 578);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(509, 265);
			this->groupBox1->TabIndex = 14;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Finger 3 - Green";
			// 
			// chk3s
			// 
			this->chk3s->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->chk3s->ForeColor = System::Drawing::Color::Lavender;
			this->chk3s->Location = System::Drawing::Point(372, 26);
			this->chk3s->Name = L"chk3s";
			this->chk3s->Size = System::Drawing::Size(121, 44);
			this->chk3s->TabIndex = 18;
			this->chk3s->Text = L"Use same speed for all";
			this->chk3s->UseVisualStyleBackColor = true;
			// 
			// lblSpeed3
			// 
			this->lblSpeed3->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblSpeed3->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lblSpeed3->Location = System::Drawing::Point(428, 73);
			this->lblSpeed3->Name = L"lblSpeed3";
			this->lblSpeed3->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lblSpeed3->Size = System::Drawing::Size(78, 19);
			this->lblSpeed3->TabIndex = 12;
			this->lblSpeed3->Text = L"value";
			this->lblSpeed3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pbarMF3
			// 
			this->pbarMF3->Location = System::Drawing::Point(374, 151);
			this->pbarMF3->Maximum = 100000;
			this->pbarMF3->Name = L"pbarMF3";
			this->pbarMF3->Size = System::Drawing::Size(119, 27);
			this->pbarMF3->TabIndex = 4;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->label6->Location = System::Drawing::Point(367, 71);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(52, 19);
			this->label6->TabIndex = 11;
			this->label6->Text = L"Speed";
			// 
			// trSpeed3
			// 
			this->trSpeed3->Location = System::Drawing::Point(363, 95);
			this->trSpeed3->Maximum = 100;
			this->trSpeed3->Minimum = 1;
			this->trSpeed3->Name = L"trSpeed3";
			this->trSpeed3->Size = System::Drawing::Size(137, 45);
			this->trSpeed3->TabIndex = 11;
			this->trSpeed3->Value = 1;
			this->trSpeed3->Scroll += gcnew System::EventHandler(this, &Form1::trSpeed3_Scroll);
			// 
			// bStartMF3
			// 
			this->bStartMF3->BackColor = System::Drawing::Color::OliveDrab;
			this->bStartMF3->ForeColor = System::Drawing::SystemColors::Desktop;
			this->bStartMF3->Location = System::Drawing::Point(374, 195);
			this->bStartMF3->Name = L"bStartMF3";
			this->bStartMF3->Size = System::Drawing::Size(121, 54);
			this->bStartMF3->TabIndex = 3;
			this->bStartMF3->Text = L"Start";
			this->bStartMF3->UseVisualStyleBackColor = false;
			this->bStartMF3->Click += gcnew System::EventHandler(this, &Form1::bStartMF3_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->groupBox9);
			this->groupBox2->Controls->Add(this->groupBox10);
			this->groupBox2->Controls->Add(this->label10);
			this->groupBox2->Controls->Add(this->label11);
			this->groupBox2->Controls->Add(this->label12);
			this->groupBox2->Controls->Add(this->label13);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Tahoma", 12));
			this->groupBox2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->groupBox2->Location = System::Drawing::Point(17, 19);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(340, 230);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Required";
			// 
			// groupBox9
			// 
			this->groupBox9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->groupBox9->Controls->Add(this->lbl33s);
			this->groupBox9->Controls->Add(this->lbl32s);
			this->groupBox9->Controls->Add(this->tr32s);
			this->groupBox9->Controls->Add(this->tr33s);
			this->groupBox9->Controls->Add(this->lbl31s);
			this->groupBox9->Controls->Add(this->tr31s);
			this->groupBox9->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox9->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->groupBox9->Location = System::Drawing::Point(211, 13);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Size = System::Drawing::Size(117, 205);
			this->groupBox9->TabIndex = 19;
			this->groupBox9->TabStop = false;
			this->groupBox9->Text = L"Speed";
			// 
			// lbl33s
			// 
			this->lbl33s->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lbl33s->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lbl33s->Location = System::Drawing::Point(19, 177);
			this->lbl33s->Name = L"lbl33s";
			this->lbl33s->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lbl33s->Size = System::Drawing::Size(78, 19);
			this->lbl33s->TabIndex = 12;
			this->lbl33s->Text = L"value";
			this->lbl33s->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lbl32s
			// 
			this->lbl32s->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lbl32s->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lbl32s->Location = System::Drawing::Point(19, 109);
			this->lbl32s->Name = L"lbl32s";
			this->lbl32s->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lbl32s->Size = System::Drawing::Size(78, 19);
			this->lbl32s->TabIndex = 12;
			this->lbl32s->Text = L"value";
			this->lbl32s->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tr32s
			// 
			this->tr32s->Location = System::Drawing::Point(3, 83);
			this->tr32s->Maximum = 100;
			this->tr32s->Name = L"tr32s";
			this->tr32s->Size = System::Drawing::Size(110, 45);
			this->tr32s->TabIndex = 10;
			this->tr32s->Value = 100;
			this->tr32s->Scroll += gcnew System::EventHandler(this, &Form1::tr32s_Scroll);
			// 
			// tr33s
			// 
			this->tr33s->Location = System::Drawing::Point(3, 151);
			this->tr33s->Maximum = 100;
			this->tr33s->Name = L"tr33s";
			this->tr33s->Size = System::Drawing::Size(110, 45);
			this->tr33s->TabIndex = 11;
			this->tr33s->Value = 100;
			this->tr33s->Scroll += gcnew System::EventHandler(this, &Form1::tr33s_Scroll);
			// 
			// lbl31s
			// 
			this->lbl31s->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lbl31s->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lbl31s->Location = System::Drawing::Point(18, 45);
			this->lbl31s->Name = L"lbl31s";
			this->lbl31s->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lbl31s->Size = System::Drawing::Size(78, 19);
			this->lbl31s->TabIndex = 11;
			this->lbl31s->Text = L"value";
			this->lbl31s->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tr31s
			// 
			this->tr31s->Location = System::Drawing::Point(3, 19);
			this->tr31s->Maximum = 100;
			this->tr31s->Name = L"tr31s";
			this->tr31s->Size = System::Drawing::Size(110, 45);
			this->tr31s->TabIndex = 9;
			this->tr31s->Value = 100;
			this->tr31s->Scroll += gcnew System::EventHandler(this, &Form1::tr31s_Scroll);
			// 
			// groupBox10
			// 
			this->groupBox10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->groupBox10->Controls->Add(this->lblFinger3Phalanx3);
			this->groupBox10->Controls->Add(this->lblFinger3Phalanx2);
			this->groupBox10->Controls->Add(this->trFinger3Ph2);
			this->groupBox10->Controls->Add(this->trFinger3Ph3);
			this->groupBox10->Controls->Add(this->lblFinger3Phalanx1);
			this->groupBox10->Controls->Add(this->trFinger3Ph1);
			this->groupBox10->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox10->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->groupBox10->Location = System::Drawing::Point(85, 13);
			this->groupBox10->Name = L"groupBox10";
			this->groupBox10->Size = System::Drawing::Size(117, 205);
			this->groupBox10->TabIndex = 18;
			this->groupBox10->TabStop = false;
			this->groupBox10->Text = L"Position";
			// 
			// lblFinger3Phalanx3
			// 
			this->lblFinger3Phalanx3->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblFinger3Phalanx3->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lblFinger3Phalanx3->Location = System::Drawing::Point(19, 177);
			this->lblFinger3Phalanx3->Name = L"lblFinger3Phalanx3";
			this->lblFinger3Phalanx3->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lblFinger3Phalanx3->Size = System::Drawing::Size(78, 19);
			this->lblFinger3Phalanx3->TabIndex = 12;
			this->lblFinger3Phalanx3->Text = L"value";
			this->lblFinger3Phalanx3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblFinger3Phalanx2
			// 
			this->lblFinger3Phalanx2->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblFinger3Phalanx2->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lblFinger3Phalanx2->Location = System::Drawing::Point(19, 109);
			this->lblFinger3Phalanx2->Name = L"lblFinger3Phalanx2";
			this->lblFinger3Phalanx2->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lblFinger3Phalanx2->Size = System::Drawing::Size(78, 19);
			this->lblFinger3Phalanx2->TabIndex = 12;
			this->lblFinger3Phalanx2->Text = L"value";
			this->lblFinger3Phalanx2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// trFinger3Ph2
			// 
			this->trFinger3Ph2->Location = System::Drawing::Point(3, 83);
			this->trFinger3Ph2->Maximum = 1800;
			this->trFinger3Ph2->Name = L"trFinger3Ph2";
			this->trFinger3Ph2->Size = System::Drawing::Size(110, 45);
			this->trFinger3Ph2->TabIndex = 10;
			this->trFinger3Ph2->Value = 900;
			this->trFinger3Ph2->Scroll += gcnew System::EventHandler(this, &Form1::trFinger3Ph2_Scroll);
			// 
			// trFinger3Ph3
			// 
			this->trFinger3Ph3->Location = System::Drawing::Point(3, 151);
			this->trFinger3Ph3->Maximum = 1800;
			this->trFinger3Ph3->Name = L"trFinger3Ph3";
			this->trFinger3Ph3->Size = System::Drawing::Size(110, 45);
			this->trFinger3Ph3->TabIndex = 11;
			this->trFinger3Ph3->Value = 900;
			this->trFinger3Ph3->Scroll += gcnew System::EventHandler(this, &Form1::trFinger3Ph3_Scroll);
			// 
			// lblFinger3Phalanx1
			// 
			this->lblFinger3Phalanx1->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblFinger3Phalanx1->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lblFinger3Phalanx1->Location = System::Drawing::Point(18, 45);
			this->lblFinger3Phalanx1->Name = L"lblFinger3Phalanx1";
			this->lblFinger3Phalanx1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lblFinger3Phalanx1->Size = System::Drawing::Size(78, 19);
			this->lblFinger3Phalanx1->TabIndex = 11;
			this->lblFinger3Phalanx1->Text = L"value";
			this->lblFinger3Phalanx1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// trFinger3Ph1
			// 
			this->trFinger3Ph1->Location = System::Drawing::Point(3, 19);
			this->trFinger3Ph1->Maximum = 1100;
			this->trFinger3Ph1->Name = L"trFinger3Ph1";
			this->trFinger3Ph1->Size = System::Drawing::Size(110, 45);
			this->trFinger3Ph1->TabIndex = 9;
			this->trFinger3Ph1->Value = 900;
			this->trFinger3Ph1->Scroll += gcnew System::EventHandler(this, &Form1::trFinger3Ph1_Scroll);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(107, 19);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(0, 19);
			this->label10->TabIndex = 4;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->label11->Location = System::Drawing::Point(8, 170);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(48, 19);
			this->label11->TabIndex = 2;
			this->label11->Text = L"Distal";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->label12->Location = System::Drawing::Point(8, 102);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(55, 19);
			this->label12->TabIndex = 1;
			this->label12->Text = L"Middle";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label13->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->label13->Location = System::Drawing::Point(8, 38);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(71, 19);
			this->label13->TabIndex = 0;
			this->label13->Text = L"Proximal";
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->chk2s);
			this->groupBox7->Controls->Add(this->lblSpeed2);
			this->groupBox7->Controls->Add(this->trSpeed2);
			this->groupBox7->Controls->Add(this->pbarMF2);
			this->groupBox7->Controls->Add(this->label22);
			this->groupBox7->Controls->Add(this->bStartMF2);
			this->groupBox7->Controls->Add(this->groupBox8);
			this->groupBox7->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(205)), static_cast<System::Int32>(static_cast<System::Byte>(51)), 
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->groupBox7->Location = System::Drawing::Point(20, 307);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(509, 265);
			this->groupBox7->TabIndex = 13;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"Finger 2 - Red";
			// 
			// chk2s
			// 
			this->chk2s->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->chk2s->ForeColor = System::Drawing::Color::Lavender;
			this->chk2s->Location = System::Drawing::Point(373, 26);
			this->chk2s->Name = L"chk2s";
			this->chk2s->Size = System::Drawing::Size(121, 44);
			this->chk2s->TabIndex = 17;
			this->chk2s->Text = L"Use same speed for all";
			this->chk2s->UseVisualStyleBackColor = true;
			// 
			// lblSpeed2
			// 
			this->lblSpeed2->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblSpeed2->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lblSpeed2->Location = System::Drawing::Point(424, 75);
			this->lblSpeed2->Name = L"lblSpeed2";
			this->lblSpeed2->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lblSpeed2->Size = System::Drawing::Size(78, 19);
			this->lblSpeed2->TabIndex = 12;
			this->lblSpeed2->Text = L"value";
			this->lblSpeed2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// trSpeed2
			// 
			this->trSpeed2->Location = System::Drawing::Point(366, 97);
			this->trSpeed2->Maximum = 100;
			this->trSpeed2->Minimum = 1;
			this->trSpeed2->Name = L"trSpeed2";
			this->trSpeed2->Size = System::Drawing::Size(137, 45);
			this->trSpeed2->TabIndex = 11;
			this->trSpeed2->Value = 1;
			this->trSpeed2->Scroll += gcnew System::EventHandler(this, &Form1::trSpeed2_Scroll);
			// 
			// pbarMF2
			// 
			this->pbarMF2->Location = System::Drawing::Point(374, 153);
			this->pbarMF2->Maximum = 100000;
			this->pbarMF2->Name = L"pbarMF2";
			this->pbarMF2->Size = System::Drawing::Size(119, 27);
			this->pbarMF2->TabIndex = 4;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label22->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->label22->Location = System::Drawing::Point(370, 73);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(52, 19);
			this->label22->TabIndex = 11;
			this->label22->Text = L"Speed";
			// 
			// bStartMF2
			// 
			this->bStartMF2->BackColor = System::Drawing::Color::OliveDrab;
			this->bStartMF2->ForeColor = System::Drawing::SystemColors::Desktop;
			this->bStartMF2->Location = System::Drawing::Point(373, 196);
			this->bStartMF2->Name = L"bStartMF2";
			this->bStartMF2->Size = System::Drawing::Size(121, 54);
			this->bStartMF2->TabIndex = 3;
			this->bStartMF2->Text = L"Start";
			this->bStartMF2->UseVisualStyleBackColor = false;
			this->bStartMF2->Click += gcnew System::EventHandler(this, &Form1::bStartMF2_Click);
			// 
			// groupBox8
			// 
			this->groupBox8->Controls->Add(this->groupBox5);
			this->groupBox8->Controls->Add(this->groupBox6);
			this->groupBox8->Controls->Add(this->label28);
			this->groupBox8->Controls->Add(this->label29);
			this->groupBox8->Controls->Add(this->label30);
			this->groupBox8->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox8->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->groupBox8->Location = System::Drawing::Point(17, 19);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Size = System::Drawing::Size(340, 231);
			this->groupBox8->TabIndex = 1;
			this->groupBox8->TabStop = false;
			this->groupBox8->Text = L"Required";
			// 
			// groupBox5
			// 
			this->groupBox5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->groupBox5->Controls->Add(this->lbl23s);
			this->groupBox5->Controls->Add(this->lbl22s);
			this->groupBox5->Controls->Add(this->tr22s);
			this->groupBox5->Controls->Add(this->tr23s);
			this->groupBox5->Controls->Add(this->lbl21s);
			this->groupBox5->Controls->Add(this->tr21s);
			this->groupBox5->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox5->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->groupBox5->Location = System::Drawing::Point(211, 15);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(117, 205);
			this->groupBox5->TabIndex = 17;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Speed";
			// 
			// lbl23s
			// 
			this->lbl23s->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lbl23s->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lbl23s->Location = System::Drawing::Point(19, 177);
			this->lbl23s->Name = L"lbl23s";
			this->lbl23s->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lbl23s->Size = System::Drawing::Size(78, 19);
			this->lbl23s->TabIndex = 12;
			this->lbl23s->Text = L"value";
			this->lbl23s->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lbl22s
			// 
			this->lbl22s->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lbl22s->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lbl22s->Location = System::Drawing::Point(19, 109);
			this->lbl22s->Name = L"lbl22s";
			this->lbl22s->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lbl22s->Size = System::Drawing::Size(78, 19);
			this->lbl22s->TabIndex = 12;
			this->lbl22s->Text = L"value";
			this->lbl22s->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tr22s
			// 
			this->tr22s->Location = System::Drawing::Point(3, 83);
			this->tr22s->Maximum = 100;
			this->tr22s->Name = L"tr22s";
			this->tr22s->Size = System::Drawing::Size(110, 45);
			this->tr22s->TabIndex = 10;
			this->tr22s->Value = 100;
			this->tr22s->Scroll += gcnew System::EventHandler(this, &Form1::tr22s_Scroll);
			// 
			// tr23s
			// 
			this->tr23s->Location = System::Drawing::Point(3, 151);
			this->tr23s->Maximum = 100;
			this->tr23s->Name = L"tr23s";
			this->tr23s->Size = System::Drawing::Size(110, 45);
			this->tr23s->TabIndex = 11;
			this->tr23s->Value = 100;
			this->tr23s->Scroll += gcnew System::EventHandler(this, &Form1::tr23s_Scroll);
			// 
			// lbl21s
			// 
			this->lbl21s->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lbl21s->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lbl21s->Location = System::Drawing::Point(18, 45);
			this->lbl21s->Name = L"lbl21s";
			this->lbl21s->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lbl21s->Size = System::Drawing::Size(78, 19);
			this->lbl21s->TabIndex = 11;
			this->lbl21s->Text = L"value";
			this->lbl21s->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tr21s
			// 
			this->tr21s->Location = System::Drawing::Point(3, 19);
			this->tr21s->Maximum = 100;
			this->tr21s->Name = L"tr21s";
			this->tr21s->Size = System::Drawing::Size(110, 45);
			this->tr21s->TabIndex = 9;
			this->tr21s->Value = 100;
			this->tr21s->Scroll += gcnew System::EventHandler(this, &Form1::tr21s_Scroll);
			// 
			// groupBox6
			// 
			this->groupBox6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->groupBox6->Controls->Add(this->lblFinger2Phalanx3);
			this->groupBox6->Controls->Add(this->lblFinger2Phalanx2);
			this->groupBox6->Controls->Add(this->trFinger2Ph2);
			this->groupBox6->Controls->Add(this->trFinger2Ph3);
			this->groupBox6->Controls->Add(this->lblFinger2Phalanx1);
			this->groupBox6->Controls->Add(this->trFinger2Ph1);
			this->groupBox6->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox6->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->groupBox6->Location = System::Drawing::Point(85, 15);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(117, 205);
			this->groupBox6->TabIndex = 16;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Position";
			// 
			// lblFinger2Phalanx3
			// 
			this->lblFinger2Phalanx3->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblFinger2Phalanx3->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lblFinger2Phalanx3->Location = System::Drawing::Point(19, 177);
			this->lblFinger2Phalanx3->Name = L"lblFinger2Phalanx3";
			this->lblFinger2Phalanx3->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lblFinger2Phalanx3->Size = System::Drawing::Size(78, 19);
			this->lblFinger2Phalanx3->TabIndex = 12;
			this->lblFinger2Phalanx3->Text = L"value";
			this->lblFinger2Phalanx3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblFinger2Phalanx2
			// 
			this->lblFinger2Phalanx2->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblFinger2Phalanx2->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lblFinger2Phalanx2->Location = System::Drawing::Point(19, 109);
			this->lblFinger2Phalanx2->Name = L"lblFinger2Phalanx2";
			this->lblFinger2Phalanx2->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lblFinger2Phalanx2->Size = System::Drawing::Size(78, 19);
			this->lblFinger2Phalanx2->TabIndex = 12;
			this->lblFinger2Phalanx2->Text = L"value";
			this->lblFinger2Phalanx2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// trFinger2Ph2
			// 
			this->trFinger2Ph2->Location = System::Drawing::Point(3, 83);
			this->trFinger2Ph2->Maximum = 1800;
			this->trFinger2Ph2->Name = L"trFinger2Ph2";
			this->trFinger2Ph2->Size = System::Drawing::Size(110, 45);
			this->trFinger2Ph2->TabIndex = 10;
			this->trFinger2Ph2->Value = 900;
			this->trFinger2Ph2->Scroll += gcnew System::EventHandler(this, &Form1::trFinger2Ph2_Scroll);
			// 
			// trFinger2Ph3
			// 
			this->trFinger2Ph3->Location = System::Drawing::Point(3, 151);
			this->trFinger2Ph3->Maximum = 1800;
			this->trFinger2Ph3->Name = L"trFinger2Ph3";
			this->trFinger2Ph3->Size = System::Drawing::Size(110, 45);
			this->trFinger2Ph3->TabIndex = 11;
			this->trFinger2Ph3->Value = 900;
			this->trFinger2Ph3->Scroll += gcnew System::EventHandler(this, &Form1::trFinger2Ph3_Scroll);
			// 
			// lblFinger2Phalanx1
			// 
			this->lblFinger2Phalanx1->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblFinger2Phalanx1->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lblFinger2Phalanx1->Location = System::Drawing::Point(18, 45);
			this->lblFinger2Phalanx1->Name = L"lblFinger2Phalanx1";
			this->lblFinger2Phalanx1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lblFinger2Phalanx1->Size = System::Drawing::Size(78, 19);
			this->lblFinger2Phalanx1->TabIndex = 11;
			this->lblFinger2Phalanx1->Text = L"value";
			this->lblFinger2Phalanx1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// trFinger2Ph1
			// 
			this->trFinger2Ph1->Location = System::Drawing::Point(3, 19);
			this->trFinger2Ph1->Maximum = 1800;
			this->trFinger2Ph1->Minimum = 700;
			this->trFinger2Ph1->Name = L"trFinger2Ph1";
			this->trFinger2Ph1->Size = System::Drawing::Size(110, 45);
			this->trFinger2Ph1->TabIndex = 9;
			this->trFinger2Ph1->Value = 900;
			this->trFinger2Ph1->Scroll += gcnew System::EventHandler(this, &Form1::trFinger2Ph1_Scroll);
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->label28->Location = System::Drawing::Point(8, 170);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(48, 19);
			this->label28->TabIndex = 2;
			this->label28->Text = L"Distal";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->label29->Location = System::Drawing::Point(8, 102);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(55, 19);
			this->label29->TabIndex = 1;
			this->label29->Text = L"Middle";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label30->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->label30->Location = System::Drawing::Point(8, 38);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(71, 19);
			this->label30->TabIndex = 0;
			this->label30->Text = L"Proximal";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Tahoma", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label20->ForeColor = System::Drawing::SystemColors::Control;
			this->label20->Location = System::Drawing::Point(16, 17);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(194, 23);
			this->label20->TabIndex = 10;
			this->label20->Text = L"MANUAL CONTROL";
			// 
			// gFinger1
			// 
			this->gFinger1->Controls->Add(this->chk1s);
			this->gFinger1->Controls->Add(this->lblSpeed1);
			this->gFinger1->Controls->Add(this->label21);
			this->gFinger1->Controls->Add(this->trSpeed1);
			this->gFinger1->Controls->Add(this->pbarMF1);
			this->gFinger1->Controls->Add(this->bStartMF1);
			this->gFinger1->Controls->Add(this->gReqF1);
			this->gFinger1->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->gFinger1->ForeColor = System::Drawing::Color::RoyalBlue;
			this->gFinger1->Location = System::Drawing::Point(20, 43);
			this->gFinger1->Name = L"gFinger1";
			this->gFinger1->Size = System::Drawing::Size(509, 258);
			this->gFinger1->TabIndex = 0;
			this->gFinger1->TabStop = false;
			this->gFinger1->Text = L"Finger 1 - Blue";
			// 
			// chk1s
			// 
			this->chk1s->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->chk1s->ForeColor = System::Drawing::Color::Lavender;
			this->chk1s->Location = System::Drawing::Point(372, 26);
			this->chk1s->Name = L"chk1s";
			this->chk1s->Size = System::Drawing::Size(121, 44);
			this->chk1s->TabIndex = 13;
			this->chk1s->Text = L"Use same speed for all";
			this->chk1s->UseVisualStyleBackColor = true;
			// 
			// lblSpeed1
			// 
			this->lblSpeed1->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblSpeed1->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lblSpeed1->Location = System::Drawing::Point(426, 73);
			this->lblSpeed1->Name = L"lblSpeed1";
			this->lblSpeed1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lblSpeed1->Size = System::Drawing::Size(78, 19);
			this->lblSpeed1->TabIndex = 12;
			this->lblSpeed1->Text = L"value";
			this->lblSpeed1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label21->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->label21->Location = System::Drawing::Point(368, 73);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(52, 19);
			this->label21->TabIndex = 11;
			this->label21->Text = L"Speed";
			// 
			// trSpeed1
			// 
			this->trSpeed1->Location = System::Drawing::Point(363, 95);
			this->trSpeed1->Maximum = 100;
			this->trSpeed1->Minimum = 1;
			this->trSpeed1->Name = L"trSpeed1";
			this->trSpeed1->Size = System::Drawing::Size(139, 45);
			this->trSpeed1->TabIndex = 11;
			this->trSpeed1->Value = 1;
			this->trSpeed1->Scroll += gcnew System::EventHandler(this, &Form1::trSpeed1_Scroll);
			// 
			// pbarMF1
			// 
			this->pbarMF1->Location = System::Drawing::Point(373, 153);
			this->pbarMF1->Maximum = 100000;
			this->pbarMF1->Name = L"pbarMF1";
			this->pbarMF1->Size = System::Drawing::Size(120, 27);
			this->pbarMF1->TabIndex = 4;
			// 
			// bStartMF1
			// 
			this->bStartMF1->BackColor = System::Drawing::Color::OliveDrab;
			this->bStartMF1->ForeColor = System::Drawing::SystemColors::Desktop;
			this->bStartMF1->Location = System::Drawing::Point(372, 195);
			this->bStartMF1->Name = L"bStartMF1";
			this->bStartMF1->Size = System::Drawing::Size(121, 54);
			this->bStartMF1->TabIndex = 3;
			this->bStartMF1->Text = L"Start";
			this->bStartMF1->UseVisualStyleBackColor = false;
			this->bStartMF1->Click += gcnew System::EventHandler(this, &Form1::bStartMF1_Click);
			// 
			// gReqF1
			// 
			this->gReqF1->Controls->Add(this->groupBox4);
			this->gReqF1->Controls->Add(this->label1);
			this->gReqF1->Controls->Add(this->groupBox3);
			this->gReqF1->Controls->Add(this->lF1p3req);
			this->gReqF1->Controls->Add(this->lF1p2req);
			this->gReqF1->Controls->Add(this->lF1p1req);
			this->gReqF1->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->gReqF1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->gReqF1->Location = System::Drawing::Point(17, 19);
			this->gReqF1->Name = L"gReqF1";
			this->gReqF1->Size = System::Drawing::Size(340, 230);
			this->gReqF1->TabIndex = 1;
			this->gReqF1->TabStop = false;
			this->gReqF1->Text = L"Required";
			// 
			// groupBox4
			// 
			this->groupBox4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->groupBox4->Controls->Add(this->lbl13s);
			this->groupBox4->Controls->Add(this->lbl12s);
			this->groupBox4->Controls->Add(this->tr12s);
			this->groupBox4->Controls->Add(this->tr13s);
			this->groupBox4->Controls->Add(this->lbl11s);
			this->groupBox4->Controls->Add(this->tr11s);
			this->groupBox4->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox4->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->groupBox4->Location = System::Drawing::Point(211, 14);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(117, 205);
			this->groupBox4->TabIndex = 15;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Speed";
			// 
			// lbl13s
			// 
			this->lbl13s->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lbl13s->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lbl13s->Location = System::Drawing::Point(19, 177);
			this->lbl13s->Name = L"lbl13s";
			this->lbl13s->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lbl13s->Size = System::Drawing::Size(78, 19);
			this->lbl13s->TabIndex = 12;
			this->lbl13s->Text = L"value";
			this->lbl13s->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lbl12s
			// 
			this->lbl12s->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lbl12s->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lbl12s->Location = System::Drawing::Point(19, 109);
			this->lbl12s->Name = L"lbl12s";
			this->lbl12s->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lbl12s->Size = System::Drawing::Size(78, 19);
			this->lbl12s->TabIndex = 12;
			this->lbl12s->Text = L"value";
			this->lbl12s->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tr12s
			// 
			this->tr12s->Location = System::Drawing::Point(3, 83);
			this->tr12s->Maximum = 100;
			this->tr12s->Name = L"tr12s";
			this->tr12s->Size = System::Drawing::Size(110, 45);
			this->tr12s->TabIndex = 10;
			this->tr12s->Value = 100;
			this->tr12s->Scroll += gcnew System::EventHandler(this, &Form1::tr12s_Scroll);
			// 
			// tr13s
			// 
			this->tr13s->Location = System::Drawing::Point(3, 151);
			this->tr13s->Maximum = 100;
			this->tr13s->Name = L"tr13s";
			this->tr13s->Size = System::Drawing::Size(110, 45);
			this->tr13s->TabIndex = 11;
			this->tr13s->Value = 100;
			this->tr13s->Scroll += gcnew System::EventHandler(this, &Form1::tr13s_Scroll);
			// 
			// lbl11s
			// 
			this->lbl11s->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lbl11s->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lbl11s->Location = System::Drawing::Point(18, 45);
			this->lbl11s->Name = L"lbl11s";
			this->lbl11s->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lbl11s->Size = System::Drawing::Size(78, 19);
			this->lbl11s->TabIndex = 11;
			this->lbl11s->Text = L"value";
			this->lbl11s->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tr11s
			// 
			this->tr11s->Location = System::Drawing::Point(3, 19);
			this->tr11s->Maximum = 100;
			this->tr11s->Name = L"tr11s";
			this->tr11s->Size = System::Drawing::Size(110, 45);
			this->tr11s->TabIndex = 9;
			this->tr11s->Value = 100;
			this->tr11s->Scroll += gcnew System::EventHandler(this, &Form1::tr11s_Scroll);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(107, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 19);
			this->label1->TabIndex = 4;
			// 
			// groupBox3
			// 
			this->groupBox3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->groupBox3->Controls->Add(this->lblFinger1Phalanx3);
			this->groupBox3->Controls->Add(this->lblFinger1Phalanx2);
			this->groupBox3->Controls->Add(this->trFinger1Ph2);
			this->groupBox3->Controls->Add(this->trFinger1Ph3);
			this->groupBox3->Controls->Add(this->lblFinger1Phalanx1);
			this->groupBox3->Controls->Add(this->trFinger1Ph1);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox3->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->groupBox3->Location = System::Drawing::Point(85, 14);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(117, 205);
			this->groupBox3->TabIndex = 14;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Position";
			// 
			// lblFinger1Phalanx3
			// 
			this->lblFinger1Phalanx3->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblFinger1Phalanx3->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lblFinger1Phalanx3->Location = System::Drawing::Point(19, 177);
			this->lblFinger1Phalanx3->Name = L"lblFinger1Phalanx3";
			this->lblFinger1Phalanx3->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lblFinger1Phalanx3->Size = System::Drawing::Size(78, 19);
			this->lblFinger1Phalanx3->TabIndex = 12;
			this->lblFinger1Phalanx3->Text = L"value";
			this->lblFinger1Phalanx3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblFinger1Phalanx2
			// 
			this->lblFinger1Phalanx2->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblFinger1Phalanx2->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lblFinger1Phalanx2->Location = System::Drawing::Point(19, 109);
			this->lblFinger1Phalanx2->Name = L"lblFinger1Phalanx2";
			this->lblFinger1Phalanx2->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lblFinger1Phalanx2->Size = System::Drawing::Size(78, 19);
			this->lblFinger1Phalanx2->TabIndex = 12;
			this->lblFinger1Phalanx2->Text = L"value";
			this->lblFinger1Phalanx2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// trFinger1Ph2
			// 
			this->trFinger1Ph2->Location = System::Drawing::Point(3, 83);
			this->trFinger1Ph2->Maximum = 1800;
			this->trFinger1Ph2->Name = L"trFinger1Ph2";
			this->trFinger1Ph2->Size = System::Drawing::Size(110, 45);
			this->trFinger1Ph2->TabIndex = 10;
			this->trFinger1Ph2->Value = 900;
			this->trFinger1Ph2->Scroll += gcnew System::EventHandler(this, &Form1::trFinger1Ph2_Scroll);
			// 
			// trFinger1Ph3
			// 
			this->trFinger1Ph3->Location = System::Drawing::Point(3, 151);
			this->trFinger1Ph3->Maximum = 1800;
			this->trFinger1Ph3->Name = L"trFinger1Ph3";
			this->trFinger1Ph3->Size = System::Drawing::Size(110, 45);
			this->trFinger1Ph3->TabIndex = 11;
			this->trFinger1Ph3->Value = 900;
			this->trFinger1Ph3->Scroll += gcnew System::EventHandler(this, &Form1::trFinger1Ph3_Scroll);
			// 
			// lblFinger1Phalanx1
			// 
			this->lblFinger1Phalanx1->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblFinger1Phalanx1->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->lblFinger1Phalanx1->Location = System::Drawing::Point(18, 45);
			this->lblFinger1Phalanx1->Name = L"lblFinger1Phalanx1";
			this->lblFinger1Phalanx1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lblFinger1Phalanx1->Size = System::Drawing::Size(78, 19);
			this->lblFinger1Phalanx1->TabIndex = 11;
			this->lblFinger1Phalanx1->Text = L"value";
			this->lblFinger1Phalanx1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// trFinger1Ph1
			// 
			this->trFinger1Ph1->Location = System::Drawing::Point(3, 19);
			this->trFinger1Ph1->Maximum = 1800;
			this->trFinger1Ph1->Name = L"trFinger1Ph1";
			this->trFinger1Ph1->Size = System::Drawing::Size(110, 45);
			this->trFinger1Ph1->TabIndex = 9;
			this->trFinger1Ph1->Value = 900;
			this->trFinger1Ph1->Scroll += gcnew System::EventHandler(this, &Form1::trFinger1Ph1_Scroll);
			// 
			// lF1p3req
			// 
			this->lF1p3req->AutoSize = true;
			this->lF1p3req->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->lF1p3req->Location = System::Drawing::Point(8, 170);
			this->lF1p3req->Name = L"lF1p3req";
			this->lF1p3req->Size = System::Drawing::Size(48, 19);
			this->lF1p3req->TabIndex = 2;
			this->lF1p3req->Text = L"Distal";
			// 
			// lF1p2req
			// 
			this->lF1p2req->AutoSize = true;
			this->lF1p2req->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->lF1p2req->Location = System::Drawing::Point(8, 102);
			this->lF1p2req->Name = L"lF1p2req";
			this->lF1p2req->Size = System::Drawing::Size(55, 19);
			this->lF1p2req->TabIndex = 1;
			this->lF1p2req->Text = L"Middle";
			// 
			// lF1p1req
			// 
			this->lF1p1req->AutoSize = true;
			this->lF1p1req->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lF1p1req->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->lF1p1req->Location = System::Drawing::Point(8, 38);
			this->lF1p1req->Name = L"lF1p1req";
			this->lF1p1req->Size = System::Drawing::Size(71, 19);
			this->lF1p1req->TabIndex = 0;
			this->lF1p1req->Text = L"Proximal";
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->panel3->Controls->Add(this->cbBaudRate);
			this->panel3->Controls->Add(this->cbComPort);
			this->panel3->Controls->Add(this->label15);
			this->panel3->Location = System::Drawing::Point(12, 38);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(785, 52);
			this->panel3->TabIndex = 3;
			// 
			// cbBaudRate
			// 
			this->cbBaudRate->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->cbBaudRate->Font = (gcnew System::Drawing::Font(L"Tahoma", 11.25F, System::Drawing::FontStyle::Bold));
			this->cbBaudRate->ForeColor = System::Drawing::SystemColors::Window;
			this->cbBaudRate->FormattingEnabled = true;
			this->cbBaudRate->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"4800 baud", L"9600 baud", L"19200 baud", L"38400 baud", 
				L"57600 baud"});
			this->cbBaudRate->Location = System::Drawing::Point(649, 12);
			this->cbBaudRate->Name = L"cbBaudRate";
			this->cbBaudRate->Size = System::Drawing::Size(121, 26);
			this->cbBaudRate->TabIndex = 13;
			this->cbBaudRate->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cbBaudRate_SelectedIndexChanged);
			// 
			// cbComPort
			// 
			this->cbComPort->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->cbComPort->Font = (gcnew System::Drawing::Font(L"Tahoma", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cbComPort->ForeColor = System::Drawing::SystemColors::Window;
			this->cbComPort->FormattingEnabled = true;
			this->cbComPort->Items->AddRange(gcnew cli::array< System::Object^  >(6) {L"COM1", L"COM2", L"COM3", L"COM4", L"COM5", L"COM6"});
			this->cbComPort->Location = System::Drawing::Point(572, 12);
			this->cbComPort->Name = L"cbComPort";
			this->cbComPort->Size = System::Drawing::Size(71, 26);
			this->cbComPort->TabIndex = 12;
			this->cbComPort->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cbComPort_SelectedIndexChanged);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Tahoma", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label15->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->label15->Location = System::Drawing::Point(12, 7);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(342, 33);
			this->label15->TabIndex = 11;
			this->label15->Text = L"Robotic Hand Controller";
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// panelgl
			// 
			this->panelgl->Location = System::Drawing::Point(12, 107);
			this->panelgl->Name = L"panelgl";
			this->panelgl->Size = System::Drawing::Size(785, 528);
			this->panelgl->TabIndex = 4;
			this->panelgl->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::panelgl_MouseDown);
			this->panelgl->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::panelgl_MouseMove);
			this->panelgl->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::panelgl_MouseUp);
			// 
			// timer2
			// 
			this->timer2->Interval = 20;
			// 
			// timer3
			// 
			this->timer3->Interval = 10;
			this->timer3->SynchronizingObject = this;
			this->timer3->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &Form1::timer3_Elapsed);
			// 
			// timer4
			// 
			this->timer4->Interval = 10;
			this->timer4->SynchronizingObject = this;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileToolStripMenuItem, 
				this->helpToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1373, 24);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->saveConfigurationToolStripMenuItem, 
				this->openConfigurationToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// saveConfigurationToolStripMenuItem
			// 
			this->saveConfigurationToolStripMenuItem->Name = L"saveConfigurationToolStripMenuItem";
			this->saveConfigurationToolStripMenuItem->Size = System::Drawing::Size(178, 22);
			this->saveConfigurationToolStripMenuItem->Text = L"Save configuration";
			this->saveConfigurationToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// openConfigurationToolStripMenuItem
			// 
			this->openConfigurationToolStripMenuItem->Name = L"openConfigurationToolStripMenuItem";
			this->openConfigurationToolStripMenuItem->Size = System::Drawing::Size(178, 22);
			this->openConfigurationToolStripMenuItem->Text = L"Open configuration";
			this->openConfigurationToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::btnLoadConfig_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->helpToolStripMenuItem1});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// helpToolStripMenuItem1
			// 
			this->helpToolStripMenuItem1->Name = L"helpToolStripMenuItem1";
			this->helpToolStripMenuItem1->Size = System::Drawing::Size(102, 22);
			this->helpToolStripMenuItem1->Text = L"Help ";
			this->helpToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::helpToolStripMenuItem1_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(1373, 940);
			this->Controls->Add(this->panelgl);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->menuStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Robot Hand Control";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->groupBox12->ResumeLayout(false);
			this->groupBox12->PerformLayout();
			this->groupBox11->ResumeLayout(false);
			this->groupBox11->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trSpeed3))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox9->ResumeLayout(false);
			this->groupBox9->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr32s))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr33s))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr31s))->EndInit();
			this->groupBox10->ResumeLayout(false);
			this->groupBox10->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger3Ph2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger3Ph3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger3Ph1))->EndInit();
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trSpeed2))->EndInit();
			this->groupBox8->ResumeLayout(false);
			this->groupBox8->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr22s))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr23s))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr21s))->EndInit();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger2Ph2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger2Ph3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger2Ph1))->EndInit();
			this->gFinger1->ResumeLayout(false);
			this->gFinger1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trSpeed1))->EndInit();
			this->gReqF1->ResumeLayout(false);
			this->gReqF1->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr12s))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr13s))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tr11s))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger1Ph2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger1Ph3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trFinger1Ph1))->EndInit();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->timer3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->timer4))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

// ================================================================
// FORM ELEMENT FUNCTIONS
// ================================================================

// ================================================================
// timer1_Tick: 
// Update OpenGL drawing
// ================================================================
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			UNREFERENCED_PARAMETER(sender);
			UNREFERENCED_PARAMETER(e);
			o_gl->updateRotations();
			o_gl->DrawGLScene();
			o_gl->SwapOpenGLBuffers();
}

// ================================================================
// Finger 1 track bar scroll events: 
// Update final values, relevant labels
// ================================================================
private: System::Void trFinger1Ph1_Scroll(System::Object^  sender, System::EventArgs^  e) {
	    GLfloat val = (GLfloat)(trFinger1Ph1 -> Value)/10;
		final_values[0] = val;
		o_gl -> update_model_angles(0, val);
		flags_new_value[0] = 1;
		this -> lblFinger1Phalanx1 -> Text = "" + val.ToString("#.#");
		}
private: System::Void trFinger1Ph2_Scroll(System::Object^  sender, System::EventArgs^  e) {
		GLfloat val = (GLfloat)(trFinger1Ph2 -> Value)/10;
		final_values[1] = val;
		o_gl -> update_model_angles(1, val);
		flags_new_value[1] = 1;
		this -> lblFinger1Phalanx2 -> Text = "" + val.ToString("#.#");
		}
private: System::Void trFinger1Ph3_Scroll(System::Object^  sender, System::EventArgs^  e) {
		GLfloat val = (GLfloat)(trFinger1Ph3 -> Value)/10;
		final_values[2] = val;
		o_gl -> update_model_angles(2, val);
		flags_new_value[2] = 1;
		this -> lblFinger1Phalanx3 -> Text = "" + val.ToString("#.#");
		}

// ================================================================
// Finger 2 track bar scroll events: 
// Update final values, relevant labels
// ================================================================
private: System::Void trFinger2Ph1_Scroll(System::Object^  sender, System::EventArgs^  e) {
	    GLfloat val = (GLfloat)(trFinger2Ph1 -> Value)/10;
		final_values[3] = val;
		o_gl -> update_model_angles(4, val);
		flags_new_value[3] = 1;
		this -> lblFinger2Phalanx1 -> Text = "" + val.ToString("#.#");
		}
private: System::Void trFinger2Ph2_Scroll(System::Object^  sender, System::EventArgs^  e) {
		GLfloat val = (GLfloat)(trFinger2Ph2 -> Value)/10;
		final_values[4] = val;
		o_gl -> update_model_angles(5, val);
		flags_new_value[4] = 1;
		this -> lblFinger2Phalanx2 -> Text = "" + val.ToString("#.#");
		}
private: System::Void trFinger2Ph3_Scroll(System::Object^  sender, System::EventArgs^  e) {
		GLfloat val = (GLfloat)(trFinger2Ph3 -> Value)/10;
		final_values[5] = val;
		o_gl -> update_model_angles(6, val);
		flags_new_value[5] = 1;
		this -> lblFinger2Phalanx3 -> Text = "" + val.ToString("#.#");
		}

// ================================================================
// Finger 3 track bar scroll events: 
// Update final values, relevant labels
// ================================================================
private: System::Void trFinger3Ph1_Scroll(System::Object^  sender, System::EventArgs^  e) {
	    GLfloat val = (GLfloat)(trFinger3Ph1 -> Value)/10;
		final_values[6] = val;
		o_gl -> update_model_angles(8, val);
		flags_new_value[6] = 1;
		this -> lblFinger3Phalanx1 -> Text = "" + val.ToString("#.#");
		}
private: System::Void trFinger3Ph2_Scroll(System::Object^  sender, System::EventArgs^  e) {
		GLfloat val = (GLfloat)(trFinger3Ph2 -> Value)/10;
		final_values[7] = val;
		o_gl -> update_model_angles(9, val);
		flags_new_value[7] = 1;
		this -> lblFinger3Phalanx2 -> Text = "" + val.ToString("#.#");
		}
private: System::Void trFinger3Ph3_Scroll(System::Object^  sender, System::EventArgs^  e) {
		GLfloat val = (GLfloat)(trFinger3Ph3 -> Value)/10;
		final_values[8] = val;
		o_gl -> update_model_angles(10, val);
		flags_new_value[8] = 1;
		this -> lblFinger3Phalanx3 -> Text = "" + val.ToString("#.#");
		}

// ================================================================
// Common speed track scroll events (one speed for all phalanges):
// Update relevant labels
// ================================================================
private: System::Void trSpeed1_Scroll(System::Object^  sender, System::EventArgs^  e) {
		this -> lblSpeed1 -> Text = (trSpeed1 -> Value) + "%";
}
private: System::Void trSpeed2_Scroll(System::Object^  sender, System::EventArgs^  e) {
		this -> lblSpeed2 -> Text = (trSpeed2 -> Value) + "%";
}
private: System::Void trSpeed3_Scroll(System::Object^  sender, System::EventArgs^  e) {
		this -> lblSpeed3 -> Text = (trSpeed3 -> Value) + "%";
}

// ================================================================
// Finger 1 Speed track bars
// Update relevant labels
// ================================================================
private: System::Void tr11s_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 this -> lbl11s -> Text = (tr11s -> Value) + "%";
		 }
private: System::Void tr12s_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 this -> lbl12s -> Text = (tr12s -> Value) + "%";
		 }
private: System::Void tr13s_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 this -> lbl13s -> Text = (tr13s -> Value) + "%";
		 }

// ================================================================
// Finger 2 Speed track bars
// Update relevant labels
// ================================================================
private: System::Void tr21s_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 this -> lbl21s -> Text = (tr21s -> Value) + "%";
		 }
private: System::Void tr22s_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 this -> lbl22s -> Text = (tr22s -> Value) + "%";
		 }
private: System::Void tr23s_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 this -> lbl23s -> Text = (tr23s -> Value) + "%";
		 }

// ================================================================
// Finger 3 Speed track bars
// Update relevant labels
// ================================================================
private: System::Void tr31s_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 this -> lbl31s -> Text = (tr31s -> Value) + "%";
		 }
private: System::Void tr32s_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 this -> lbl32s -> Text = (tr32s -> Value) + "%";
		 }
private: System::Void tr33s_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 this -> lbl33s -> Text = (tr33s -> Value) + "%";
		 }

// ================================================================
// Start button events:
// Calculate increments, send data out
// ================================================================
private: System::Void bStartMF1_Click(System::Object^  sender, System::EventArgs^  e) {
			intervals_set1();
		 }
private: System::Void bStartMF2_Click(System::Object^  sender, System::EventArgs^  e) {
			intervals_set2();
		 }
private: System::Void bStartMF3_Click(System::Object^  sender, System::EventArgs^  e) {
			intervals_set3();
		 }
private: System::Void bStartAll_Click(System::Object^ sender, System::EventArgs^ e){
			intervals_set1();
			intervals_set2();
			intervals_set3();
		 }

// ================================================================
// Reset button event: 
// Reset hand to 90 degrees, send data out
// ================================================================
private: System::Void bReset_Click(System::Object^  sender, System::EventArgs^  e) {
			 reset_Hand();
		 }

// ================================================================
// MouseDown event: 
// Track down what button is pressed, record location
// ================================================================
private: System::Void panelgl_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 MouseState.leftButton = FALSE;
		 MouseState.rightButton = FALSE;
		 MouseState.middleButton = FALSE;

		 POINT mouseDownLocation;
		 HWND hWnd;

		 hWnd = static_cast<HWND>((panelgl) -> Handle.ToPointer());

		 // Register which button is pressed
		 if (e->Button == System::Windows::Forms::MouseButtons::Left)
		 {
			 MouseState.leftButton = TRUE;
			if (GetCursorPos(&mouseDownLocation))
			{
			if (ScreenToClient(hWnd, &mouseDownLocation))
				{
					MouseState.x = mouseDownLocation.x;
					MouseState.y = mouseDownLocation.y;
					MouseState.old_x = mouseDownLocation.x;
					MouseState.old_y = mouseDownLocation.y;
					o_gl -> selectGL(MouseState.old_x, (528 - MouseState.old_y));
				}
			}
		 }
		 else if (e->Button == System::Windows::Forms::MouseButtons::Right)
		 {
			 MouseState.rightButton = TRUE;	
			 if (GetCursorPos(&mouseDownLocation))
			 {
				if (ScreenToClient(hWnd, &mouseDownLocation))
				{
					    MouseState.x = mouseDownLocation.x;
						MouseState.y = mouseDownLocation.y;
						MouseState.old_x = mouseDownLocation.x;
						MouseState.old_y = mouseDownLocation.y;
				}
			 }
		 }
		 else if (e->Button == System::Windows::Forms::MouseButtons::Middle)
		 {
			 MouseState.middleButton = TRUE;
		}
 }

// ================================================================
// MouseMove event: 
// Record new mouse location
// ================================================================
private: System::Void panelgl_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		// Update the mouse path with the mouse information
        POINT mouseDownLocation;
		HWND hWnd;

		hWnd = static_cast<HWND>((panelgl) -> Handle.ToPointer());

		if (MouseState.rightButton && !MouseState.leftButton && !MouseState.middleButton)
		{
			if (GetCursorPos(&mouseDownLocation))
			{
				if (ScreenToClient(hWnd, &mouseDownLocation))
					{
						MouseState.old_x = MouseState.x;
						MouseState.old_y = MouseState.y;
						MouseState.x = mouseDownLocation.x;
						MouseState.y = mouseDownLocation.y;
						label3 -> Text = "X: " + MouseState.x + " Y: " + MouseState.y;
					}
			}
		 }
		else if (MouseState.leftButton && !MouseState.rightButton && !MouseState.middleButton){
		   if (GetCursorPos(&mouseDownLocation))
			{
			if (ScreenToClient(hWnd, &mouseDownLocation))
				{
					FLAG_PHALANX_BUSY = TRUE;
					MouseState.old_x = MouseState.x;
					MouseState.old_y = MouseState.y;
					MouseState.x = mouseDownLocation.x;
					MouseState.y = mouseDownLocation.y;
					label3 -> Text = "X: " + MouseState.x + " Y: " + MouseState.y;
					o_gl -> selectGL(MouseState.x, (528 - MouseState.y));
				}
			}
		 }
}
		
// ================================================================
// MouseUp event: 
// Set MouseState button states to false, reset pointer location
// ================================================================
private: System::Void panelgl_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 MouseState.leftButton = FALSE;
		 MouseState.rightButton = FALSE;
		 FLAG_PHALANX_BUSY = FALSE;
		 
		 MouseState.old_x = MouseState.x;
		 MouseState.old_y = MouseState.y;
		 }

// ================================================================
// timer3 Elapsed event: 
// Fires every 20 ms
// Updates angles (to AVR) by incremental values
// ================================================================
private: System::Void timer3_Elapsed(System::Object^  sender, System::Timers::ElapsedEventArgs^  e) {
	int flag_counter = 0;
	if (FLAG_NEW_VALUES)
	{
		this -> timer1 -> Enabled = false;
		for (int i = 0; i < 9; i++)
		{
			if (flags_new_value[i])
			{
				if (angles_to_AVR[i] == final_values[i])
				{
					increments[i] = 0;
					flags_new_value[i] = 0;
					flag_counter ++;
				}
				else
				{
					if ((abs(angles_to_AVR[i]-final_values[i])) < (abs(increments[i])))
					{
						angles_to_AVR[i] = final_values[i];
						increments[i] = 0;
						flags_new_value[i] = 0;
						flag_counter ++;
					}
					else
					{
					angles_to_AVR[i] += increments[i];
					}
				}
			}
			else
			{
				flag_counter ++;
			}
		}

		// Update progress bars
		if ((int)(pbarMF1 -> Value + g_pb_1) > 100000.0f ){ pbarMF1 -> Value = 100000;}
		else {pbarMF1 -> Value = pbarMF1 -> Value + (int)g_pb_1;}
		if ((int)(pbarMF2 -> Value + g_pb_2) > 100000.0f ){ pbarMF2 -> Value = 100000;}
		else {pbarMF2 -> Value = pbarMF2 -> Value + (int)g_pb_2;}
		if ((int)(pbarMF3 -> Value + g_pb_3) > 100000.0f ){ pbarMF3 -> Value = 100000;}
		else {pbarMF3 -> Value = pbarMF3 -> Value + (int)g_pb_3;}

		// Send new data to AVR
		update_Hand(1);

		// If update is done
		if (flag_counter >= 9)
		{
			FLAG_NEW_VALUES = FALSE;
			this -> timer3 -> Enabled = false;
			this -> timer1 -> Enabled = true;
		}
		
	}
}

// ================================================================
// Emergency Button event: 
// Makes the hand go limp
// ================================================================
private: System::Void bEmergencyStop_Click(System::Object^  sender, System::EventArgs^  e) {
		update_Hand(2);
}

// ================================================================
// ComPort combo box selection event: 
// Change index for communication purposes
// ================================================================
private: System::Void cbComPort_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_com_channel = cbComPort -> SelectedIndex;
		 }

// ================================================================
// Communication baud rate combo box selection event: 
// Change index for communication purposes
// ================================================================
private: System::Void cbBaudRate_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_com_baud = cbBaudRate -> SelectedIndex;
		 }

// ================================================================
// Help menu item clicked event: 
// Opens webpage for help
// ================================================================
private: System::Void helpToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
		 System::Diagnostics::Process::Start("http://milagorobets.com/handcontroller/control.php");
}


// ================================================================
// CONFIGURATION FILE
// ================================================================

// ================================================================
// Save Configuration button event: 
// Saves angle values for all phalanges
// ================================================================
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		
		// Write file stream
		StreamWriter^ myStream;
		SaveFileDialog^ saveFile = gcnew SaveFileDialog;
		saveFile -> Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
		saveFile -> FilterIndex = 2;
		saveFile -> RestoreDirectory = true;
		saveFile -> InitialDirectory = txtPathConfig -> Text;

		// Open save file dialog
		if ( saveFile->ShowDialog() == System::Windows::Forms::DialogResult::OK )
		{
			if ( (myStream = gcnew StreamWriter(saveFile->OpenFile())) != nullptr )
			{
				// Write angles to file in order. No speed info written
				myStream -> Write(f_p[0].theta + " " + f_p[1].theta + " " + f_p[2].theta + " " + f_p[4].theta +
					" " + f_p[5].theta + " " + f_p[6].theta + " " + f_p[8].theta + " " + f_p[9].theta + " " + f_p[10].theta);
				
				// Display path to file
				txtPathConfig -> Text = saveFile -> FileName;

				// Closes file stream
				myStream->Close();

				// Display that file write was successful
				lblSaveConfig -> Text = "SAVE OK";
				lblSaveConfig -> ForeColor = System::Drawing::Color::GreenYellow;
			}
			else
			{
				// Display that file write failed
				lblSaveConfig -> Text = "SAVE FAILED";
				lblSaveConfig -> ForeColor = System::Drawing::Color::Maroon;
			}
		}
		else
		{
			// Display that file opening failed
			lblSaveConfig -> Text = "SAVE FAILED";
			lblSaveConfig -> ForeColor = System::Drawing::Color::Maroon;
		}
}

// ================================================================
// Load Configuration button event: 
// Load angle values into model
// ================================================================
private: System::Void btnLoadConfig_Click(System::Object^  sender, System::EventArgs^  e) {
		
		// Open reading stream
		StreamReader^ myStream;
		OpenFileDialog^ openFile = gcnew OpenFileDialog;
		openFile -> Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
		openFile -> FilterIndex = 2;
		openFile -> RestoreDirectory = true;
		if ( openFile -> ShowDialog() == System::Windows::Forms::DialogResult::OK )
		{
			if ( (myStream = gcnew StreamReader(openFile->OpenFile())) != nullptr )
			{
				// Update path field with new file name
				txtPathConfig -> Text = openFile -> FileName;

				// Read line
				System::String^ data_read = myStream->ReadToEnd();
				myStream->Close();

				// Extract values for angles using spaces are indicators
				int data_read_length = data_read -> Length;
				array<int>^ space_positions = gcnew array<int>(8);
				int space_c = 0;

				for (int i = 0; i < data_read_length; i++)
				{
					if (data_read[i] == ' ')
					{
						space_positions[space_c] = i;
						space_c++;
					}
				}
				if (space_c == 8)
				{
					// Parse string into doubles
					System::String^  substring_data = data_read -> Substring(0, space_positions[0]-0);
					double valu = System::Convert::ToDouble(substring_data);
					f_p[0].theta = (GLfloat)valu;

					substring_data = data_read -> Substring((space_positions[0]+1), space_positions[1]-space_positions[0]-1);
					valu = System::Convert::ToDouble(substring_data);
					f_p[1].theta = (GLfloat)valu;

					substring_data = data_read -> Substring((space_positions[1]+1), space_positions[2]-space_positions[1]-1);
					valu = System::Convert::ToDouble(substring_data);
					f_p[2].theta = (GLfloat)valu;

					substring_data = data_read -> Substring((space_positions[2]+1), space_positions[3]-space_positions[2]-1);
					valu = System::Convert::ToDouble(substring_data);
					f_p[4].theta = (GLfloat)valu;

					substring_data = data_read -> Substring((space_positions[3]+1), space_positions[4]-space_positions[3]-1);
					valu = System::Convert::ToDouble(substring_data);
					f_p[5].theta = (GLfloat)valu;

					substring_data = data_read -> Substring((space_positions[4]+1), space_positions[5]-space_positions[4]-1);
					valu = System::Convert::ToDouble(substring_data);
					f_p[6].theta = (GLfloat)valu;

					substring_data = data_read -> Substring((space_positions[5]+1), space_positions[6]-space_positions[5]-1);
					valu = System::Convert::ToDouble(substring_data);
					f_p[8].theta = (GLfloat)valu;

					substring_data = data_read -> Substring((space_positions[6]+1), space_positions[7]-space_positions[6]-1);
					valu = System::Convert::ToDouble(substring_data);
					f_p[9].theta = (GLfloat)valu;

					substring_data = data_read -> Substring((space_positions[7]+1), data_read_length-space_positions[7]-1);
					valu = System::Convert::ToDouble(substring_data);
					f_p[10].theta = (GLfloat)valu;
				}

				// Indicate that load was successful
				lblLoadConfig -> Text = "LOAD OK";
				lblLoadConfig -> ForeColor = System::Drawing::Color::GreenYellow;
			}
			else
			{
				// Indicate that load failed
				lblLoadConfig -> Text = "LOAD FAILED";
				lblLoadConfig -> ForeColor = System::Drawing::Color::Maroon;
			}
		}
		else
		{
			// Indicate that file did not load properly
			lblLoadConfig -> Text = "LOAD FAILED";
			lblLoadConfig -> ForeColor = System::Drawing::Color::Maroon;
		}
}


// ================================================================
// MOTION FILE
// ================================================================

// ================================================================
// Begin Recording button event: 
// Opens file and stores file name for future use
// ================================================================
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		// Writing stream opened
		StreamWriter^ myStream;
		SaveFileDialog^ saveFile = gcnew SaveFileDialog;
		saveFile -> Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
		saveFile -> FilterIndex = 2;
		saveFile -> RestoreDirectory = true;
		System::String^ temp;
		if ( saveFile->ShowDialog() == System::Windows::Forms::DialogResult::OK ){
			
			// Store file name
			temp = saveFile -> FileName;
			motion_file_name = gcnew array<wchar_t>(temp -> Length){L' '};
			motion_file_name = temp -> ToCharArray();

			if ( (myStream = gcnew StreamWriter(gcnew String(motion_file_name))) != nullptr ) 
			{
				// Write "MOTION" to first line to identify file
				myStream -> WriteLine("MOTION");

				// Close stream
				myStream -> Close();

				// Update label to indicate writing successful
				lblBeginRec -> Text = "OK";
				lblBeginRec -> ForeColor = System::Drawing::Color::GreenYellow;

				// Enable "Add configuration", "Add pause", "End recording" buttons
				// Disable "Begin Recording" button
				button3 -> Enabled = false; button3 -> BackColor = System::Drawing::Color::SlateGray;
				bAddPause -> Enabled = true; bAddPause -> BackColor = System::Drawing::Color::LightSteelBlue;
				bAddConfig -> Enabled = true; bAddConfig -> BackColor = System::Drawing::Color::LightSteelBlue;
				bEndRec -> Enabled = true; bEndRec -> BackColor = System::Drawing::Color::LightSteelBlue;
			}
			else
			{
				// Update label: writing failed
				lblBeginRec -> Text = "FAILED";
				lblBeginRec -> ForeColor = System::Drawing::Color::Maroon;
			}
		}
		else
		{
			// Update label: writing failed
			lblBeginRec -> Text = "FAILED";
			lblBeginRec -> ForeColor = System::Drawing::Color::Maroon;
		}
}

// ================================================================
// Add Pause button event: 
// Add a value in ms to pause replay for
// ================================================================
private: System::Void bAddPause_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 // Open writing stream
			 StreamWriter^ myStream;
			 System::String^ path_name = gcnew String(motion_file_name);
			 
			 if ( (myStream = gcnew StreamWriter(path_name, true)) != nullptr ){
				// "W" indicates waiting
				myStream -> WriteLine("W " + txtPause -> Text );
				// Update if write successful
				lblAddPause -> Text = "OK";
				lblAddPause -> ForeColor = System::Drawing::Color::GreenYellow;
			 }
			 else
			 {
				// Update if write fails
				lblAddPause -> Text = "FAILED";
				lblAddPause -> ForeColor = System::Drawing::Color::Maroon;
			 }
			 // Close stream
			 myStream -> Close();
		 }

// ================================================================
// Add Configuration button event: 
// Add angle values and speeds
// ================================================================
private: System::Void bAddConfig_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 // Create writing stream
			 StreamWriter^ myStream;
			 System::String^ path_name = gcnew String(motion_file_name);

			 // Open stream
			 if ((myStream = gcnew StreamWriter(path_name, true)) != nullptr)
			 {
				 if (chk1s -> Checked) // Finger 1: all speeds should be the same
				 {
					myStream -> Write("n " + f_p[0].theta + " " + (trSpeed1 -> Value) + " " +
						f_p[1].theta + " " + (trSpeed1 -> Value) + " " + f_p[2].theta + " " + (trSpeed1 -> Value));
				 }
				 else // Finger 1: use individual speeds
				 {
					myStream -> Write("n " + f_p[0].theta + " " + (tr11s -> Value) + " " +
						f_p[1].theta + " " + (tr12s -> Value) + " " + f_p[2].theta + " " + (tr13s -> Value));
				 }
				 if (chk2s -> Checked) // Finger 2: all speeds should be the same
				 {
					myStream -> Write(" " + f_p[4].theta + " " + (trSpeed2 -> Value) + " " +
						f_p[5].theta + " " + (trSpeed2 -> Value) + " " + f_p[6].theta + " " + (trSpeed2 -> Value));
				 }
				 else // Finger 2: use individual speeds
				 {
					myStream -> Write(" " + f_p[4].theta + " " + (tr21s -> Value) + " " +
						f_p[5].theta + " " + (tr22s -> Value) + " " + f_p[6].theta + " " + (tr23s -> Value));
				 }
				 if (chk3s -> Checked) // Finger 3: all speeds should be the same
				 {
					myStream -> WriteLine(" " + f_p[8].theta + " " + (trSpeed3 -> Value) + " " +
						f_p[9].theta + " " + (trSpeed3 -> Value) + " " + f_p[10].theta + " " + (trSpeed3 -> Value));
				 }
				 else // Finger 3: use individual speeds
				 {
					myStream -> WriteLine(" " + f_p[8].theta + " " + (tr21s -> Value) + " " +
						f_p[9].theta + " " + (tr22s -> Value) + " " + f_p[10].theta + " " + (tr23s -> Value));
				 }

				 // Close stream
				 myStream -> Close();

				 // Update label that write successful
				 lblAddConfig -> Text = "OK";
				 lblAddConfig -> ForeColor = System::Drawing::Color::GreenYellow;
			 }
			 else
			 {
				// Update label that write failed
				lblAddConfig -> Text = "FAILED";
				lblAddConfig -> ForeColor = System::Drawing::Color::Maroon;
			 }
		 }

// ================================================================
// End Recording button event: 
// Change button states
// ================================================================
private: System::Void bEndRec_Click(System::Object^  sender, System::EventArgs^  e) {
			// Enable "Begin Recording" button
			button3 -> Enabled = true; button3 -> BackColor = System::Drawing::Color::LightSteelBlue;

			// Disable "Add Pause", "Add Configuration", "End Recording"
			bAddPause -> Enabled = false; bAddPause -> BackColor = System::Drawing::Color::SlateGray;
			bAddConfig -> Enabled = false; bAddConfig -> BackColor = System::Drawing::Color::SlateGray;
			bEndRec -> Enabled = false; bEndRec -> BackColor = System::Drawing::Color::SlateGray;

			// Successfully ended (shouldn't fail)
			lblEndRec -> Text = "OK";
			lblEndRec -> ForeColor = System::Drawing::Color::GreenYellow;
		 }

// ================================================================
// Load Recording button event: 
// Open recording file, make sure it is a valid motion file
// ================================================================
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
	
	// Start open file dialog
	OpenFileDialog^ openFile = gcnew OpenFileDialog;
	openFile -> Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
	openFile -> FilterIndex = 2;
	openFile -> RestoreDirectory = true;
	System::String^ temp;
	if (openFile -> ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		// Save file name
		temp = openFile -> FileName;
		motion_file_name = gcnew array<wchar_t>(temp -> Length){L' '};
		motion_file_name = temp -> ToCharArray();

		// Update text box with current file name
		txtPathMotion -> Text = temp;

		// Start reading
		if ((myStreamReader = gcnew StreamReader(gcnew String(motion_file_name))) != nullptr)
		{
			// Reading first line
			System::String^ data_read = myStreamReader -> ReadLine();

			// Check if first line is "MOTION"
			if (!String::Compare(data_read, "MOTION", StringComparison::Ordinal))
			{	
				// Show that file is proper and loaded
				lblRecLoaded -> Text = "LOADED OK";
				lblRecLoaded -> ForeColor = System::Drawing::Color::GreenYellow;

				// Initialize background worker for pause routines
				bw = gcnew BackgroundWorker();
				bw->WorkerReportsProgress = true;
				bw->WorkerSupportsCancellation = true;
				bw->ProgressChanged += gcnew ProgressChangedEventHandler( this, &GUI_1::Form1::bw_ProgressChanged );
				bw->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler( this, &GUI_1::Form1::bw_RunWorkerCompleted );
				bw->DoWork += gcnew DoWorkEventHandler( this, &GUI_1::Form1::bw_DoWork );
		
				// Initialize background worker for motion routines
				bw_motion = gcnew BackgroundWorker();
				bw_motion->WorkerReportsProgress = true;
				bw_motion->WorkerSupportsCancellation = true;
				bw_motion->ProgressChanged += gcnew ProgressChangedEventHandler( this, &GUI_1::Form1::motion_ProgressChanged );
				bw_motion->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler( this, &GUI_1::Form1::motion_RunWorkerCompleted );
				bw_motion->DoWork += gcnew DoWorkEventHandler( this, &GUI_1::Form1::motion_DoWork);

				// Indicate that reader is now open
				FLAG_READER_CLOSED = false;		

				// Enable Play Recording button
				bPlayRecording -> Enabled = true; bPlayRecording -> BackColor = System::Drawing::Color::OliveDrab;
			}
			else
			{	
				// Show that file is either improper or did not load
				lblRecLoaded -> Text = "LOAD FAILED";
				lblRecLoaded -> ForeColor = System::Drawing::Color::Maroon;
				bPlayRecording -> Enabled = false; bPlayRecording -> BackColor = System::Drawing::Color::DarkOliveGreen;
				return;
			}
		}
		else 
		{
			// File loading failed
			lblRecLoaded -> Text = "LOAD FAILED";
			lblRecLoaded -> ForeColor = System::Drawing::Color::Maroon;
			bPlayRecording -> Enabled = false; bPlayRecording -> BackColor = System::Drawing::Color::DarkOliveGreen;
			return;
		}
	}
}
		 
// ================================================================
// Play Recording button event: 
// Read the recording file, handle pauses and configurations
// ================================================================
private: System::Void bPlayRecording_Click(System::Object^  sender, System::EventArgs^  e) {
	// Reader still open
	FLAG_READER_CLOSED = false;
	read_file_function();
}


// ================================================================
// FUNCTION PROTOTYPES: SEE SOURCE FILE FOR DEFINITIONS
// ================================================================

// ================================================================
// read_file_function: 
// Read the recording file, handle pauses and configurations
// ================================================================
private: void read_file_function();

// ================================================================
// motion_config: 
// Start bw_motion worker
// ================================================================
private: void motion_config();

// ================================================================
// motion_DoWork: 
// Every 20 ms update angles until motion complete
// ================================================================
private: void motion_DoWork(System::Object^ sender, DoWorkEventArgs^ e);

// ================================================================
// motion_RunWorkerCompleted: 
// Read next line in file
// ================================================================
private: void motion_RunWorkerCompleted(System::Object^ sender, RunWorkerCompletedEventArgs^ e);

// ================================================================
// motion_ProgressChanged: 
// Sends updates to main thread periodically (does nothing here)
// ================================================================
private: void motion_ProgressChanged(System::Object^ sender, ProgressChangedEventArgs^ e);

// ================================================================
// motion_pause: 
// Start bw (pause) worker
// ================================================================
private: void motion_pause(int pause_duration);

// ================================================================
// bw_DoWork: 
// Pause for set amount of time
// ================================================================
private: void bw_DoWork(System::Object^  sender, DoWorkEventArgs^ e );

// ================================================================
// bw_ProgressChanged: 
// Sends updates to main thread periodically (does nothing here)
// ================================================================
private: void bw_ProgressChanged(System::Object^  sender , ProgressChangedEventArgs^ e );

// ================================================================
// bw_RunWorkerCompleted: 
// Return to main thread - read next line in file
// ================================================================
private: void bw_RunWorkerCompleted(System::Object^  sender, RunWorkerCompletedEventArgs^ e );

// ================================================================
// tmr_Tick: 
// Empty (but necessary) timer tick function for BW timers
// ================================================================
private: void tmr_Tick(System::Object^ sender);

// ================================================================
// update_Hand: 
// Send new values to the hand, depends on (source)
// ================================================================
public: int update_Hand(int source);

// ================================================================
// reset_Hand: 
// Resets all degrees to 90 degrees. No effect on speed
// ================================================================
public: void reset_Hand();

// ================================================================
// update_TrackBars: 
// Put current angle values to track bars
// ================================================================
private: void update_TrackBars(int vertex);

// ================================================================
// calc_motion_intervals: 
// Calculate intervals for motion based on angles and speed
// ================================================================
private: void calc_motion_intervals();

// ================================================================
// calculate_servo_intervals: 
// Calculate increments for angles to achieve desired speed
// ================================================================
private: double calculate_servo_intervals(GLfloat speed, GLfloat angle);

// ================================================================
// intervals_set1:
// Responsible for calculating increments for motion of Finger 1
// ================================================================
private: void intervals_set1();

// ================================================================
// intervals_set1:
// Responsible for calculating increments for motion of Finger 2
// ================================================================
private: void intervals_set2();

// ================================================================
// intervals_set1:
// Responsible for calculating increments for motion of Finger 3
// ================================================================
private: void intervals_set3();

private: void update_progress_bars();


}; // end of class def
}
#endif

// Reference class to use OpenGL object
namespace OpenGLForm{ ref class COpenGL; }


