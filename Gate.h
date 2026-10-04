#ifndef GATE_H
#define GATE_H

#include "CircuitElement.h"
#include "Wire.h"

/**
 * @brief Abstract base class for logic gates.
 * Automatically registers itself as a listener to its input wires in the constructor.
 */
class Gate : public CircuitElement {
protected:
    Wire* in1;
    Wire* in2;
    Wire* out;

public:
    Gate(Wire* input1, Wire* input2, Wire* output);
    virtual ~Gate() = default;
};

/**
 * @brief Concrete 2-input NAND Gate.
 * Logic: out = !(in1 && in2)
 */
class NandGate : public Gate {
public:
    NandGate(Wire* input1, Wire* input2, Wire* output);
    void evaluate() override;
};

#endif // GATE_H
