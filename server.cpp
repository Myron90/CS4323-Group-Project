/*
Group B
Author: Gavin Zlatar
Email: gavin.zlatar@okstate.edu
Date: 4/5/2025

Description: The 'server.cpp' file creates a multithreaded server that processes requests from child processes while
checking for deadlocks. Threads handle requests and update a resource graph, which tracks resource dependencies. 
The program uses this graph to detect deadlocks by looking for cycles. If a deadlock is found, it alerts the user; 
otherwise, it confirms everything is running smoothly. Mutexes and condition variables ensure threads work safely 
and efficiently.
*/
#include "parsing.h"
#include "logging.h"
#include "ipc.h"
#include <iostream>
#include <vector>
#include <map>
#include <mutex>
#include <thread>
#include <condition_variable>

void handleRequest(int processID);
bool detectDeadlock(const std::map<int, std::vector<int>>& resourceGraph);

std::mutex mtx;
std::condition_variable cv;

// simulated resource graph for detecting deadlocks
std::map<int, std::vector<int>> resourceGraph;

int main() {
    std::cout << "Server started...\n";
    
    auto intersections = parseIntersections("intersections.txt");
    auto trains = parseTrains("trains.txt", intersections);
    
    // example child processes communicating with the server
    std::vector<int> childProcesses = {1, 2, 3, 4};
    std::vector<std::thread> threads;

    for (int processID : childProcesses) {
        threads.emplace_back(handleRequest, processID);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // deadlock detection statement
    if (detectDeadlock(resourceGraph)) {
        std::cout << "Deadlock detected! Resolving...\n";
        // TO DO: implement deadlock resolution logic here



    } else {
        std::cout << "No deadlock detected. System running smoothly.\n";
    }

    std::cout << "Server shutting down...\n";
    return 0;
}

void handleRequest(int processID) {
    std::unique_lock<std::mutex> lock(mtx);

    
    std::cout << "Handling request from Process " << processID << "\n";
    // simulate resource request (add to resource graph)
    resourceGraph[processID] = {processID + 1}; // xxample dependency
    
    cv.notify_all();
}


bool detectDeadlock(const std::map<int, std::vector<int>>& resourceGraph) {
    // resource allocation graph for deadlock
    std::map<int, bool> visited, recursionStack;

    for (const auto& node : resourceGraph) {
        visited[node.first] = false;
        recursionStack[node.first] = false;
    }

    for (const auto& node : resourceGraph) {
        int processID = node.first;
        if (!visited[processID]) {
            // placeholder for cycle detection:


            bool cycleFound = false; // TO DO: replace with actual algorithm
            if (cycleFound) return true;
        }
    }

    return false;
}
