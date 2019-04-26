/**********************************************************
Company: Dinamica y Desarrollo								
Designed by: Juan Sebastian Rincón Manrique
Date: 04/12/2017
Description: This library manages to communicate with the TTP229 chip from an stm8s003f 
microcontroller, it works with a TTP229 (16-Channel Digital Touch Capacitive Switch Sensor)   
using the 2-wires serial interface protocol - only 2 microcontroller pins.
Dependencies: TTP229.h , Extevents.h
*********************************************************/

/*********************************** CIRCUIT **********************************\
| General:                                                                     |
|	* TTP229 VCC to pin VCC                                                |
|	* TTP229 GND to pin GND                                                |
|	* TTP229 SCL to any pin you choose...                                  |
|	* TTP229 SDO to any pin you choose...                                  |
|                                                                              |
| 16 Buttons Mode (else 8 Buttons Mode):                                       |
|	* TTP229 TP2 to GND via 1 Megohm resistor!                             |
|	# Must use the ReadKey16, GetKeys16... else use the ReadKey8, GetKeys8 |
|                                                                              |
| Important:                                                                   |
|	* Must reconnect the TTP229 power so the mode changes will take effect |
|	* The 1 Megohm resistors already exist on some TTP229 modules          |
\******************************************************************************/

//////////////////////////////////////////////////////////////
//Libraries
//////////////////////////////////////////////////////////////

#include "TTP229.h"

uint8_t _keyPress;
uint8_t bitFlag;
uint8_t count;

/************************************************************
** Timers & interrupt handlers
************************************************************/

#pragma vector = EXTI1_vector
__interrupt void EXTI_PORTB_IRQHandler(void){
  for (unsigned int x = 25;x>0;x--){asm("nop");}; //delay arround 10 microseconds
  Exti1flag = 1;
}

void KBWaitLong(void){
  for (unsigned int x = 5;x>0;x--){asm("nop");}; //this delay uses 20 cycles for clock (arround 10 microseconds)  
}

void SCLWaitShort(void){ //this delay uses 4 cycles for clock (arround 2 microseconds)
  for (unsigned int x = 4;x>0;x--){asm("nop");};
}

/*---------------------------Start init functions------------------------------*/

void TTP_Init(){
  TTP_INIT_MACRO;
  TTP_SCL = 1;
}

//Set up the inernal clock to run at 16 MHz using the HSI
void InitialiseSystemClock(){
    CLK_ICKR = 0;                       //  Reset the Internal Clock Register.
    CLK_ICKR_HSIEN = 1;                 //  Enable the HSI.
    CLK_ECKR = 0;                       //  Disable the external clock.
    while (CLK_ICKR_HSIRDY == 0);       //  Wait for the HSI to be ready for use.
    CLK_CKDIVR = 0;                     //  Ensure the clocks are running at full speed.
    CLK_PCKENR1 = 0xFF;                 //  Enable all peripheral clocks.
    CLK_PCKENR2 = 0xFF;                 //  Ditto.
    CLK_CCOR = 0;                       //  Turn off CCO.
    CLK_HSITRIMR = 0;                   //  Turn off any HSIU trimming.
    CLK_SWIMCCR = 0;                    //  Set SWIM to run at clock / 2.
    CLK_SWR = 0xE1;                     //  Use HSI as the clock source.
    CLK_SWCR = 0;                       //  Reset the clock switch control register.
    CLK_SWCR_SWEN = 1;                  //  Enable switching.
    while (CLK_SWCR_SWBSY != 0);        //  Pause while the clock switch is busy.
}

/*-----------------------------End init functions------------------------------*/

uint8_t ReadKey(){
  key();
  return _keyPress;
  bitFlag = 0;
}

void key(){
  count = 0;
  for (uint8_t i = 0; i < 16; i++){
    GetBit();
    if (bitFlag == 1 && TTP_SDOVAL == 1){ 
      count = i + 1; 
    }
    else{
      i = 16;
      _keyPress = count + 1;
      if (_keyPress < 1 || _keyPress > 16){
        _keyPress = 0;
      }
    }
  }
}

void GetBit(){
  TTP_SCL = 0;
  SCLWaitShort();
  TTP_SCL ^= TTP_SDOVAL;
  bitFlag = TTP_SCL;
  TTP_SCL = 1;
  SCLWaitShort();
}