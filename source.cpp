#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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
// struct Rat {
//     int row;
//     int col;
//     Rat(int r, int c) : row(r), col(c) {}
// };

struct Rat {
    int row;
    int col;
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

// Selection function: Roulette Wheel Selection
int rouletteWheelSelection(const std::vector<double>& fitnessValues) {
    // Calculate total fitness
    double totalFitness = 0.0;
    for (double fitness : fitnessValues) {
        totalFitness += fitness;
    }

    // Generate a random number between 0 and totalFitness
    double randomNumber = (double)std::rand() / RAND_MAX * totalFitness;

    // Select an individual based on the random number
    double cumulativeFitness = 0.0;
    for (int i = 0; i < fitnessValues.size(); ++i) {
        cumulativeFitness += fitnessValues[i];
        if (cumulativeFitness >= randomNumber) {
            return i; // Return the index of the selected individual
        }
    }

    // This should never happen
    return -1;
}

// Crossover function: Partially Mapped Crossover (PMX)

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




// Mutation function: Swap Mutation
void swapMutation(Rat& rat) {
    // Generate two random positions
    int pos1 = std::rand() % ROWS;
    int pos2 = std::rand() % COLS;

    // Swap positions
    std::swap(rat.row, pos1);
    std::swap(rat.col, pos2);
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
 

// int main() {
//     // Seed the random number generator
//     std::srand(std::time(nullptr));

//     // Define population size
//     const int POPULATION_SIZE = 10;

//     // Define number of generations
//     const int NUM_GENERATIONS = 5;

//     // Initialize population of rats
//     std::vector<Rat> population;
//     for (int i = 0; i < POPULATION_SIZE; ++i) {
//         int randomRow = std::rand() % ROWS;
//         int randomCol = std::rand() % COLS;
//         population.push_back(Rat(randomRow, randomCol));
//     }

//     // Initialize variables to track the best rat found
//     Rat bestRat = population[0];
//     double bestFitness = evaluateFitness(bestRat);

//     // Perform genetic algorithm for a specified number of generations
//     for (int generation = 1; generation <= NUM_GENERATIONS; ++generation) {
//         std::cout << "Generation " << generation << ":" << std::endl;

//         // Evaluate fitness for each rat in the population
//         std::vector<double> fitnessValues;
//         for (const Rat& rat : population) {
//             double fitness = evaluateFitness(rat);
//             fitnessValues.push_back(fitness);

//             // Update the best rat if found
//             if (fitness > bestFitness) {
//                 bestFitness = fitness;
//                 bestRat = rat;
//             }
//         }

//         // Select individuals from the population for reproduction
//         std::vector<Rat> selectedRats;
//         for (int i = 0; i < POPULATION_SIZE / 2; ++i) {
//             int selectedIndex = rouletteWheelSelection(fitnessValues);
//             selectedRats.push_back(population[selectedIndex]);
//         }

//         // Perform crossover and mutation operations on selected rats to create offspring
//         // Here we assume each pair of selected rats produces two offspring
//         std::vector<Rat> offspring;
//         for (int i = 0; i < selectedRats.size(); i += 2) {
//             Rat parent1 = selectedRats[i];
//             Rat parent2 = selectedRats[i + 1];
//             Rat child1(0, 0), child2(0, 0);
//             partiallyMappedCrossover(parent1, parent2, child1, child2);
//             swapMutation(child1);
//             swapMutation(child2);
//             offspring.push_back(child1);
//             offspring.push_back(child2);
//         }

//         // Replace some individuals in the population with offspring
//         for (int i = 0; i < offspring.size(); ++i) {
//             int replaceIndex = std::rand() % POPULATION_SIZE; // Choose a random individual to replace
//             population[replaceIndex] = offspring[i];
//         }

//         // Print the updated population
//         std::cout << "Population:" << std::endl;
//         for (int i = 0; i < POPULATION_SIZE; ++i) {
//             std::cout << "Rat " << i+1 << " - Row: " << population[i].row << ", Col: " << population[i].col << std::endl;
//         }

//         std::cout << std::endl;
//     }

//     // Output the best rat found
//     std::cout << "Best Rat Found:" << std::endl;
//     std::cout << "Row: " << bestRat.row << ", Col: " << bestRat.col << std::endl;
//     std::cout << "Fitness: " << bestFitness << std::endl;

//     return 0;
// }
