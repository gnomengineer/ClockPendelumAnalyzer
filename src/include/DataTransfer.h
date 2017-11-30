#ifndef DATATRANSFER_H
#define DATATRANSFER_H

#include "IDBConnector.h"
#include "IDataPersistor.h"
#include <list>
#include <string>

class DataTransfer {
    public:
        DataTransfer();
        ~DataTransfer();
        std::list<DataTupel> getDataListByName(std::string name);
        std::list<DataTupel> getDataListByDate(std::string date);
        bool saveDataList(std::list<DataTupel> data);
    private:
        std::list<DataTupel> m_DataList;
        IDataPersistor* m_Persistor;
        IDBConnector* m_Connector;
};

#endif
