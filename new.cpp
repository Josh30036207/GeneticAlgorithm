#include <iostream>
#include <vector>
#include <algorithm>


// Define Rat struct
struct Rat {
    int row;
    int col;
};

// Define ROWS and COLS constants
const int ROWS = 5;
const int COLS = 5;

// Define partiallyMappedCrossover function
void partiallyMappedCrossover(const Rat& parent1, const Rat& parent2, Rat& child1, Rat& child2) {
    // Define mapping section indices
    int start = 1; // Start index of the mapping section
    int end = 2;   // End index of the mapping section

    // Create mapping sections
    int mapping1[COLS];
    int mapping2[COLS];

    // Perform mapping
    for (int i = start; i <= end; ++i) {
        mapping1[parent1.col] = parent2.col;
        mapping2[parent2.col] = parent1.col;
    }

    // Perform crossover
    child1.row = parent1.row;
    child2.row = parent2.row;

    for (int i = 0; i < COLS; ++i) {
        if (i >= start && i <= end) {
            child1.col = parent2.col;
            child2.col = parent1.col;
        } else {
            child1.col = mapping1[parent1.col];
            child2.col = mapping2[parent2.col];
        }
    }
}

int main() {
    // Create parent rats
    Rat parent1 = {1, 1};
    Rat parent2 = {3, 3};

    // Create child rats
    Rat child1, child2;

    // Perform crossover
    partiallyMappedCrossover(parent1, parent2, child1, child2);

    // Print results
    std::cout << "Parent 1: Row " << parent1.row << ", Col " << parent1.col << std::endl;
    std::cout << "Parent 2: Row " << parent2.row << ", Col " << parent2.col << std::endl;
    std::cout << "Child 1: Row " << child1.row << ", Col " << child1.col << std::endl;
    std::cout << "Child 2: Row " << child2.row << ", Col " << child2.col << std::endl;

    return 0;
}
