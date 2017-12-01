#include "Analyzer.h"
#include "DataTupel.h"
#include <string>

class DataAssembler {
    public:
        DataTupel getNewDataSample(std::string clockname);

    private:
        Analyzer m_Analyzer;
};
