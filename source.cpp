#include <iostream>
#include <cmath>

// Define the dimensions of the maze
const int ROWS = 5;
const int COLS = 5;

// Define the maze layout using a 2D array
char maze[ROWS][COLS] = {
    {'0', '1', '0', '0', '0'},
    {'0', '1', '1', '1', '0'},
    {'0', '0', '0', '0', '0'},
    {'1', '1', '1', '1', '0'},
    {'0', '0', '0', 'C', '0'}
};

// Define the rat's position in the maze
struct Rat {
    int row;
    int col;
    Rat(int r, int c) : row(r), col(c) {}
};

// Calculate Manhattan distance between two points
int manhattanDistance(int row1, int col1, int row2, int col2) {
    return std::abs(row1 - row2) + std::abs(col1 - col2);
}

// Fitness function: Evaluate how close the rat is to the cheese
double evaluateFitness(const Rat& rat) {
    // Calculate Manhattan distance between rat and cheese
    int distance = manhattanDistance(rat.row, rat.col, ROWS - 1, COLS - 2);

    // Fitness is inversely proportional to distance
    return 1.0 / (distance + 1);
}

// Function to print the maze with the rat's position
void printMazeWithRat(const Rat& rat) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (i == rat.row && j == rat.col) {
                std::cout << 'R' << " "; // Represent rat with 'R'
            } else {
                std::cout << maze[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    // Initial rat position
    Rat rat(0, 0);

    // Print the initial maze with the rat's position
    std::cout << "Initial Maze with Rat:" << std::endl;
    printMazeWithRat(rat);

    // Evaluate fitness
    double fitness = evaluateFitness(rat);
    std::cout << "Fitness: " << fitness << std::endl;

    return 0;
}
