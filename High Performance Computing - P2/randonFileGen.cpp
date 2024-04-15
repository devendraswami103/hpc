#include <iostream>
#include <fstream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

void generateRandomFile(const string& filename) {
    ofstream outputFile(filename);
    if (!outputFile) {
        cerr << "Error: Unable to create output file!" << endl;
        return;
    }

    srand(time(nullptr)); // Seed for random number generator

    // Generate random values for each parameter
    int numUsers = rand() % 49 + 2; // Random number of users between 2 and 50
    int numTasks = rand() % 99 + 2; // Random number of tasks between 2 and 100
    int numNodes = rand() % 4 + 2;   // Random number of nodes between 2 and 5

    outputFile << numUsers << endl;
    outputFile << numTasks << endl;

    for (int i = 0; i < numTasks; ++i) {
        double arrivalTime = static_cast<double>(rand() % 21);         // Random arrival time between 0 and 20
        double executionTime = static_cast<double>(rand() % 19 + 2);    // Random execution time between 2 and 20
        int userId = rand() % numUsers + 1;                                   // Random user ID between 2 and 50
        double reliabilityRequirement = (rand() % 51 + 20) / 100.0;     // Random reliability requirement between 0.2 and 0.7

        outputFile << arrivalTime << " " << executionTime << " " << userId << " " << reliabilityRequirement << endl;
    }

    outputFile << numNodes << endl;

    for (int i = 0; i < numNodes; ++i) {
        double failureRate = (rand() % 10 + 1) / 100.0; // Random failure rate between 0.01 and 0.1
        outputFile << failureRate << endl;
    }

    outputFile.close();
}

int main() {
    generateRandomFile("input.txt");
    cout << "Random input file generated successfully." << endl;
    return 0;
}
