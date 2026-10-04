#ifndef CSV_OUTPUT_H
#define CSV_OUTPUT_H

#include <fstream>
#include <string>
#include "OutputDisplay.h"

/**
 * @brief Concrete OutputDisplay implementation exporting readings to a CSV file.
 */
class CSVOutput : public OutputDisplay {
private:
    std::ofstream file;
    std::string filename;

public:
    explicit CSVOutput(const std::string& outFilename = "simulation_results.csv");
    ~CSVOutput() override;

    /**
     * @brief Writes the CSV header row containing "Step" and names of all watched wires.
     */
    void initHeader();

    /**
     * @brief Records a new CSV row containing the stepId and boolean states of watched wires.
     */
    void recordStep(int stepId) override;
};

#endif // CSV_OUTPUT_H
