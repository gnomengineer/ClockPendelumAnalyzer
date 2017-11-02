//
// Created by tobias on 26.10.17.
//

#ifndef CLOCKPENDELUMANALYZER_RTCMODULE_H
#define CLOCKPENDELUMANALYZER_RTCMODULE_H

#include "../include/GPIO.h"

class RTCModule {
public:

    RTCModule();
    ~RTCModule();

    void readReferenceFrequency();

    static void* startRTCthread(void* rtcPointer);

    void stopThread();

private:

    GPIO* m_refFreqIn;
    bool m_Error;
    bool m_Running;
};

#endif //CLOCKPENDELUMANALYZER_RTCMODULE_H
