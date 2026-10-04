#ifndef WIRE_H
#define WIRE_H

#include <string>
#include <vector>

class CircuitElement;
class EventQueue;

/**
 * @brief Represents an electrical connection wire carrying a boolean state.
 * Implements the Observer pattern: when state changes, it schedules registered listeners.
 */
class Wire {
private:
    std::string name;
    bool state;
    EventQueue* eventQueue;
    std::vector<CircuitElement*> listeners;

public:
    Wire(const std::string& wireName, EventQueue* eq, bool initialState = false);
    Wire(EventQueue* eq, bool initialState = false, const std::string& wireName = "Wire");

    /**
     * @brief Subscribes a downstream CircuitElement to observe state changes on this wire.
     */
    void addListener(CircuitElement* element);

    /**
     * @brief Sets the wire's signal value. Schedules listeners only on actual state transition.
     */
    void set(bool val);

    /**
     * @brief Retrieves current binary state of the wire.
     */
    bool get() const;

    /**
     * @brief Retrieves wire identifier name.
     */
    const std::string& getName() const;
};

#endif // WIRE_H
