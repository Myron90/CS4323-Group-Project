/*
Group B
Author: Evelyn Wilson
Email: evelyn.wilson@okstate.edu
Date: April 2, 2025

Description: This code reads the intersections and trains from their respective text files into objects.
It also defines the basic methods
*/

#include "parsing.h"

using namespace std;

class Train; // Forward declaration for the vector in Intersection

// Define intersection class
class Intersection {
public:
    string name;
    unsigned int capacity;
    bool is_mutex;
    unsigned int train_count = 0;

    pthread_mutex_t mtx;
    sem_t semaphore;
    condition_variable cv;

    // Constructor
    Intersection(string name, unsigned int capacity) : name(name), capacity(capacity), is_mutex(capacity==1), train_count(0) {
        if(is_mutex){ // Create mutex
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutex_attr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
            pthread_mutex_init(&mtx, &attr);
        } else { // Create semaphore
            sem_init(&semaphore, 1, capacity);
        }
    }
    
    vector<Train*> trains_in_intersection;
    
    // Acquire train, called in travel function. Returns whether it was successfully acquired.
    bool acquire(Train* train) {
        if(is_mutex){ // Mutex method
            if(train_count == 0) { // If intersection is empty
                pthread_mutex_lock(&mtx);
                trains_in_intersection.push_back(train);
                train_count++;
                return true; // Train was acquired
            } else {
                return false; // Train was not acquired
            }
        } else { // Semaphore method
            if (train_count < capacity) { // If there is room for another train
                sem_wait(&semaphore); // Unsure about this
                trains_in_intersection.push_back(train);
                train_count++; // Train was acquired
            } else {
                return false; // Train was not acquired
            }
            
        }
    }
    
    // Release train, called by the travel function. Returns whether it was successfully released.
    bool release(Train* train) {
        // Find the specific train in the intersection
        auto found_train = find(trains_in_intersection.begin(), trains_in_intersection.end(), train);
        if(found_train != trains_in_intersection.end()) { // Unlock mutex and update semaphore for intersection
            if(is_mutex){
                pthread_mutex_unlock(&mtx);
                return true;
            } else {
                sem_post(&semaphore);
                return true;
            }
        } else {
            cout << "Error: Train not found";
            return false;
        }
    }

    bool isOpen() { // Returns whether the intersection has an availability or not.
        is_mutex ? train_count == 0 : train_count < capacity;
    }
};

// Define train class
class Train {
public:
    string name;
    vector<Intersection*> route;
    Intersection* current_location = nullptr; // I think this will be helpful for the travel function

    // Constructor
    Train(string name, vector<Intersection*> route): name(name), route(route) {}

};

// Parse intersections.txt into objects of type Intersection
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

        // Debugging parsing, remove in submission
        cout << "Name : " << name << " , Capacity: " << capacity << endl;
        
        intersections[name] = new Intersection(name, capacity);
    }
    
    return intersections;
}

// Parse trains.txt into objects of type Train
unordered_map<string, Train*> parseTrains(const string& filename, unordered_map<string, Intersection*>& intersections){
    ifstream file(filename);
    string line;
    unordered_map<string, Train*> trains;
 
    while(getline(file, line)) { // While there is a next line
        stringstream ss(line);
        string name;
        string intersection;
        vector<Intersection*> route;

        getline(ss, name, ':');
        // Adjusted to work for any number of intersections
        while(getline(ss, intersection, ',')){
            route.push_back(intersections[intersection]);
        ss >> intersection;
        route.push_back(intersections[intersection]);

        // Debugging parsing, remove in submission
        cout << "Train: " << name << " | Route: ";
        for (auto* intersection : route) {
            cout << intersection->name << " ";
        }
        cout << endl;
        }

        trains[name] = new Train(name, route);
    }

    return trains;
}

void parsing() { 
    unordered_map<string, Intersection*> parseIntersections(const string& filename);
    unordered_map<string, Train*> parseTrains(const string& filename, unordered_map<string, Intersection*>& intersections);
}