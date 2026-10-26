# Digital Electronics Circuit Simulator

This project is a small, interactive C++ simulator for exploring how simple digital circuits behave. Choose a circuit, try different pairs of inputs, and the simulator will propagate the signals and save each result to a CSV file.

It was built around the digital circuit design problem: create gates from simpler components, connect them into useful circuits, and record their outputs for later inspection or plotting.

## What you can simulate

Choose one of these circuits when the program starts:

| Menu choice | Circuit | Recorded output |
| --- | --- | --- |
| `1` | Two-input AND | `OutputAND` |
| `2` | Two-input OR | `OutputOR` |
| `3` | One-input NOT | `OutputNOT` |
| `4` | Two-input NOR | `OutputNOR` |
| `5` | Two-input XOR | `OutputXOR` |
| `6` | One-bit half adder | `Sum`, `Carry` |
| `7` | One-bit full adder | `Sum`, `Cout` |
| `8` | Two-bit combinational shifter | `Out0`, `Out1` |

All logic gates (AND, OR, NOT, NOR, XOR), multiplexers, adders, and shifters are constructed modularly using universal NAND gates. The half adder combines XOR and AND; the full adder combines two half adders and an OR gate; and the 2-bit shifter uses 2:1 multiplexers built from NAND gates.

## Build and start

You will need a C++17 compiler (the Makefile uses `g++`) and GNU Make. In a terminal, go to the project folder—the one containing the Makefile—and run:

```sh
make run
```

Make compiles the program if needed, then starts it. To compile without starting it, use `make`.

## Try a simulation

After choosing a circuit, enter one pair of binary inputs per line. For example, choose `1` for AND and then enter:

```text
0 0
0 1
1 0
1 1
```

Each pair is one simulation step. The simulator updates the inputs, processes queued gate evaluations until the circuit settles, and records the result. When you are finished, send end-of-file with **Ctrl+D** on macOS/Linux or **Ctrl+Z** on Windows.

For an AND circuit, the results will look like this:

```text
Step,InputA,InputB,OutputAND
1,0,0,0
2,0,1,0
3,1,0,0
4,1,1,1
```

## Where the results go

The program writes `simulation_results.csv` to the directory where you started it (normally the project root when using `make run`). A new run replaces the previous CSV, so rename or copy it first if you want to keep it.

## How the code is organized

```text
.
├── Circuit/       # Circuit ownership and builders for combinations of gates
├── Components/    # Wires and NAND gate components
├── Main/          # Program entry point and interactive menu
├── Output/        # Output display interface and CSV writer
├── Simulation/    # Event queue used to propagate signal changes
├── Makefile       # Build, run, and clean commands
└── README.md
```

## Make commands

| Command | What it does |
| --- | --- |
| `make` | Builds `simulator.exe` |
| `make run` | Builds if necessary, then starts the simulator |
| `make clean` | Removes object files, the executable, and the generated CSV |

## Current scope

This version focuses on the interactive combinational circuits listed above and CSV export. Larger examples mentioned in the problem statement—such as counters or more complex circuits—and its multithreading stretch goal are not implemented yet.
