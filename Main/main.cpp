#include <iostream>
#include <vector>
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
    std::cout << "  3. NOT\n";
    std::cout << "  4. NOR\n";
    std::cout << "  5. XOR\n";
    std::cout << "  6. Half Adder\n";
    std::cout << "  7. Full Adder\n";
    std::cout << "  8. 2-Bit Shifter\n";
    std::cout << "Enter choice (1-8): ";

    int choice = 1;
    if (!(std::cin >> choice) || choice < 1 || choice > 8) {
        std::cerr << "Invalid choice. Exiting.\n";
        return 1;
    }

    // 3. Instantiate CSVOutput
    CSVOutput csvOutput("simulation_results.csv");

    // 4. Primary input wire list for the simulation loop
    std::vector<Wire*> inputWires;

    // 5. Dynamically instantiate outputs and build chosen circuit
    if (choice == 1) {
        std::cout << "\n[Configured Circuit: 2-Input AND Gate]\n";
        Wire* wireA = topCircuit.createWire("InputA", &eq, false);
        Wire* wireB = topCircuit.createWire("InputB", &eq, false);
        Wire* wireOut = topCircuit.createWire("OutputAND", &eq, false);
        buildAndGate(topCircuit, &eq, wireA, wireB, wireOut);
        inputWires.push_back(wireA);
        inputWires.push_back(wireB);
        csvOutput.watchWire(wireA);
        csvOutput.watchWire(wireB);
        csvOutput.watchWire(wireOut);
    } else if (choice == 2) {
        std::cout << "\n[Configured Circuit: 2-Input OR Gate]\n";
        Wire* wireA = topCircuit.createWire("InputA", &eq, false);
        Wire* wireB = topCircuit.createWire("InputB", &eq, false);
        Wire* wireOut = topCircuit.createWire("OutputOR", &eq, false);
        buildOrGate(topCircuit, &eq, wireA, wireB, wireOut);
        inputWires.push_back(wireA);
        inputWires.push_back(wireB);
        csvOutput.watchWire(wireA);
        csvOutput.watchWire(wireB);
        csvOutput.watchWire(wireOut);
    } else if (choice == 3) {
        std::cout << "\n[Configured Circuit: 1-Input NOT Gate]\n";
        Wire* wireA = topCircuit.createWire("InputA", &eq, false);
        Wire* wireOut = topCircuit.createWire("OutputNOT", &eq, true);
        buildNotGate(topCircuit, &eq, wireA, wireOut);
        inputWires.push_back(wireA);
        csvOutput.watchWire(wireA);
        csvOutput.watchWire(wireOut);
    } else if (choice == 4) {
        std::cout << "\n[Configured Circuit: 2-Input NOR Gate]\n";
        Wire* wireA = topCircuit.createWire("InputA", &eq, false);
        Wire* wireB = topCircuit.createWire("InputB", &eq, false);
        Wire* wireOut = topCircuit.createWire("OutputNOR", &eq, true);
        buildNorGate(topCircuit, &eq, wireA, wireB, wireOut);
        inputWires.push_back(wireA);
        inputWires.push_back(wireB);
        csvOutput.watchWire(wireA);
        csvOutput.watchWire(wireB);
        csvOutput.watchWire(wireOut);
    } else if (choice == 5) {
        std::cout << "\n[Configured Circuit: 2-Input XOR Gate]\n";
        Wire* wireA = topCircuit.createWire("InputA", &eq, false);
        Wire* wireB = topCircuit.createWire("InputB", &eq, false);
        Wire* wireOut = topCircuit.createWire("OutputXOR", &eq, false);
        buildXorGate(topCircuit, &eq, wireA, wireB, wireOut);
        inputWires.push_back(wireA);
        inputWires.push_back(wireB);
        csvOutput.watchWire(wireA);
        csvOutput.watchWire(wireB);
        csvOutput.watchWire(wireOut);
    } else if (choice == 6) {
        std::cout << "\n[Configured Circuit: 1-Bit Half Adder]\n";
        Wire* wireA = topCircuit.createWire("InputA", &eq, false);
        Wire* wireB = topCircuit.createWire("InputB", &eq, false);
        Wire* wireSum = topCircuit.createWire("Sum", &eq, false);
        Wire* wireCarry = topCircuit.createWire("Carry", &eq, false);
        buildHalfAdder(topCircuit, &eq, wireA, wireB, wireSum, wireCarry);
        inputWires.push_back(wireA);
        inputWires.push_back(wireB);
        csvOutput.watchWire(wireA);
        csvOutput.watchWire(wireB);
        csvOutput.watchWire(wireSum);
        csvOutput.watchWire(wireCarry);
    } else if (choice == 7) {
        std::cout << "\n[Configured Circuit: 1-Bit Full Adder]\n";
        Wire* wireA = topCircuit.createWire("InputA", &eq, false);
        Wire* wireB = topCircuit.createWire("InputB", &eq, false);
        Wire* wireCin = topCircuit.createWire("Cin", &eq, false);
        Wire* wireSum = topCircuit.createWire("Sum", &eq, false);
        Wire* wireCout = topCircuit.createWire("Cout", &eq, false);
        buildFullAdder(topCircuit, &eq, wireA, wireB, wireCin, wireSum, wireCout);
        inputWires.push_back(wireA);
        inputWires.push_back(wireB);
        inputWires.push_back(wireCin);
        csvOutput.watchWire(wireA);
        csvOutput.watchWire(wireB);
        csvOutput.watchWire(wireCin);
        csvOutput.watchWire(wireSum);
        csvOutput.watchWire(wireCout);
    } else if (choice == 8) {
        std::cout << "\n[Configured Circuit: 2-Bit Combinational Shifter]\n";
        Wire* wireShift = topCircuit.createWire("Shift", &eq, false);
        Wire* wireD0 = topCircuit.createWire("D0", &eq, false);
        Wire* wireD1 = topCircuit.createWire("D1", &eq, false);
        Wire* wireOut0 = topCircuit.createWire("Out0", &eq, false);
        Wire* wireOut1 = topCircuit.createWire("Out1", &eq, false);
        buildShifter(topCircuit, &eq, wireShift, wireD0, wireD1, wireOut0, wireOut1);
        inputWires.push_back(wireShift);
        inputWires.push_back(wireD0);
        inputWires.push_back(wireD1);
        csvOutput.watchWire(wireShift);
        csvOutput.watchWire(wireD0);
        csvOutput.watchWire(wireD1);
        csvOutput.watchWire(wireOut0);
        csvOutput.watchWire(wireOut1);
    }

    // 6. Initialize CSV Header row after all watched wires are configured
    csvOutput.initHeader();

    // 7. Continuous Standard Input Simulation Loop
    int stepId = 1;

    if (inputWires.size() == 1) {
        std::cout << "\nEnter 1 input (0 or 1) per line, or Ctrl+D/Ctrl+Z to exit:\n";
        int valA = 0;
        while (std::cin >> valA) {
            inputWires[0]->set(valA != 0);
            eq.processEvents();
            csvOutput.recordStep(stepId);
            stepId++;
        }
    } else if (inputWires.size() == 2) {
        std::cout << "\nEnter two inputs (0 or 1) separated by a space, or Ctrl+D/Ctrl+Z to exit:\n";
        int valA = 0;
        int valB = 0;
        while (std::cin >> valA >> valB) {
            inputWires[0]->set(valA != 0);
            inputWires[1]->set(valB != 0);
            eq.processEvents();
            csvOutput.recordStep(stepId);
            stepId++;
        }
    } else if (inputWires.size() == 3) {
        if (choice == 7) {
            std::cout << "\nEnter three inputs (InputA InputB Cin) separated by spaces, or Ctrl+D/Ctrl+Z to exit:\n";
        } else {
            std::cout << "\nEnter three inputs (Shift D0 D1) separated by spaces, or Ctrl+D/Ctrl+Z to exit:\n";
        }
        int valA = 0;
        int valB = 0;
        int valC = 0;
        while (std::cin >> valA >> valB >> valC) {
            inputWires[0]->set(valA != 0);
            inputWires[1]->set(valB != 0);
            inputWires[2]->set(valC != 0);
            eq.processEvents();
            csvOutput.recordStep(stepId);
            stepId++;
        }
    }

    std::cout << "\nSimulation finished.\n";
    std::cout << "Results exported to 'simulation_results.csv'.\n";

    return 0;
}
