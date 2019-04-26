 /********************************************************
 Company: Dinámica y Desarrollo
 Designed by: Juan Sebastían Rincón Manrique 
 Date: 19/10/2017
 Description: in this code are created the interrupt flags
 Dependencies: Extevents.h
 *********************************************************/

#ifndef _EXTEVENTS_H
#define _EXTEVENTS_H
#include "DataType.h"
 

typedef union {
	uint8_t Flag;	    	// Access all register
	struct {
		uint8_t Exti0	    :1;	// Access to bit 0
		uint8_t Exti1	    :1;	// Access to bit 1
		uint8_t Exti2	    :1;	// Access to bit 2
		uint8_t Exti3       :1; // Access to bit 3
		uint8_t Exti4	    :1;	// Access to bit 4

} Bits;
} STR_FLAGS;

extern volatile STR_FLAGS _INT_Extevents;
 
#define INT_EXTVENTS     _INT_Extevents.Flag            // All register
#define	Exti0flag        _INT_Extevents.Bits.Exti0      // Bit 0
#define	Exti1flag        _INT_Extevents.Bits.Exti1      // Bit 1
#define	Exti2flag        _INT_Extevents.Bits.Exti2      // Bit 2
#define	Exti3flag        _INT_Extevents.Bits.Exti3      // Bit 3
#define	Exti4flag        _INT_Extevents.Bits.Exti4      // Bit 3
 
#endif
