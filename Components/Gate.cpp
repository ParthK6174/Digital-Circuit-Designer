#include "Gate.h"

Gate::Gate(Wire* input1, Wire* input2, Wire* output)
    : in1(input1), in2(input2), out(output) {
    if (in1 != nullptr) {
        in1->addListener(this);
    }
    if (in2 != nullptr) {
        in2->addListener(this);
    }
}

NandGate::NandGate(Wire* input1, Wire* input2, Wire* output)
    : Gate(input1, input2, output) {}

void NandGate::evaluate() {
    bool val1 = in1 ? in1->get() : false;
    bool val2 = in2 ? in2->get() : false;
    bool result = !(val1 && val2);

    if (out != nullptr) {
        out->set(result);
    }
}
