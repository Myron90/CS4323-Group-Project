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
# include <semaphore.h>
using namespace std;

// Define intersection class
class Intersection {
public:
    string name;
    unsigned int capacity;
    bool is_mutex;
    unsigned int train_count = 0;

    mutex mtx;
    sem_t semaphore;
    condition_variable cv;

    // Constructor
    Intersection(string name, unsigned int capacity) : name(name), capacity(capacity), is_mutex(capacity==1) {
        if(!is_mutex){
            sem_init(&semaphore, 0, capacity);
        }
    }
    
    vector<Train*> trains_in_intersection;
    
    // Acquire train, called by the travel function
    void acquire(Train* train) {
        if(is_mutex){ // Mutex method
            unique_lock<mutex> lock(mtx); // Unsure about this
            // TODO: add communication
            trains_in_intersection.push_back(train);
            train_count++;
        } else { // Semaphore method
            // TODO: add communication
            sem_wait(&semaphore); // Unsure about this
            trains_in_intersection.push_back(train);
            train_count++;
        }
    }
    
    // Release train, called by the travel function
    void release(Train* train) {
        if(is_mutex){
            // TODO: add communication
            // TODO: add any necessary mutex code here
            trains_in_intersection.erase(find(trains_in_intersection.begin(), trains_in_intersection.end(), train));
            train_count--;
        } else {
            // TODO: add communication
            sem_post(&semaphore);
            trains_in_intersection.erase(find(trains_in_intersection.begin(), trains_in_intersection.end(), train));
        }
    }

};

// Define train class
class Train {
public:
    string name;
    vector<Intersection*> route;
    Intersection current_location; // I think this will be helpful for the travel function

    // Constructor
    Train(string name, vector<Intersection*> route): name(name), route(route) {}

};

// Parse the text
unordered_map<string, Intersection*> parseIntersections(const string& filename){
    // Create intersections unordered map so trains can access intersections by name
    unordered_map<string, Intersection*> intersections;
    ifstream file(filename);
    string line;
    
    // Works for any number of intersections
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
        string intersection;
        vector<Intersection*> route;

        getline(ss, name, ',');
        // Adjusted to work for any number of intersections
        while(getline(ss, intersection, ',')){
            route.push_back(intersections[intersection]);
        ss >> intersection;
        route.push_back(intersections[intersection]);

        trains[name] = new Train(name, route);
    }

    return trains;
}

int main() { 
    unordered_map<string, Intersection*> intersections = parseIntersections("intersections.txt");
    unordered_map<string, Train*> trains = parseTrains("trains.txt", intersections);
}