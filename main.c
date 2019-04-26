#include <iostm8s003f3.h>
#include <intrinsics.h>
#include "DataType.h"
#include "TTP229.h"

uint8_t u8Tecla = 0;

int main( void ){
  __disable_interrupt();
  InitialiseSystemClock();
  TTP_Init();
  __enable_interrupt();
  while(1){
    if (Exti1flag == 1){
      u8Tecla = ReadKey();
      Exti1flag = 0;
    }
  __halt();
  }
}