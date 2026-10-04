#ifndef CIRCUIT_BUILDERS_H
#define CIRCUIT_BUILDERS_H

class Circuit;
class EventQueue;
class Wire;

/**
 * Builds a 2-input AND Gate using 2 NAND gates.
 */
void buildAndGate(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* out);

/**
 * Builds a 2-input OR Gate using 3 NAND gates (De Morgan's Laws).
 */
void buildOrGate(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* out);

/**
 * Builds a 2-input XOR Gate using 4 NAND gates.
 */
void buildXorGate(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* out);

/**
 * Builds a 1-bit Half Adder by composing XOR (Sum) and AND (Carry).
 */
void buildHalfAdder(Circuit& parent, EventQueue* eq, Wire* inA, Wire* inB, Wire* sum, Wire* carry);

#endif // CIRCUIT_BUILDERS_H
