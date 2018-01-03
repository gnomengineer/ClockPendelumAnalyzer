#ifndef DATATUPEL_H
#define DATATUPEL_H

#include <string>

class DataTupel {
    public:
        DataTupel(const std::string& name, const std::string& date, uint32_t absoluteTime);
        DataTupel(const std::string& name, const std::string& date, const std::string& absoluteTime);
        DataTupel(const std::string& name, const std::string& date, uint32_t absoluteTime, uint32_t referenceFrequency);
        std::string getClockName() { return m_ClockName;}
        std::string getDate() { return m_Date; }
        uint32_t getAbsoluteTime() { return m_AbsoluteTime; }
        uint32_t getReferenceFrequency() {return m_ReferenceFrequency; }
        int getHeat() { return m_Heat; }
        int getHumidity() { return m_Humidity; }

        void setClockName(const std::string& name);
        void setDate(const std::string date);
        void setAbsoluteTime(uint32_t absoluteTime);
        void setReferenceFrequency(uint32_t frequency);
        void setHeat(int heat);
        void setHumidity(int humidity);

        enum class Tupel{
            CLOCKNAME = 1,
            DATE = 2,
            ABSOLUTETIME = 3,
            REF_FREQUENCY = 4,
            HEAT = 5,
            HUMIDITY = 6
        };

    private:
        std::string m_ClockName;
        std::string m_Date = "20171122151059";
        int m_Heat = 0;
        int m_Humidity = 0;
        uint32_t m_AbsoluteTime = 0;
        uint32_t m_ReferenceFrequency = 0;
};

#endif
