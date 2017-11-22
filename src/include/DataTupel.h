#ifndef DATATUPEL_H
#define DATATUPEL_H

#include <string>

class DataTupel {
    public:
        DataTupel();
        DataTupel(std::string name, std::string date, int difference);
        std::string getClockName() { return m_ClockName;}
        std::string getDate() { return m_Date; }
        int getTimeDifference() { return m_TimeDifference; }
        int getHeat() { return m_Heat; }
        int getHumidity() { return m_Humidity; }

        void setClockName(std::string name);
        void setDate(std::string date);
        void setTimeDifference(int difference);
        void setHeat(int heat);
        void setHumidity(int humidity);
    private:
        std::string m_ClockName;
        std::string m_Date = "20171122151059";
        int m_Heat = 0;
        int m_Humidity = 0;
        int m_TimeDifference = 0;

#endif
