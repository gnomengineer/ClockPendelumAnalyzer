#ifndef SQLITEIMPLEMENTATION_H
#define SQLITEIMPLEMENTATION_H

#include "DataTupel.h"
#include "IDBConnector.h"
#include "IDataPersistor.h"
#include <list>
#include <string>
#include <sqlite3.h>

class SQLiteImplementation : public IDBConnector, public IDataPersistor {
    public:
        ~SQLiteImplementation();
        void connect(std::string uri);
        void disconnect();
        std::list<DataTupel> getDataByDate(const std::string& date);
        std::list<DataTupel> getDataByName(const std::string& name);
        void saveData(DataTupel data);
        void saveDataList(std::list<DataTupel> data);
        static int addToList(void* info,
                int numberOfRows, char** data, char** columnNames);
    private:
        const std::string TABLE = "clocktable";
        void printSQLiteError();
        void printSQLError();
        void createTableOnce();
        sqlite3* m_DataBase;
        int m_ErrorCode = 0;
        char* m_SQLErrorMessage = 0;
};

#endif 
