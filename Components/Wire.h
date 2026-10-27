#ifndef WIRE_H
#define WIRE_H

#include <string>
#include <vector>
using namespace std;

class CircuitElement;
class EventQueue;

/**
 * Represents an electrical connection wire carrying a boolean state.
 * Implements the Observer pattern: when state changes, it schedules registered listeners.
 */
class Wire {
private:
    string name; //lable of the particular wire
    bool state; //curent physical voltage(0 or 1)
    EventQueue* eventQueue;
    vector<CircuitElement*> listeners; //list of all gates plugged into this specific wire

public:
    //Constructors
    Wire(const string& wireName, EventQueue* eq, bool initialState = false); //for creating custom named wire while ignoring init. state 
    Wire(EventQueue* eq, bool initialState = false, const string& wireName = "Wire"); //when we dont want to enter wire name manually

    //Member Functions
    void addListener(CircuitElement* element); //Subscribes a downstream CircuitElement to observe state changes on this wire. Contains all the gates connected to that particular wire

    void set(bool val); //Sets the wire's signal value. Schedules listeners only on actual state transition.

    bool get() const; //Retrieves current binary state of the wire.

    const string& getName() const; //Retrieves wire identifier name.
};

#endif // WIRE_H
