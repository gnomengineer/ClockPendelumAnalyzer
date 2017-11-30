/* ###################################################################
**     Filename    : Events.c
**     Project     : tinyK20_Blinky
**     Processor   : MK20DX128VFT5
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-11, 13:30, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 

static int overrunCntr = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK20DX128EX5]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  SensorPin_OnInterrupt (module Events)
**
**     Component   :  SensorPin [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SensorPin_OnInterrupt(void)
{
	LED1_Neg();
	/* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  PPSPin_OnInterrupt (module Events)
**
**     Component   :  PPSPin [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PPSPin_OnInterrupt(void)
{
	LED1_Neg();
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  FixPin_OnInterrupt (module Events)
**
**     Component   :  FixPin [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FixPin_OnInterrupt(void)
{
	static LDD_TDeviceData* timerHandle;
	static FC1_TValueType cnt = 0;
	static FC1_TValueType lastCnt = 0;
	static FC1_TValueType diff = 0;
	LED1_Neg();
	lastCnt = cnt;
	cnt = FC1_GetCounterValue(timerHandle);
	diff = cnt - lastCnt;

  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  FC1_OnInterrupt (module Events)
**
**     Component   :  FC1 [FreeCntr_LDD]
*/
/*!
**     @brief
**         This event is called when a compare matches the counter
**         value (if compare or reload is selected as a interrupt
**         source) or a counter overflows (for free-running devices).
**         Component and OnInterrupt event must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt service/event] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void FC1_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	overrunCntr++;
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
