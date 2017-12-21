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
        void addToVector(std::string timeKey, int absoluteTimeValue);

    private:
        std::mutex m_time_list_mutex;
        std::list<std::pair<std::string,int>> m_time_list;
};
