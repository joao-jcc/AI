#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "raylib.h"
#include "doctest.hpp"
#include "utilities.hpp"
#include "maze.hpp"
#include <stdexcept>

std::string input_maze_1 = "text/maze1.txt";
std::string input_maze_2 = "text/maze2.txt";
std::string input_maze_3 = "text/maze3.txt";
std::string input_maze_4 = "text/maze4.txt";
std::string input_maze_5 = "text/maze5.txt";

TEST_CASE("01- Input Maze") {
    Maze maze1(input_maze_1);
    Maze maze2(input_maze_2);



    SUBCASE ("Start") {
        CHECK (equal_v2( maze1.get_vector2('s'), Vector2{5, 0} ));
        CHECK (equal_v2( maze2.get_vector2('s'), Vector2{15, 0} ));
    }

    SUBCASE ("Goal") {
        CHECK (equal_v2( maze1.get_vector2('g'), Vector2{0, 5} ));
        CHECK (equal_v2( maze2.get_vector2('g'), Vector2{8, 13} ));
    }
    
    SUBCASE ("Dimension") {
        CHECK( equal_v2( maze1.get_vector2('d'), Vector2{6, 7} ));
        CHECK( equal_v2( maze2.get_vector2('d'), Vector2{16, 29} ));
    }

    SUBCASE ("Counting the number of walls") {
        std::vector< std::vector<bool> > walls = maze1.get_walls();
        Vector2 dimension = maze1.get_vector2('d');
        
        unsigned counting = 0;
        for (int l=0; l < dimension.x; ++l) {
            for (int c=0; c < dimension.y; ++c) {
                counting += walls[l][c];
            }
        }

        unsigned empty_spaces = 11;
        CHECK_EQ(counting, dimension.x * dimension.y - empty_spaces);
    }
}

TEST_CASE ("02- Actions") {
    Maze maze4(input_maze_4);
    Maze maze5(input_maze_5);

    SUBCASE ("All moves available") {
        Node node{Vector2{1, 1}};
        std::vector<Vector2> actions = maze4.actions(&node);
        
        CHECK_EQ(actions.size(), 4);
    }

    SUBCASE ("Empty moves") {
        Node node{Vector2{0, 0}};
        std::vector<Vector2> actions = maze5.actions(&node);
        
        CHECK_EQ(actions.size(), 0);
    }

    
    SUBCASE ("LEFT") {
        Node node{Vector2{0, 6}};
        std::vector<Vector2> actions = maze5.actions(&node);
        
        CHECK_EQ(actions.size(), 1);
        CHECK( equal_v2(Vector2{0, -1}, actions.at(0)) );
    }

    SUBCASE ("RIGHT") {
        Node node{Vector2{2, 0}};
        std::vector<Vector2> actions = maze5.actions(&node);
        
        CHECK_EQ(actions.size(), 1);
        CHECK( equal_v2(Vector2{0, 1}, actions.at(0)) );
    }

    SUBCASE ("DOWN") {
        Node node{Vector2{0, 3}};
        std::vector<Vector2> actions = maze5.actions(&node);
        
        CHECK_EQ(actions.size(), 1);
        CHECK( equal_v2(Vector2{1, 0}, actions.at(0)) );
    }

    SUBCASE ("UP") {
        Node node{Vector2{3, 3}};
        std::vector<Vector2> actions = maze5.actions(&node);

        CHECK_EQ(actions.size(), 1);
        CHECK( equal_v2(Vector2{-1, 0}, actions.at(0)) );
    }
}


TEST_CASE ("04- Vector2") {
    Vector2 v1{1, 2};
    Vector2 v2{1, 2};
    Vector2 v3{1, 3};

    CHECK (equal_v2(v1, v2));
    CHECK (!equal_v2(v2, v3));
}

TEST_CASE ("05- Nodes") {
    Node origin{Vector2{0, 0}, Vector2{0, 0}, nullptr};  

    // --- branch a ---

    // move down from origin
    Node node1a{Vector2{1, 0}, Vector2{1, 0}, &origin};
    
    // move right from node1a
    Node node2a{Vector2{1, 1}, Vector2{0, 1}, &node1a};


    // --- branch b ---

    // move right from origin
    Node node1b{Vector2{0, 1}, Vector2{0, 1}, &origin};

    // move down from node1b
    Node node2b{Vector2{1, 1}, Vector2{0, 1}, &node1b};


    // --- union ---

    Node node1u{Vector2{2, 1}, Vector2{1, 0}, &node2b};
    Node node2u{Vector2{2, 1}, Vector2{1, 0}, &node2a};

    CHECK (equal_node(&origin, &origin));
    CHECK (!equal_node(&node2u, &node1u));
    CHECK(equal_node(&node1u, &node1u));
    CHECK(equal_node(&node1a, &node1a));
}



