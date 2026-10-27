# Automated Circuit Component Testing

This directory provides automated component testing for all digital circuits in the simulator.

Each circuit component has its own dedicated testing script that verifies **100% of all possible input combinations (its full truth table)** using an automated, data-driven test pattern.

---

## Individual Component Test Scripts

### Level 1 Circuits (Basic Logic Gates)
| Script | Component | Choice | Inputs | Cases |
| :--- | :--- | :---: | :--- | :---: |
| [`test_and.sh`](test_and.sh) | 2-Input AND Gate | `1` | `InputA`, `InputB` | 4 |
| [`test_or.sh`](test_or.sh) | 2-Input OR Gate | `2` | `InputA`, `InputB` | 4 |
| [`test_not.sh`](test_not.sh) | 1-Input NOT Gate | `3` | `InputA` | 2 |
| [`test_nor.sh`](test_nor.sh) | 2-Input NOR Gate | `4` | `InputA`, `InputB` | 4 |
| [`test_xor.sh`](test_xor.sh) | 2-Input XOR Gate | `5` | `InputA`, `InputB` | 4 |

### Level 2 Circuits (Modular Subcircuits)
| Script | Component | Choice | Inputs | Cases |
| :--- | :--- | :---: | :--- | :---: |
| [`test_half_adder.sh`](test_half_adder.sh) | 1-Bit Half Adder | `6` | `InputA`, `InputB` | 4 |
| [`test_full_adder.sh`](test_full_adder.sh) | 1-Bit Full Adder | `7` | `InputA`, `InputB`, `Cin` | 8 |
| [`test_shifter.sh`](test_shifter.sh) | 2-Bit Combinational Shifter | `8` | `Shift`, `D0`, `D1` | 8 |

---

## Master Runners

| Script | Purpose |
| :--- | :--- |
| [`test_level1_circuits.sh`](test_level1_circuits.sh) | Runs all 5 Level 1 logic gate tests |
| [`test_level2_circuits.sh`](test_level2_circuits.sh) | Runs all 3 Level 2 subcircuit tests (supports filter args) |
| [`run_all_tests.sh`](run_all_tests.sh) | Runs all 8 circuit components (total 34 test cases) |

---

## How to Run

### Run an Individual Component
```bash
./Testing/test_and.sh
./Testing/test_not.sh
./Testing/test_half_adder.sh
./Testing/test_full_adder.sh
./Testing/test_shifter.sh
```

### Run by Level or All via Make
```bash
make test       # Runs all 8 components
make test-l1    # Runs Level 1 gates (AND, OR, NOT, NOR, XOR)
make test-l2    # Runs Level 2 subcircuits (Half Adder, Full Adder, Shifter)
```
