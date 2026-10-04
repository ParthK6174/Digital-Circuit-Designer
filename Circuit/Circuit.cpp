#include "Circuit.h"
#include "EventQueue.h"

Circuit::Circuit(Circuit&& other) noexcept
    : elements(std::move(other.elements)), internalWires(std::move(other.internalWires)) {}

Circuit& Circuit::operator=(Circuit&& other) noexcept {
    if (this != &other) {
        clear();
        elements = std::move(other.elements);
        internalWires = std::move(other.internalWires);
    }
    return *this;
}

Circuit::~Circuit() {
    clear();
}

void Circuit::clear() {
    for (CircuitElement* elem : elements) {
        delete elem;
    }
    elements.clear();

    for (Wire* wire : internalWires) {
        delete wire;
    }
    internalWires.clear();
}

Wire* Circuit::createWire(const std::string& name, EventQueue* eq, bool initialState) {
    Wire* wire = new Wire(name, eq, initialState);
    internalWires.push_back(wire);
    return wire;
}

Wire* Circuit::createWire(EventQueue* eq, bool initialState, const std::string& name) {
    Wire* wire = new Wire(name, eq, initialState);
    internalWires.push_back(wire);
    return wire;
}

NandGate* Circuit::createNandGate(Wire* in1, Wire* in2, Wire* out) {
    NandGate* gate = new NandGate(in1, in2, out);
    elements.push_back(gate);
    return gate;
}
