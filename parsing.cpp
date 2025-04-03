/*
Group B
Author: Evelyn Wilson
Email: evelyn.wilson@okstate.edu
Date: April 2, 2025

Description: This code reads the intersections and trains from their respective text files into objects.
It also defines the basic methods
*/
#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <string>
#include <mutex>
#include <sstream>
#include <fstream>
using namespace std;

// Define intersection class
class Intersection {
public:
    string name;
    int capacity;
    bool is_mutex;
};

// Define train class
class Train {
public:
    string name;
    Intersection* intersection1;
    Intersection* intersection2;
    Intersection* intersection3;
};

// Parse the text
void parseIntersections(const string& filename){
    ifstream file(filename);
    string line;
    
    while(getline(file, line)) { // While there is a next line
         stringstream ss(line);
         string name;
         int capacity;
         bool is_mutex;

         getline(ss, name, ':');
         ss >> capacity;

         cout << "Name : " << name << " | Capacity: " << capacity << endl;
        
        if(capacity == 1){
            is_mutex = true;
        } else {
            is_mutex = false;
        }
    }
}

void parseTrains(const string& filename){

}

int main() { 
    parseIntersections("intersections.txt");
    parseTrains("trains.txt");
}