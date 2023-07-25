# Set compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Idependencies/thirdy_party
LDFLAGS := -Ldependencies/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

# Define source files and object files for maze
maze_sources := $(wildcard programs/maze/src/*.cpp)
maze_objects := $(patsubst programs/maze/src/%.cpp, programs/maze/build/%.o, $(maze_sources))
maze_executable := executables/maze

# Default target, compiles and links all executables
all: maze

maze: CXXFLAGS += -Iprograms/maze/include
maze: create_build_dir $(maze_objects)
	$(CXX) $(maze_objects) -o $(maze_executable) $(LDFLAGS)

# Create build directory if it doesn't exist
create_build_dir:
	mkdir -p programs/maze/build

# Compile maze source files
programs/maze/build/%.o: programs/maze/src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -rf programs/maze/build/*.o $(maze_executable)

run: maze
	$(maze_executable)