#ifndef SQLITEIMPLEMENTATION_H
#define SQLITEIMPLEMENTATION_H

#include "DataTupel.h"
#include <list>
#include <string>

class SQLiteImplementation : public IDBConnector, public IDataPersistor {
    public:
        ~SQLiteImplementation();
        void connect(std::string uri);
        void disconnect();
        std::list<DataTupel> getDataByDate(const std::string& date);
        std::list<DataTupel> getDataByName(const std::string& name);
        void saveData(DataTupel data);
        void saveDataList(std::list<DataTupel> data);
    private:
        //sqlite
};

#endif 
