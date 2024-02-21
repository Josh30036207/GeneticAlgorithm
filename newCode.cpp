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
// Crossover function: Partially Mapped Crossover (PMX)
// Crossover function: Partially Mapped Crossover (PMX)
// Crossover function: Partially Mapped Crossover (PMX)
void partiallyMappedCrossover(const Rat& parent1, const Rat& parent2, Rat& child1, Rat& child2) {
    std::vector<int> mapping1(ROWS * COLS, -1);
    std::vector<int> mapping2(ROWS * COLS, -1);

    // Create mapping 1
    for (int i = parent1.row * COLS; i < (parent1.row + 1) * COLS; ++i) {
        mapping1[i % (ROWS * COLS)] = parent2.row * COLS + i % COLS;
    }

    // Create mapping 2
    int parent2Index = parent2.row * COLS + parent2.col;
    if (parent2Index >= 0 && parent2Index < ROWS * COLS) {
        mapping2[parent2Index] = parent1.row * COLS + parent1.col;
    }

    // Apply mapping 1 to child 1
    for (int i = 0; i < ROWS * COLS; ++i) {
        if (mapping1[i] == -1) {
            int row = i / COLS;
            int col = i % COLS;
            mapping1[i] = row * COLS + col;
        }
    }

    // Apply mapping 2 to child 2
    for (int i = 0; i < ROWS * COLS; ++i) {
        if (mapping2[i] == -1) {
            int row = i / COLS;
            int col = i % COLS;
            mapping2[i] = row * COLS + col;
        }
    }

    // Create children
    child1 = parent1;
    child2 = parent2;

    // Update children positions using mappings with bounds checking
    int child1Index = child1.row * COLS + child1.col;
    if (child1Index >= 0 && child1Index < ROWS * COLS) {
        int newPos = mapping1[child1Index];
        int newRow = newPos / COLS;
        int newCol = newPos % COLS;
        if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
            child1.row = newRow;
            child1.col = newCol;
        }
    }

    int child2Index = child2.row * COLS + child2.col;
    if (child2Index >= 0 && child2Index < ROWS * COLS) {
        int newPos = mapping2[child2Index];
        int newRow = newPos / COLS;
        int newCol = newPos % COLS;
        if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
            child2.row = newRow;
            child2.col = newCol;
        }
    }
}

// Mutation function: Swap Mutation
void swapMutation(Rat& rat) {
    int direction = std::rand() % 4;
    int newRow = rat.row;
    int newCol = rat.col;

    switch (direction) {
        case 0:  // Up
            if (newRow > 0) {
                newRow--;
            }
            break;
        case 1:  // Down
            if (newRow < ROWS - 1) {
                newRow++;
            }
            break;
        case 2:  // Left
            if (newCol > 0) {
                newCol--;
            }
            break;
        case 3:  // Right
            if (newCol < COLS - 1) {
                newCol++;
            }
            break;
    }

    // Update rat's position if within bounds
    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
        rat.row = newRow;
        rat.col = newCol;
    }
}




// Main function
int main() {
    // Seed the random number generator
    std::srand(std::time(nullptr));

    // Define population size
    const int POPULATION_SIZE = 10;

    // Define number of generations
    const int NUM_GENERATIONS = 5;

   // Initialize population of rats
    std::vector<Rat> population;
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        int randomRow = std::rand() % ROWS;
        int randomCol = std::rand() % COLS;
        
    // Check if the random position is within maze bounds
    if (randomRow >= 0 && randomRow < ROWS && randomCol >= 0 && randomCol < COLS) {
        population.push_back(Rat(randomRow, randomCol));
    } else {
        // Handle invalid position (e.g., by retrying or setting a default position)
        // For simplicity, you can retry generating random positions until a valid one is found
        --i; // Retry generating a random position
    }
}


    // Initialize variables to track the best rat found
    Rat bestRat = population[0];
    double bestFitness = evaluateFitness(bestRat);

    // Perform genetic algorithm for a specified number of generations
    for (int generation = 1; generation <= NUM_GENERATIONS; ++generation) {
        std::cout << "Generation " << generation << ":" << std::endl;

        // Evaluate fitness for each rat in the population
        std::vector<double> fitnessValues;
        for (const Rat& rat : population) {
            double fitness = evaluateFitness(rat);
            fitnessValues.push_back(fitness);

            // Update the best rat if found
            if (fitness > bestFitness) {
                bestFitness = fitness;
                bestRat = rat;
            }
        }

        // Select individuals from the population for reproduction
        std::vector<Rat> selectedRats;
        for (int i = 0; i < POPULATION_SIZE / 2; ++i) {
            int selectedIndex = rouletteWheelSelection(fitnessValues);
            selectedRats.push_back(population[selectedIndex]);
        }

        // Perform crossover and mutation operations on selected rats to create offspring
        // Here we assume each pair of selected rats produces two offspring
        std::vector<Rat> offspring;
        for (int i = 0; i < selectedRats.size(); i += 2) {
            Rat parent1 = selectedRats[i];
            Rat parent2 = selectedRats[i + 1];
            Rat child1(0, 0), child2(0, 0);
            partiallyMappedCrossover(parent1, parent2, child1, child2);
            swapMutation(child1);
            swapMutation(child2);
            offspring.push_back(child1);
            offspring.push_back(child2);
        }

        // Replace some individuals in the population with offspring
        for (int i = 0; i < offspring.size(); ++i) {
            int replaceIndex = std::rand() % POPULATION_SIZE; // Choose a random individual to replace
            population[replaceIndex] = offspring[i];
        }

        // Print the updated population
        std::cout << "Population:" << std::endl;
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            std::cout << "Rat " << i+1 << " - Row: " << population[i].row << ", Col: " << population[i].col << std::endl;
        }

        std::cout << std::endl;
    }

    // Output the best rat found
    std::cout << "Best Rat Found:" << std::endl;
    std::cout << "Row: " << bestRat.row << ", Col: " << bestRat.col << std::endl;
    std::cout << "Fitness: " << bestFitness << std::endl;

    printMazeWithRat(bestRat);

    return 0;
}
