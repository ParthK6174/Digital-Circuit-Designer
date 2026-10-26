#ifndef CIRCUIT_BUILDERS_H
#define CIRCUIT_BUILDERS_H

class Circuit;
class EventQueue;
class Wire;

/**
 * Builds a 1-input NOT Gate using 1 NAND gate.
 */
void buildNotGate(Circuit& parent, EventQueue* eq, Wire* in, Wire* out);

/**
 * Builds a 2-input AND Gate using 2 NAND gates.
 */
void buildAndGate(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* out);

/**
 * Builds a 2-input OR Gate using 3 NAND gates (De Morgan's Laws).
 */
void buildOrGate(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* out);

/**
 * Builds a 2-input NOR Gate using 4 NAND gates (OR followed by NOT).
 */
void buildNorGate(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* out);

/**
 * Builds a 2-input XOR Gate using 4 NAND gates.
 */
void buildXorGate(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* out);

/**
 * Builds a 2-to-1 Multiplexer using 4 NAND gates.
 * Logic: out = (sel == 0) ? in0 : in1
 */
void buildMux2to1(Circuit& parent, EventQueue* eq, Wire* sel, Wire* in0, Wire* in1, Wire* out);

/**
 * Builds a 1-bit Half Adder by composing XOR (Sum) and AND (Carry).
 */
void buildHalfAdder(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* sum, Wire* carry);

/**
 * Builds a 1-bit Full Adder by composing two Half Adders and an OR gate.
 */
void buildFullAdder(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* cin, Wire* sum, Wire* cout);

/**
 * Builds a 2-bit Combinational Shifter using 2:1 Multiplexers.
 * Shift=0: out1 = in1, out0 = in0 (pass-through)
 * Shift=1: out1 = in0, out0 = 0   (left shift by 1 with zero-fill)
 */
void buildShifter(Circuit& parent, EventQueue* eq, Wire* shift, Wire* in0, Wire* in1, Wire* out0, Wire* out1);

#endif // CIRCUIT_BUILDERS_H
