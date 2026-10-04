#ifndef CSV_OUTPUT_H
#define CSV_OUTPUT_H

#include <fstream>
#include <string>
#include "OutputDisplay.h"

/**
 * Concrete OutputDisplay implementation exporting readings to a CSV file.
 */
class CSVOutput : public OutputDisplay {
private:
    std::ofstream file;
    std::string filename;

public:
    explicit CSVOutput(const std::string& outFilename = "simulation_results.csv");
    ~CSVOutput() override;

    void initHeader();
    void recordStep(int stepId) override;
};

#endif // CSV_OUTPUT_H
