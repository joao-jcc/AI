"""
Search Algorithm in Mazes
06/09/2021
""" 

import sys

class Node:
    """ Main Data Structure """
    def __init__(self, state, parent, action, manhattan=None):
        self.state = state
        self.parent = parent
        self.action = action
        self.manhattan = manhattan


class StackFrontier:
    """ Model Frontier using Depth-First Search"""

    def __init__(self):
        self.frontier = []
    
    def add(self, node):
        self.frontier.append(node)
    
    def empty(self):
        if self.frontier == []:
            return True
        return False
    
    def contains_state(self, node):
        if node in self.frontier:
            return True
        return False
    
    def remove(self):
        if self.empty():
            raise Exception("Frontier is empty")
        node = self.frontier.pop()

        return node


class QueueFrontier(StackFrontier):
    """ Model Frontier using Breadth-First Search"""
    
    def remove(self):
        if self.empty():
            raise Exception("Frontier is empty")  
        node = self.frontier.pop(0)

        return node


class ManhattanFrontier(StackFrontier):
    """ Mode a Frontier using Manhattan Distance as Heuristic Function"""

    def remove(self):
        if self.empty():
            raise Exception("Frontier is empty")
        min_distance = min(node.manhattan for node in self.frontier)
        nodes = [node for node in self.frontier if node.manhattan == min_distance]
        node = nodes[0]
        self.frontier.remove(node)

        return node
        

class Maze:
    """ Model the maze based on a .txt file"""

    def __init__(self, filename):
        with open(filename, "r") as file:
            f = file.readlines()
        
        maze = []
        walls = []
        for l_pos, line in enumerate(f):
            l, w = [], []
            for c_pos, e in enumerate(line):
                if e == '\n':
                    continue

                elif e == 'A':
                    self.initial_state = (l_pos, c_pos)
                    w.append(False)
                
                elif e == 'B':
                    self.goal_state = (l_pos, c_pos)
                    w.append(False)
                
                elif e == ' ':
                    w.append(False)

                else:
                    w.append(True)
 
                l.append(e)

            maze.append(l)
            walls.append(w)
        self.maze = maze
        self.walls = walls
        self.x= len(self.maze[0])
        self.y = len(self.maze)
    
    def actions(self, node):
        """ All possible actions based on maze edges and walls ('#')""" 
        l, c = node.state
        options = []
        # down
        if l < self.y-1 and self.maze[l+1][c] != '#':
            options.append([1, 0])
        # up
        if l > 0 and self.maze[l-1][c] != '#':
            options.append([-1, 0])
        # right
        if c < self.x-1 and self.maze[l][c+1] != '#':
            options.append([0, 1])
        # left
        if c > 0 and self.maze[l][c-1] != '#':
            options.append([0, -1])
        
        return options

    def manhattan(self, state):
        y, x = state
        y_goal, x_goal = self.goal_state

        return abs(y_goal - y) + abs(x_goal - x)
    
    def result(self, node, action, frontier='q'):
        """ Generate a new node from a parent node"""
        dx, dy = action
        x, y = node.state
        state = (x+dx, y+dy)
        if frontier == "m":
            manhattan = self.manhattan(state)
            return Node(state=state, parent=node, action=action, manhattan=manhattan)

        return Node(state=state, parent=node, action=action)
    
    def solve(self, frontier='q'):
        """Find a path to the maze"""
        # initialize start node
        mnt_start = self.manhattan(self.initial_state)
        start = Node(self.initial_state, None, None, manhattan=mnt_start)
        # create a frontier instance, cells and explored sets
        if frontier == "q":
            frontier = QueueFrontier()
        if frontier == "s":
            frontier = StackFrontier()
        if frontier == 'm':
            frontier = ManhattanFrontier()

        cells, explored_set = [], []
        # Add start node to the frontier
        frontier.add(start)
        # entry the while loop
        while True:
            if frontier.empty():
                raise Exception("No solution")
            
            # check if the node is the goal and expand the node if not.
            node = frontier.remove()
            explored_set.append(node)
            cells.append(node.state)
            if node.state == self.goal_state:
                break

            for action in self.actions(node):
                nd = self.result(node, action)
                if not frontier.contains_state(nd.state) and nd.state not in cells:    
                    frontier.add(nd)

        # path
        node = explored_set[-1]
        path = [node]
        while node.parent != None:
            node = node.parent
            path.append(node)

        path.reverse()
        self.path = path
        self.cells = cells
        self.cost = len(explored_set)
        return {"cells":cells, "explored_set":explored_set, "path":path}
    
    def print(self):
        solution = [node.state for node in self.path]
        exp_set = self.cells
        print()
        for i, row in enumerate(self.walls):
            for j, col in enumerate(row):
                if col:
                    print("█", end="")
                elif (i, j) == self.initial_state:
                    print("A", end="")
                elif (i, j) == self.goal_state:
                    print("B", end="")
                elif solution is not None and (i, j) in solution:
                    print("*", end="")
                elif (i, j) in exp_set:
                    print("-", end="")
                else:
                    print(" ", end="")
            print()
        print()


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python file.py maze.txt -sqm")
        sys.exit(1)

    maze = Maze(sys.argv[1])
    solution = maze.solve(sys.argv[2])
    print(f"Initial State: {maze.initial_state}")
    print(f"Goal State: {maze.goal_state}")
    print(f"Cost: {maze.cost}")
    print("Solving...")
    print()
    maze.print()


