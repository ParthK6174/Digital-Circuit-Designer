#ifndef OUTPUT_DISPLAY_H
#define OUTPUT_DISPLAY_H

#include <vector>
#include "Wire.h"

/**
 * Abstract base class for recording and visualizing simulation outputs.
 */
class OutputDisplay {
protected:
    std::vector<Wire*> watchedWires;

public:
    virtual ~OutputDisplay() = default;

    void watchWire(Wire* wire) {
        if (wire != nullptr) {
            watchedWires.push_back(wire);
        }
    }

    virtual void recordStep(int stepId) = 0;
};

#endif // OUTPUT_DISPLAY_H
