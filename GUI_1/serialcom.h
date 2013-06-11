// ================================================================

// SERIAL COMMUNICATION Header File

// ================================================================

#include "stdafx.h"
#ifndef serialcommunication
#define serialcommunication

extern int g_com_channel; // COM port on the computer
extern int g_com_baud; // Communication baud rate

using namespace System;

public class SerialCommunication{

	private:			
	public:
		// Default constructor
		SerialCommunication();

		// Writing function
		int SerialWrite(unsigned int *);
};

#endif