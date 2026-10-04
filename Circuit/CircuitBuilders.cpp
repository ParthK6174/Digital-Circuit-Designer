#include "CircuitBuilders.h"
#include "Circuit.h"
#include "Wire.h"
#include "Gate.h"

void buildAndGate(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* out) {
    Wire* w_nand1_out = parent.createWire("AND_Internal_N1", eq, true);

    parent.createNandGate(inA, inB, w_nand1_out);
    parent.createNandGate(w_nand1_out, w_nand1_out, out);
}

void buildOrGate(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* out) {
    Wire* w_notA = parent.createWire("OR_Internal_NotA", eq, true);
    Wire* w_notB = parent.createWire("OR_Internal_NotB", eq, true);

    parent.createNandGate(inA, inA, w_notA);
    parent.createNandGate(inB, inB, w_notB);
    parent.createNandGate(w_notA, w_notB, out);
}

void buildXorGate(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* out) {
    Wire* w_nand1_out = parent.createWire("XOR_Internal_N1", eq, true);
    Wire* w_nand2_out = parent.createWire("XOR_Internal_N2", eq, true);
    Wire* w_nand3_out = parent.createWire("XOR_Internal_N3", eq, true);

    parent.createNandGate(inA, inB, w_nand1_out);           // Stage 1
    parent.createNandGate(inA, w_nand1_out, w_nand2_out);   // Stage 2 (top)
    parent.createNandGate(inB, w_nand1_out, w_nand3_out);   // Stage 2 (bottom)
    parent.createNandGate(w_nand2_out, w_nand3_out, out);   // Stage 3 (output)
}

void buildHalfAdder(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* sum, Wire* carry) {
    buildXorGate(parent, eq, inA, inB, sum);
    buildAndGate(parent, eq, inA, inB, carry);
}
