#ifndef GATE_H
#define GATE_H

#include "CircuitElement.h"
#include "Wire.h"

/**
 Abstract base class for logic gates.
 Automatically registers itself as a listener to its input wires in the constructor.
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

class NandGate : public Gate { // output = !(input1 && input2)
public:
    NandGate(Wire* input1, Wire* input2, Wire* output);
    void evaluate() override;
};

#endif // GATE_H
