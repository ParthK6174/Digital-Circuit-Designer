#ifndef CIRCUIT_ELEMENT_H
#define CIRCUIT_ELEMENT_H

/**
 * Abstract base class representing any evaluatable component in the simulator.
 */
class CircuitElement {
public:
    virtual ~CircuitElement() = default;

    /**
     * Pure virtual method called by the EventQueue to update output states.
     */
    virtual void evaluate() = 0;
};

#endif // CIRCUIT_ELEMENT_H
