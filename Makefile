CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2
CPPFLAGS = -Iinclude

# Source files
SOURCES = src/main.cpp src/lexer.cpp src/parser.cpp src/interpreter.cpp src/ast.cpp src/token.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = toy-compiler

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Run the program with example input
run: $(TARGET)
	./$(TARGET) "3 + 5 * 2"

# Run more comprehensive tests
test: $(TARGET)
	@echo "Test 1: 3 + 5 * 2"
	@./$(TARGET) "3 + 5 * 2"
	@echo "\nTest 2: (10 + 2) * 3"
	@./$(TARGET) "(10 + 2) * 3"
	@echo "\nTest 3: 100 / 5 - 3"
	@./$(TARGET) "100 / 5 - 3"
	@echo "\nTest 4: (20 - 5) / (3 + 2)"
	@./$(TARGET) "(20 - 5) / (3 + 2)"
	@echo "\nTest 5: 2 * 3 * 4"
	@./$(TARGET) "2 * 3 * 4"
	@echo "\nTest 6: 100"
	@./$(TARGET) "100"

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all run test clean
