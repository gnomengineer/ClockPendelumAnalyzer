/* ###################################################################
**     Filename    : main.c
**     Project     : tinyK20_Blinky
**     Processor   : MK20DX128VFT5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-11, 13:30, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "WAIT1.h"
#include "RefCnt.h"
#include "KIN1.h"
#include "UTIL1.h"
#include "TGT_SWD_OE.h"
#include "BitIoLdd2.h"
#include "SensorPin.h"
#include "ExtIntLdd1.h"
#include "FixPin.h"
#include "ExtIntLdd2.h"
#include "PPSPin.h"
#include "ExtIntLdd3.h"
#include "GI2C1.h"
#include "I2C1.h"
#include "SDA1.h"
#include "BitIoLdd3.h"
#include "SCL1.h"
#include "BitIoLdd4.h"
#include "CI2C1.h"
#include "CS1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "CLS1.h"
#include "XF1.h"
#include "USB1.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "USB0.h"
#include "TMOUT1.h"
#include "MCUC1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Event.h"
#include "stdbool.h"
static RefCnt_TValueType lastGPSReferenceCounter = 0;
static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];
static uint8_t in_buffer[USB1_DATA_BUFF_SIZE];
static bool usb_connected = 0;

void MAIN_EventHandler(EVNT_Handle event) {
	static RefCnt_TValueType referenceFrequency = 0;
	char buffer[9];
	RefCnt_TValueType counterValue;
	switch(event) {
  	case EVNT_GPS_PULSE_REGISTERED:
  		counterValue = EVENTS_getCounterValue();
  		referenceFrequency = counterValue - lastGPSReferenceCounter;
  		lastGPSReferenceCounter = counterValue;
  		UTIL1_Num32uToStr(buffer, sizeof(buffer), referenceFrequency);
  		if (usb_connected) {
  			CDC1_SendString(buffer);
  			CDC1_SendString("\n\r");
  		}
		break;
	case EVNT_SENSOR_SIGNAL_REGISTERED:
		break;
	default:
  		break;
    /* \todo extend handler as needed */
   } /* switch */
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	 int i, cnt = 0;
	 uint32_t val = 0;
	 unsigned char buf[16];
	 static RefCnt_TValueType* timerHandle;

	  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
		 PE_low_level_init();
	  /*** End of Processor Expert internal initialization.                    ***/

	 for(;;) {
		 while(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF) {
		  /* device not enumerated */
			 WAIT1_Waitms(10);
			 EVNT_HandleEvent(MAIN_EventHandler, TRUE);
			 usb_connected = FALSE;
		 }
		 usb_connected = TRUE;
		 if (CDC1_GetCharsInRxBuf()!=0) {
			 i = 0;
			 while(i<sizeof(in_buffer)-1 && CDC1_GetChar(&in_buffer[i])==ERR_OK) {
				 i++;
			 }
			 in_buffer[i] = '\0';
			 EVNT_HandleEvent(MAIN_EventHandler, TRUE);
	  }
	  else {
		  EVNT_HandleEvent(MAIN_EventHandler, TRUE);
		  WAIT1_Waitms(10);
	  }
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
