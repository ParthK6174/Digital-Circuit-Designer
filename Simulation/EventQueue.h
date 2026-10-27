#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <queue>

class CircuitElement;

/*
 * EventQueue manages the FIFO scheduling and execution of circuit element evaluations.
 * Whenever a wire's state transitions, connected elements are pushed here.
*/

class EventQueue {
private:
    std::queue<CircuitElement*> queue;

public:
    EventQueue() = default;

    /**
     * Push a circuit element into the queue for subsequent evaluation.
     */
    void schedule(CircuitElement* element);

    /**
     * Continuously pops and evaluates elements until the queue is exhausted.
     * This drives the signal propagation through the circuit until it settles.
     */
    void processEvents();

    /**
     * Checks whether there are pending events.
     */
    bool isEmpty() const;

    /**
     *  Returns current number of pending events.
     */
    size_t size() const;
};

#endif // EVENT_QUEUE_H
