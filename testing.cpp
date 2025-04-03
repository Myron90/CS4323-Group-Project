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

void generateIntersections() {
    // File: intersections.txt
    std::ofstream file("intersections.txt");

    // Random Seed
    std::srand(std::time(0));

    // Generate a 1-10 intersections
    int numIntersections = (std::rand() % 10) + 1;

    for (int i = 0; i < numIntersections; ++i) {
        // Generate 1-3 capacity per intersection
        int capacity = (std::rand() % 3) + 1;

        // Set intersection number as alphabetical
        char alpha = 'A' + i;

        // Write to file
        file << "Intersection" << alpha << ':' << capacity << std::endl;
    }
    file.close();
}