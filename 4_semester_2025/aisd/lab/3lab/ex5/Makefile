SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=)
CXX := g++
CXXFLAGS := -I. -Wall -Wextra -std=c++17

all: $(OBJ)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

.PHONY: all clean
