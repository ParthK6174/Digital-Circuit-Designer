# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Output executable name
TARGET = simulator.exe

# Source and object files
SRCS = main.cpp EventQueue.cpp Wire.cpp Gate.cpp Circuit.cpp CSVOutput.cpp CircuitBuilders.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the compiled simulator
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	@if exist *.o del /Q /F *.o
	@if exist $(TARGET) del /Q /F $(TARGET)
	@if exist simulation_results.csv del /Q /F simulation_results.csv

.PHONY: all run clean
