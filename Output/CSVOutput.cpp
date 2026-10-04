#include "CSVOutput.h"

#include <iostream>

CSVOutput::CSVOutput(const std::string& outFilename)
    : filename(outFilename) {
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open CSV output file: " << filename << "\n";
    }
}

CSVOutput::~CSVOutput() {
    if (file.is_open()) {
        file.flush();
        file.close();
    }
}

void CSVOutput::initHeader() {
    if (!file.is_open()) {
        return;
    }

    file << "Step";
    for (const Wire* wire : watchedWires) {
        file << "," << (wire ? wire->getName() : "Unknown");
    }
    file << "\n";
    file.flush();
}

void CSVOutput::recordStep(int stepId) {
    if (!file.is_open()) {
        return;
    }

    file << stepId;
    for (const Wire* wire : watchedWires) {
        file << "," << (wire ? wire->get() : 0);
    }
    file << "\n";
    file.flush();
}
