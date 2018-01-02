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
#include "Event.h"

#ifdef __cplusplus
extern "C" {
#endif 

#define MAX_COUNTER_VALUE 65536

static int overrunCntr = 0;
static int ppsIsAlive = 0;
static RefCnt_TValueType referenceCounterGPS = 0;
static RefCnt_TValueType clockPendulumCounter = 0;
static RefCnt_TValueType lastCnt = 0;
static LDD_TDeviceData* timerHandle;

/* User includes (#include below this line is not maintained by Processor Expert) */

RefCnt_TValueType EVENTS_getCounterValue() {
	return referenceCounterGPS;
}

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
	clockPendulumCounter = RefCnt_GetCounterValue(timerHandle) + overrunCntr * MAX_COUNTER_VALUE;
	EVNT_SetEvent(EVNT_SENSOR_SIGNAL_REGISTERED);
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
	referenceCounterGPS = RefCnt_GetCounterValue(timerHandle) + overrunCntr * MAX_COUNTER_VALUE;
	EVNT_SetEvent(EVNT_GPS_PULSE_REGISTERED);
	ppsIsAlive = 2;
	LED1_Neg();
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
	static RefCnt_TValueType diff = 0;
	if (ppsIsAlive > 0) {
		--ppsIsAlive;
	}
	else {
		referenceCounterGPS = RefCnt_GetCounterValue(timerHandle) + overrunCntr * MAX_COUNTER_VALUE;
		EVNT_SetEvent(EVNT_GPS_PULSE_REGISTERED);
		LED1_Neg();
	}
}

/*
** ===================================================================
**     Event       :  CI2C1_OnSlaveBlockSent (module Events)
**
**     Component   :  CI2C1 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when I2C in slave mode finishes the
**         transmission of the data successfully. This event is not
**         available for the MASTER mode and if SlaveSendBlock is
**         disabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void CI2C1_OnSlaveBlockSent(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  CI2C1_OnSlaveBlockReceived (module Events)
**
**     Component   :  CI2C1 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when I2C in slave mode finishes the
**         reception of the data successfully. This event is not
**         available for the MASTER mode and if SlaveReceiveBlock is
**         disabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void CI2C1_OnSlaveBlockReceived(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  RefCnt_OnCounterRestart (module Events)
**
**     Component   :  RefCnt [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void RefCnt_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	overrunCntr++;
}

/*
** ===================================================================
**     Event       :  AS1_OnError (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnRxChar(void)
{
  /* Write your code here ... */
	LED1_Neg();
}

/*
** ===================================================================
**     Event       :  AS1_OnTxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnFullRxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnFullRxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnFreeTxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnFreeTxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  ResetCnt_OnInterrupt (module Events)
**
**     Component   :  ResetCnt [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ResetCnt_OnInterrupt(void)
{
	RefCnt_ResetCounter(timerHandle);
	overrunCntr = 0;
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
