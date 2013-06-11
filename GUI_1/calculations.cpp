// ================================================================

// CALCULATIONS Source File

// ================================================================

#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include < vcclr.h >
#include < stdio.h >
#include < stdlib.h >
#include < vcclr.h >
#include "calculations.h"

// ================================================================
// _calc_count: 
// Calculates number of uController cycles for required degrees
// ================================================================
unsigned int _calc_count(double deg){
	int count = (int)((deg/180)*19999);
	return count;	
}

// ================================================================
// _produce_counts_all: 
// Calculates number of cycles for all 9 servos
// ================================================================
unsigned int * _produce_counts_all(double * data){
	unsigned int * send_char = new unsigned int[19];
	int temp_char, temp_part;
	int c_c;
		c_c = 0;
		for (int i = 0; i < 9; i++){
			int val = _calc_count(data[i]);
			char* pI = (char*)&val;
			char temp = *pI;
			send_char[c_c] = (int)temp + 32; // Low byte first
			pI++;
			temp = *pI;
			send_char[c_c+1] = (int)temp + 32; // High byte second
			c_c += 2;
		}
	return send_char; // Return pointer to count values
}


