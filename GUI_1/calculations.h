// ================================================================

// CALCULATIONS Header File

// ================================================================

#include "stdafx.h"
#ifndef calculations
#define calculations

// ================================================================
// _calc_count: 
// Calculates number of uController cycles for required degrees
// ================================================================
unsigned int _calc_count(double deg);

// ================================================================
// _produce_counts_all: 
// Calculates number of cycles for all 9 servos
// ================================================================
unsigned int * _produce_counts_all(double * data);

#endif
