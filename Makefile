# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Target executable
TARGET = main

# Source files
SRCS = main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target: build and run
all: clean $(TARGET) run

# Build the target executable
$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the target executable
run:
	@./$(TARGET)

# Clean up build files
clean:
	@rm -f $(TARGET) $(OBJS)

# Alias for clean, build, and run
.PHONY: all clean run
