# Set compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Idependencies/thirdy_party -Iinclude
LDFLAGS := -Ldependencies/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

# Define source files and object files for maze
maze_sources := $(wildcard src/*.cpp)
maze_objects := $(patsubst src/%.cpp, build/%.o, $(maze_sources))
maze_executable := bin/maze

# Define executable for test
test_executable := bin/test

# Default target, compiles and links all executables
all: maze test

maze: create_build_dir $(maze_objects)
	$(CXX) $(maze_objects) -o $(maze_executable) $(LDFLAGS)

test: create_build_dir $(maze_objects)
	$(CXX) test/test.cpp src/maze.cpp src/frontier.cpp src/utilities.cpp src/cell.cpp -o $(test_executable) $(LDFLAGS) $(CXXFLAGS)

# Create build directory if it doesn't exist
create_build_dir:
	mkdir -p build

# Compile maze source files
build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build/*.o $(maze_executable) $(test_executable)
