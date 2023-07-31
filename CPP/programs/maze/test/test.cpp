#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"
#include "utilities.hpp"
#include "maze.hpp"
#include <stdexcept>

TEST_CASE("01- Input Maze") {
    std::string input_maze_1 = "text/maze1.txt";
    std::string input_maze_2 = "text/maze2.txt";

    Maze maze1(input_maze_1);
    Maze maze2(input_maze_2);

    SUBCASE ("Start") {
        CHECK (is_equal ( maze1.get_vector2('s'), Vector2{5, 0} ));
        CHECK (is_equal ( maze2.get_vector2('s'), Vector2{15, 0} ));
    }

    SUBCASE ("Goal") {
        CHECK (is_equal ( maze1.get_vector2('g'), Vector2{0, 5} ));
        CHECK (is_equal ( maze2.get_vector2('g'), Vector2{8, 13} ));
    }
    
    SUBCASE ("Dimension") {
        CHECK( is_equal( maze1.get_vector2('d'), Vector2{6, 7} ) );
        CHECK( is_equal( maze2.get_vector2('d'), Vector2{16, 29} ) );
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
