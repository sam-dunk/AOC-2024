# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -O2

# Directories
SRC_DIR = src
BUILD_DIR = build

# Find all .cpp files in src
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# Generate executable names based on source filenames
EXES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%,$(SRCS))

# Default target
all: $(EXES)

# Rule to build each executable
$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean target
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean
