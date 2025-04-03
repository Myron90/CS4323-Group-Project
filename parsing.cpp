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
#include <unordered_map>
using namespace std;

// Define intersection class
class Intersection {
public:
    string name;
    unsigned int capacity;
    bool is_mutex;

    // Constructor
    Intersection(string name, unsigned int capacity) : name(name), capacity(capacity), is_mutex(c==1) {}
    
    // TODO: define Trains vector 
    // TODO: Define mutex and semaphore functions to add and remove trains
};

// Define train class
class Train {
public:
    string name;

    // Create a vector to store the train's intersections
    vector<Intersection*> route;

    // Constructor
    Train(string name, vector<Intersection*> route): name(name), route(route) {}

    // TODO: Define methods to acquire and release intersections
};

// Parse the text
unordered_map<string, Intersection*> parseIntersections(const string& filename){
    // Create intersections unordered map so trains can access intersections by name
    unordered_map<string, Intersection*> intersections;
    ifstream file(filename);
    string line;
    
    while(getline(file, line)) { // While there is a next line
        stringstream ss(line);
        string name;
        unsigned int capacity;

        getline(ss, name, ':');
        ss >> capacity;

        cout << "Name : " << name << " , Capacity: " << capacity << endl;
        
        intersections[name] = new Intersection(name, capacity);
    }
    
    return intersections;
}

unordered_map<string, Train*> parseTrains(const string& filename, unordered_map<string, Intersection*>& intersections){
    ifstream file(filename);
    string line;
    unordered_map<string, Train*> trains;
 
    while(getline(file, line)) { // While there is a next line
        stringstream ss(line);
        string name;
        string intersection1, intersection2, intersection3;
        vector<Intersection*> route;

        getline(ss, name, ',');
        getline(ss, intersection1, ',');
        getline(ss, intersection2, ',');
        ss >> intersection3;

        cout << "Name : " << name << " , Intersections: " << intersection1 << ", " << intersection2 << ", and " << intersection3 << endl;
        // Read intersections into a route, pulling from the intersections unordered map
        route.push_back(intersections[intersection1]);
        route.push_back(intersections[intersection2]);
        route.push_back(intersections[intersection3]);

        trains[name] = new Train(name, route);
    }
    
    return trains;
}

int main() { 
    unordered_map<string, Intersection*> intersections = parseIntersections("intersections.txt");
    unordered_map<string, Train*> trains = parseTrains("trains.txt", intersections);
}