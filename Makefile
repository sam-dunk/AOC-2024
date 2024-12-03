CXX = g++
CXXFLAGS = -Wall -Wextra -O2

SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
EXES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%,$(SRCS))

all: $(BUILD_DIR) $(EXES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
