#pragma once

#include "DataTupel.h"
#include "IObserver.h"
#include <string>
#include <mutex>
#include <list>
#include <utility>

class DataAssembler : public IObserver {
    public:
        DataTupel getNewDataSample(std::string clockname);
        void addToVector(std::string timeKey, uint32_t absoluteTime, uint32_t referenceFrequency);

    private:
        std::mutex m_time_list_mutex;
        std::list<DataTupel> m_time_list;
};
