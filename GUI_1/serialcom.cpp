// ================================================================

// SERIAL COMMUNICATION Source File

// ================================================================

#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include < vcclr.h >
#include < stdio.h >
#include < stdlib.h >
#include < vcclr.h >
#include "serialcom.h"

int g_com_channel; // COM port on the computer
int g_com_baud; // Communication baud rate

// ================================================================
// SerialCommunication: 
// Creates instance of object (completely empty)
// ================================================================
SerialCommunication::SerialCommunication(){}

// ================================================================
// SerialWrite: 
// Writes string of data to proper com port at baud rate
// ================================================================
int SerialCommunication::SerialWrite(unsigned int * datar){

	DCB dcb;
	DWORD byteswritten;
	wchar_t route[5];

	switch (g_com_channel){ // Check what COM port user wants to use
		case 0: wcscpy_s(route, 5, L"COM1"); break;
		case 1: wcscpy_s(route, 5, L"COM2"); break;
		case 2: wcscpy_s(route, 5, L"COM3"); break;
		case 3: wcscpy_s(route, 5, L"COM4"); break;
		case 4: wcscpy_s(route, 5, L"COM5"); break;
		case 5: wcscpy_s(route, 5, L"COM6"); break;
	}	
	
	// Create a handle to a file to write in
	HANDLE hPort = CreateFile(
			route,
			GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL
			);

	// Check if file doesn't create
	if (!GetCommState(hPort,&dcb))
	return false;

	dcb.BaudRate = CBR_19200; // Not default! If g_com_baud never initializes
	switch (g_com_baud){ // Check communication baud rate that user wants
		case 0: dcb.BaudRate = CBR_4800; break; 
		case 1: dcb.BaudRate = CBR_9600; break;
		case 2: dcb.BaudRate = CBR_19200; break; 
		case 3: dcb.BaudRate = CBR_38400; break;
		case 4: dcb.BaudRate = CBR_57600; break;
	}
	
	dcb.ByteSize = 8; // 8 data bits
	dcb.Parity = NOPARITY; // no parity
	dcb.StopBits = ONESTOPBIT; // 1 stop bit

	// If changing settings doesn't work
	if (!SetCommState(hPort,&dcb))
	return false;

	// Create a copy of received data
	char * data_t = new char[19];
		for (int i=0; i<19;i++){
		data_t[i] = datar[i];	
	}


	// hPort = handle to comm line
	// data_t = data to send
	// sizeof(char)*19 = number of bytes to write
	// byteswritten = place to store number of bytes actually written
	int retVal = WriteFile(hPort,(LPVOID)data_t,sizeof(char)*19,&byteswritten,NULL);
	
	CloseHandle(hPort); // Close the handle

	delete[] data_t; // Clear memory
	return retVal;
}
