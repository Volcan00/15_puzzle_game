# Define the compiler and the flags
CXX = g++
CXXFLAGS = -std=c++17

# Define the target executable
TARGET = 15_puzzle_game

# Define the source files
SRCS = main.cpp

# Define the object files
OBJS = $(SRCS:.cpp = .o)

# Default rule
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean