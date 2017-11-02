//
// Created by tobias on 26.10.17.
//
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include "../include/RTCModule.h"
//#include <unistd.h>
#include <iostream>

RTCModule::RTCModule()
    : m_Error(false)
    , m_Running(true) {
    m_refFreqIn = new GPIO("23");
    m_refFreqIn->setDirection(GPIO::INPUT);
}

RTCModule::~RTCModule() {
    delete m_refFreqIn;
}

void RTCModule::readReferenceFrequency() {
    while(m_Running) {
        std::cout << std::to_string(m_refFreqIn->readValue()) << std::endl;
    }
}

void *RTCModule::startRTCthread(void *rtcPointer) {
    auto* me = static_cast<RTCModule*>(rtcPointer);
    me->readReferenceFrequency();
    pthread_exit(me);
}

void RTCModule::stopThread() {
    m_Running = false;
}



