/*
 * Event.h
 *
 *  Created on: 20 Dec 2017
 *      Author: tobias
 */

#ifndef SOURCES_EVENT_H_
#define SOURCES_EVENT_H_
#include <stdbool.h> /* for bool type */

typedef enum EVNT_Handle {
  EVNT_STARTUP,            /*!< System startup Event */
  EVNT_GPS_PULSE_REGISTERED,     /*!< Frequency reference signal interrupt registered */
  EVNT_SENSOR_SIGNAL_REGISTERED, /*!< Pendulum sensor signal registered */
  /*!< \todo Your extra events here */
  EVNT_NOF_EVENTS       /*!< Must be last one! */
} EVNT_Handle;

/*!
 * \brief Sets an event.
 * \param[in] event The handle of the event to set.
 */
void EVNT_SetEvent(EVNT_Handle event);

/*!
 * \brief Routine to check if an event is pending. If an event is pending, the event is cleared and the provided callback is called.
 * \param[in] callback Callback routine to be called. The event handle is passed as argument to the callback.
 * \param[in] clearEvent If TRUE, it will clear the event in the EVNT_HandleEvent(), otherwise not.
 */
void EVNT_HandleEvent(void (*callback)(EVNT_Handle), bool clearEvent);

/*! \brief Event module initialization */
void EVNT_Init(void);

/*! \brief Event module de-initialization */
void EVNT_Deinit(void);

#endif /* SOURCES_EVENT_H_ */
