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
    unsigned int capacity;
    bool is_mutex = capacity == 1 ? true : false;

    // Constructor
    Intersection(string n, unsigned int c) : name(n), capacity(c) {}
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
    int count = 0;
    
    while(getline(file, line)) { // While there is a next line
        stringstream ss(line);
        string name;
        unsigned int capacity;

        getline(ss, name, ':');
        ss >> capacity;

        cout << "Name : " << name << " | Capacity: " << capacity << endl;
        
        count ++;
        if(count == 1){
            Intersection intersectionA(name, capacity);
        } else if(count == 2){
            Intersection intersectionB(name, capacity);
        } else if(count == 3){
            Intersection intersectionC(name, capacity);
        } else if(count == 4){ 
            Intersection intersectionD(name, capacity);
        } else if(count == 5){
            Intersection intersectionE(name, capacity);
        } else {
            printf("ERROR");
        }

    }
}

void parseTrains(const string& filename){

}

int main() { 
    parseIntersections("intersections.txt");
    parseTrains("trains.txt");
}