# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
CPPFLAGS = -ICircuit -IComponents -IMain -IOutput -ISimulation

# Output executable name
TARGET = simulator.exe

# Source and object files
SRCS = $(wildcard Circuit/*.cpp Components/*.cpp Main/*.cpp Output/*.cpp Simulation/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Run the compiled simulator
run: $(TARGET)
	./$(TARGET)

# Run all automated component tests
test: $(TARGET)
	./Testing/run_all_tests.sh

# Run only level 1 basic gate tests
test-l1: $(TARGET)
	./Testing/test_level1_circuits.sh

# Run only level 2 subcircuit tests
test-l2: $(TARGET)
	./Testing/test_level2_circuits.sh

# Clean build artifacts
clean:
	$(RM) $(OBJS) $(TARGET) simulation_results.csv

.PHONY: all run clean test test-l1 test-l2

