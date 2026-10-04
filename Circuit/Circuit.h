#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <vector>
#include <string>
#include <utility>
#include "CircuitElement.h"
#include "Wire.h"
#include "Gate.h"

class EventQueue;

/**
 * Composite container acting as the lifecycle/memory manager for all
 * dynamically allocated wires and gates. Prevents memory leaks upon destruction.
 */
class Circuit {
private:
    std::vector<CircuitElement*> elements;
    std::vector<Wire*> internalWires;

public:
    Circuit() = default;

    // Disallow copying to prevent double-free errors
    Circuit(const Circuit&) = delete;
    Circuit& operator=(const Circuit&) = delete;

    // Allow moving
    Circuit(Circuit&& other) noexcept;
    Circuit& operator=(Circuit&& other) noexcept;

    ~Circuit();

    void clear();

    Wire* createWire(const std::string& name, EventQueue* eq, bool initialState = false);
    Wire* createWire(EventQueue* eq, bool initialState = false, const std::string& name = "Wire");
    NandGate* createNandGate(Wire* in1, Wire* in2, Wire* out);

    template <typename T, typename... Args>
    T* createElement(Args&&... args) {
        T* elem = new T(std::forward<Args>(args)...);
        elements.push_back(elem);
        return elem;
    }
};

#endif // CIRCUIT_H
