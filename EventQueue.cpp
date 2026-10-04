#include "EventQueue.h"
#include "CircuitElement.h"

void EventQueue::schedule(CircuitElement* element) {
    if (element != nullptr) {
        queue.push(element);
    }
}

void EventQueue::processEvents() {
    while (!queue.empty()) {
        CircuitElement* element = queue.front();
        queue.pop();
        if (element != nullptr) {
            element->evaluate();
        }
    }
}

bool EventQueue::isEmpty() const {
    return queue.empty();
}

size_t EventQueue::size() const {
    return queue.size();
}
