#ifndef OUTPUT_DISPLAY_H
#define OUTPUT_DISPLAY_H

#include <vector>
#include "Wire.h"

/**
 * @brief Abstract base class for recording and visualizing simulation outputs.
 */
class OutputDisplay {
protected:
    std::vector<Wire*> watchedWires;

public:
    virtual ~OutputDisplay() = default;

    /**
     * @brief Adds a wire to the list of watched signals.
     */
    void watchWire(Wire* w) {
        if (w != nullptr) {
            watchedWires.push_back(w);
        }
    }

    /**
     * @brief Pure virtual method to record the circuit state at a given step.
     */
    virtual void recordStep(int stepId) = 0;
};

#endif // OUTPUT_DISPLAY_H
