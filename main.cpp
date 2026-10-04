#include <iostream>
#include "EventQueue.h"
#include "Circuit.h"
#include "Wire.h"
#include "Gate.h"
#include "CSVOutput.h"
#include "CircuitBuilders.h"

int main() {
    // 1. Instantiate the EventQueue and top-level Circuit container
    EventQueue eq;
    Circuit topCircuit;

    // 2. Interactive Circuit Selection Menu
    std::cout << "======================================================\n";
    std::cout << "      Digital Electronics Circuit Simulator           \n";
    std::cout << "======================================================\n";
    std::cout << "Select circuit to simulate:\n";
    std::cout << "  1. AND\n";
    std::cout << "  2. OR\n";
    std::cout << "  3. XOR\n";
    std::cout << "  4. Half Adder\n";
    std::cout << "Enter choice (1-4): ";

    int choice = 1;
    if (!(std::cin >> choice) || choice < 1 || choice > 4) {
        std::cerr << "Invalid choice. Exiting.\n";
        return 1;
    }

    // 3. Create Primary Inputs
    Wire* wireA = topCircuit.createWire("InputA", &eq, false);
    Wire* wireB = topCircuit.createWire("InputB", &eq, false);

    // 4. Instantiate CSVOutput
    CSVOutput csvOutput("simulation_results.csv");
    csvOutput.watchWire(wireA);
    csvOutput.watchWire(wireB);

    // 5. Dynamically instantiate outputs and build chosen circuit
    if (choice == 1) {
        std::cout << "\n[Configured Circuit: 2-Input AND Gate]\n";
        Wire* wireOut = topCircuit.createWire("OutputAND", &eq, false);
        buildAndGate(topCircuit, &eq, wireA, wireB, wireOut);
        csvOutput.watchWire(wireOut);
    } else if (choice == 2) {
        std::cout << "\n[Configured Circuit: 2-Input OR Gate]\n";
        Wire* wireOut = topCircuit.createWire("OutputOR", &eq, false);
        buildOrGate(topCircuit, &eq, wireA, wireB, wireOut);
        csvOutput.watchWire(wireOut);
    } else if (choice == 3) {
        std::cout << "\n[Configured Circuit: 2-Input XOR Gate]\n";
        Wire* wireOut = topCircuit.createWire("OutputXOR", &eq, false);
        buildXorGate(topCircuit, &eq, wireA, wireB, wireOut);
        csvOutput.watchWire(wireOut);
    } else if (choice == 4) {
        std::cout << "\n[Configured Circuit: 1-Bit Half Adder]\n";
        Wire* wireSum = topCircuit.createWire("Sum", &eq, false);
        Wire* wireCarry = topCircuit.createWire("Carry", &eq, false);
        buildHalfAdder(topCircuit, &eq, wireA, wireB, wireSum, wireCarry);
        csvOutput.watchWire(wireSum);
        csvOutput.watchWire(wireCarry);
    }

    // 6. Initialize CSV Header row after all watched wires are configured
    csvOutput.initHeader();

    // 7. Continuous Standard Input Simulation Loop
    std::cout << "\nEnter two inputs (0 or 1) separated by a space, or Ctrl+D/Ctrl+Z to exit:\n";

    int valA = 0;
    int valB = 0;
    int stepId = 1;

    while (std::cin >> valA >> valB) {
        // Apply input signals
        wireA->set(valA != 0);
        wireB->set(valB != 0);

        // Propagate signals through event dispatcher until settled
        eq.processEvents();

        // Record the settled state of watched wires to CSV
        csvOutput.recordStep(stepId);
        stepId++;
    }

    std::cout << "\nSimulation finished.\n";
    std::cout << "Results exported to 'simulation_results.csv'.\n";

    return 0;
}
