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
        int saveData(DataTupel data);
        int saveDataList(std::list<DataTupel> data);
        static int addToList(void* info,
                int numberOfRows, char** data, char** columnNames);
    private:
        const std::string TABLE = "clocktable";
        void printSQLiteError(const std::string errorOccurence = "");
        void printSQLError();
        void createTableOnce();
        void getData(const std::string& key, const std::string& value);

        std::list<DataTupel> m_Result;
        sqlite3* m_DataBase;
        int m_ErrorCode = 0;
        char* m_SQLErrorMessage = 0;
};

#endif 
