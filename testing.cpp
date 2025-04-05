/*
Group B
Author: Logan Dawes
Email: logan.dawes@okstate.edu
Date: 04/05/2025

Description: Generates a random initialization of intersections.txt and trains.txt for automated testing.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <set>

void generateConfig() {
    // File: intersections.txt
    std::ofstream intersectionsFile("intersections.txt");

    // Random Seed
    std::srand(std::time(0));

    // Generate a 1-10 intersections
    int numIntersections = (std::rand() % 10) + 1;
    printf("Number of intersections: %d\n", numIntersections);

    // Vector for intersections
    std::vector<std::string> intersections;

    for (int i = 0; i < numIntersections; ++i) {
        // Generate 1-3 capacity per intersection
        int capacity = (std::rand() % 3) + 1;
        printf("Intersection %d capacity: %d\n", i, capacity);

        // Set intersection number as alphabetical
        char alpha = 'A' + i;

        // Add intersection to vector
        std::string intersectionName = strncat("Intersection", &alpha, 1);
        intersections.push_back(intersectionName);

        // Write to file
        intersectionsFile << intersectionName << ':' << capacity << std::endl;
    }
    intersectionsFile.close();

    // File: trains.txt
    std::ofstream trainsFile("trains.txt");

    // Random Seed
    std::srand(std::time(0));

    // Generate a 1-10 trains
    int numTrains = (std::rand() % 10) + 1;
    printf("Number of trains: %d\n", numTrains);

    for (int i = 0; i < numTrains; ++i) {
        // Generate random intersection number for route
        int numRouteIntersections = (std::rand() % numIntersections) + 1;

        // Set for route intersections
        std::set<std::string> route;

        // Write to file
        trainsFile << "Train" << i+1 << ':';

        // Generate Route
        for (int j = 0; j < numRouteIntersections; ++j) {
            std::string selectedIntersection;
            do {
                // Aquire random intersection index to select intersection
                int intersectionIndex = std::rand() % numIntersections;
                selectedIntersection = intersections[intersectionIndex];
            }
            // Go through route to ensure no duplicates
            while (route.find(selectedIntersection) != route.end());

            // Add to route
            route.insert(selectedIntersection);

            // Comma seperated entries
            if (j != 0) {
                trainsFile << ",";
            }

            // Write route
            trainsFile << selectedIntersection;
        }
        trainsFile << std::endl;

    }
    trainsFile.close();
}

int main(){
    generateConfig();
    return 0;
}
