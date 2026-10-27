#include "Wire.h"
#include "EventQueue.h"
#include "CircuitElement.h"

Wire::Wire(const std::string& wireName, EventQueue* eq, bool initialState)
    : name(wireName), state(initialState), eventQueue(eq) {}

Wire::Wire(EventQueue* eq, bool initialState, const std::string& wireName)
    : name(wireName), state(initialState), eventQueue(eq) {}

void Wire::addListener(CircuitElement* element) {
    if (element != nullptr) {
        listeners.push_back(element);
    }
}
//listener will then contain all the gates connected to that particular wire

void Wire::set(bool val) {
    if (val != state)//checks whetere the state is updated or not 
    {
        state = val; //updates the state
        if (eventQueue != nullptr) {
            for (CircuitElement* listener : listeners) {
                eventQueue->schedule(listener);
            }
        }
    }
}


bool Wire::get() const {
    return state;
}

const std::string& Wire::getName() const {
    return name;
}
