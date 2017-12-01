#ifndef IDATATPERSISTOR_H
#define IDATATPERSISTOR_H

#include "DataTupel.h"
#include <string>
#include <list>

class IDataPersistor {
public:
    virtual std::list<DataTupel> getDataByName(const std::string& name) = 0;
    virtual std::list<DataTupel> getDataByDate(const std::string& date) = 0;
    virtual int saveData(DataTupel data) = 0;
    virtual int saveDataList(std::list<DataTupel> data) = 0;
};

#endif
