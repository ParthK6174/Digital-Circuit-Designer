#include <iostream>
#include <vector>
#include "EventQueue.h"
#include "Circuit.h"
#include "Wire.h"
#include "Gate.h"
#include "CSVOutput.h"
#include "CircuitBuilders.h"
using namespace std;

int main() {
    // 1. Instantiate the EventQueue and top-level Circuit 
    EventQueue eq;
    Circuit topCircuit;

    // 2. Interactive Circuit Selection Menu
    cout << "======================================================\n";
    cout << "      Digital Electronics Circuit Simulator           \n";
    cout << "======================================================\n";
    cout << "Select circuit to simulate:\n";
    cout << "  1. AND\n";
    cout << "  2. OR\n";
    cout << "  3. NOT\n";
    cout << "  4. NOR\n";
    cout << "  5. XOR\n";
    cout << "  6. Half Adder\n";
    cout << "  7. Full Adder\n";
    cout << "  8. 2-Bit Shifter\n";
    cout << "Enter choice (1-8): ";

    int choice = 0;
    cin >> choice;
    if(choice < 1 || choice > 8){
        cout << "Invalid choice.";
        return 1;
    }
    

    // 3. Instantiate CSVOutput
    CSVOutput csvOutput("simulation_results.csv");

    // 4. Primary input wire list for the simulation loop
    vector<Wire*> inputWires;

    // 5. Dynamically instantiate outputs and build chosen circuit
    if (choice == 1) {
        cout << "\n[Configured Circuit: 2-Input AND Gate]\n";
        Wire* wireA = topCircuit.createWire("InputA", &eq, false);
        Wire* wireB = topCircuit.createWire("InputB", &eq, false);
        Wire* wireOut = topCircuit.createWire("OutputAND", &eq, false);
        buildAndGate(topCircuit, &eq, wireA, wireB, wireOut);
        inputWires.push_back(wireA);
        inputWires.push_back(wireB);
        csvOutput.watchWire(wireA);
        csvOutput.watchWire(wireB);
        csvOutput.watchWire(wireOut);
    } 
    else if (choice == 2) {
        cout << "\n[Configured Circuit: 2-Input OR Gate]\n";
        Wire* wireA = topCircuit.createWire("InputA", &eq, false);
        Wire* wireB = topCircuit.createWire("InputB", &eq, false);
        Wire* wireOut = topCircuit.createWire("OutputOR", &eq, false);
        buildOrGate(topCircuit, &eq, wireA, wireB, wireOut);
        inputWires.push_back(wireA);
        inputWires.push_back(wireB);
        csvOutput.watchWire(wireA);
        csvOutput.watchWire(wireB);
        csvOutput.watchWire(wireOut);
    } 
    else if (choice == 3) {
        cout << "\n[Configured Circuit: 1-Input NOT Gate]\n";
        Wire* wireA = topCircuit.createWire("InputA", &eq, false);
        Wire* wireOut = topCircuit.createWire("OutputNOT", &eq, true);
        buildNotGate(topCircuit, &eq, wireA, wireOut);
        inputWires.push_back(wireA);
        csvOutput.watchWire(wireA);
        csvOutput.watchWire(wireOut);
    } 
    else if (choice == 4) {
        cout << "\n[Configured Circuit: 2-Input NOR Gate]\n";
        Wire* wireA = topCircuit.createWire("InputA", &eq, false);
        Wire* wireB = topCircuit.createWire("InputB", &eq, false);
        Wire* wireOut = topCircuit.createWire("OutputNOR", &eq, true);
        buildNorGate(topCircuit, &eq, wireA, wireB, wireOut);
        inputWires.push_back(wireA);
        inputWires.push_back(wireB);
        csvOutput.watchWire(wireA);
        csvOutput.watchWire(wireB);
        csvOutput.watchWire(wireOut);
    } 
    else if (choice == 5) {
        cout << "\n[Configured Circuit: 2-Input XOR Gate]\n";
        Wire* wireA = topCircuit.createWire("InputA", &eq, false);
        Wire* wireB = topCircuit.createWire("InputB", &eq, false);
        Wire* wireOut = topCircuit.createWire("OutputXOR", &eq, false);
        buildXorGate(topCircuit, &eq, wireA, wireB, wireOut);
        inputWires.push_back(wireA);
        inputWires.push_back(wireB);
        csvOutput.watchWire(wireA);
        csvOutput.watchWire(wireB);
        csvOutput.watchWire(wireOut);
    } 
    else if (choice == 6) {
        cout << "\n[Configured Circuit: 1-Bit Half Adder]\n";
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
    } 
    else if (choice == 7) {
        cout << "\n[Configured Circuit: 1-Bit Full Adder]\n";
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
    } 
    else if (choice == 8) {
        cout << "\n[Configured Circuit: 2-Bit Combinational Shifter]\n";
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
        cout << "\nEnter 1 input (0 or 1) per line, or Ctrl+D/Ctrl+Z to exit:\n";
        int valA = 0;
        while (cin >> valA) {
            inputWires[0]->set(valA != 0);
            eq.processEvents();
            csvOutput.recordStep(stepId);
            stepId++;
        }
    } 
    else if (inputWires.size() == 2) {
        cout << "\nEnter two inputs (0 or 1) separated by a space, or Ctrl+D/Ctrl+Z to exit:\n";
        int valA = 0;
        int valB = 0;
        while (cin >> valA >> valB) {
            inputWires[0]->set(valA != 0);
            inputWires[1]->set(valB != 0);
            eq.processEvents();
            csvOutput.recordStep(stepId);
            stepId++;
        }
    } 
    else if (inputWires.size() == 3) {
        if (choice == 7) {
            cout << "\nEnter three inputs (InputA InputB Cin) separated by spaces, or Ctrl+D/Ctrl+Z to exit:\n";
        } else {
            cout << "\nEnter three inputs (Shift D0 D1) separated by spaces, or Ctrl+D/Ctrl+Z to exit:\n";
        }
        int valA = 0;
        int valB = 0;
        int valC = 0;
        while (cin >> valA >> valB >> valC) {
            inputWires[0]->set(valA != 0);
            inputWires[1]->set(valB != 0);
            inputWires[2]->set(valC != 0);
            eq.processEvents();
            csvOutput.recordStep(stepId);
            stepId++;
        }
    }

    cout << "\nSimulation finished.\n";
    cout << "Results exported to 'simulation_results.csv'.\n";

    return 0;
}
