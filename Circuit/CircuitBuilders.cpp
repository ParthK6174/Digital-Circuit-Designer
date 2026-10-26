#include "CircuitBuilders.h"
#include "Circuit.h"
#include "Wire.h"
#include "Gate.h"

void buildNotGate(Circuit& parent, EventQueue* eq, Wire* in, Wire* out) {
    (void)eq;
    parent.createNandGate(in, in, out);
}

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

void buildNorGate(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* out) {
    Wire* w_or = parent.createWire("NOR_Internal_OR", eq, false);
    buildOrGate(parent, eq, inA, inB, w_or);
    buildNotGate(parent, eq, w_or, out);
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

void buildMux2to1(Circuit& parent, EventQueue* eq, Wire* sel, Wire* in0, Wire* in1, Wire* out) {
    Wire* w_not_sel = parent.createWire("MUX_Internal_NotSel", eq, true);
    Wire* w_nand0 = parent.createWire("MUX_Internal_N0", eq, true);
    Wire* w_nand1 = parent.createWire("MUX_Internal_N1", eq, true);

    buildNotGate(parent, eq, sel, w_not_sel);
    parent.createNandGate(in0, w_not_sel, w_nand0);
    parent.createNandGate(in1, sel, w_nand1);
    parent.createNandGate(w_nand0, w_nand1, out);
}

void buildHalfAdder(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* sum, Wire* carry) {
    buildXorGate(parent, eq, inA, inB, sum);
    buildAndGate(parent, eq, inA, inB, carry);
}

void buildFullAdder(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* cin, Wire* sum, Wire* cout) {
    Wire* w_ha1_sum = parent.createWire("FA_Internal_HA1_Sum", eq, false);
    Wire* w_ha1_carry = parent.createWire("FA_Internal_HA1_Carry", eq, false);
    Wire* w_ha2_carry = parent.createWire("FA_Internal_HA2_Carry", eq, false);

    buildHalfAdder(parent, eq, inA, inB, w_ha1_sum, w_ha1_carry);
    buildHalfAdder(parent, eq, w_ha1_sum, cin, sum, w_ha2_carry);
    buildOrGate(parent, eq, w_ha1_carry, w_ha2_carry, cout);
}

void buildShifter(Circuit& parent, EventQueue* eq, Wire* shift, Wire* in0, Wire* in1, Wire* out0, Wire* out1) {
    Wire* w_zero = parent.createWire("Shifter_Internal_Zero", eq, false);

    // When shift is 0, out0 = in0; when shift is 1, out0 = 0 (left shift zero fill)
    buildMux2to1(parent, eq, shift, in0, w_zero, out0);
    // When shift is 0, out1 = in1; when shift is 1, out1 = in0 (shift in0 into MSB position)
    buildMux2to1(parent, eq, shift, in1, in0, out1);
}
