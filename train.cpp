/*
Group B
Author: Myron Peoples
Email: myron.peoples@okstate.edu
Date: 
Description: 
*/
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <vector>
#include <cstring>
#include <ctime>
#include <cstdlib>

// REFERENCE FOR: IPC MESSAGE QUEUES - Logan
// Message structure for communication with the server
struct msg_request {
    long mtype;        // Message type (ACQUIRE or RELEASE)
    int train_id;      // ID of the train
    char intersection[50];  // Intersection name
};

// REFERENCE FOR: IPC MESSAGE QUEUES - Logan
// Message structure for server's response to the train
struct msg_response {
    long mtype;       // Message type (GRANT, WAIT, DENY)
    int train_id;     // ID of the train
    char intersection[50]; // Intersection name
};

class Train {
public:
    int train_id;                        // Train identifier
    std::vector<std::string> route;      // List of intersections this train must pass through
    int request_queue_id;                // Message queue for requests to the server
    int response_queue_id;               // Message queue for server responses

    Train(int id, std::vector<std::string> r, int req_q_id, int resp_q_id) {
        train_id = id;
        route = r;
        request_queue_id = req_q_id;
        response_queue_id = resp_q_id;
    }

    // REFERENCE FOR: IPC MESSAGE QUEUES - Logan
    // Function to request an intersection from the server
    void requestIntersection(const char* intersection_name) {
        msg_request request;
        request.mtype = 1; // Assuming 1 is the type for 'ACQUIRE'
        request.train_id = train_id;
        strncpy(request.intersection, intersection_name, sizeof(request.intersection));

        msgsnd(request_queue_id, &request, sizeof(request) - sizeof(long), 0);  // Send request
    }

    // REFERENCE FOR: IPC MESSAGE QUEUES - Logan
    // Function to wait for the server's response
    void waitForResponse() {
        msg_response response;
        msgrcv(response_queue_id, &response, sizeof(response) - sizeof(long), train_id, 0);  // Receive response
        if (response.mtype == 1) {
            std::cout << "Train " << train_id << " granted access to intersection " << response.intersection << std::endl;
        } else if (response.mtype == 2) {
            std::cout << "Train " << train_id << " waiting for intersection " << response.intersection << std::endl;
        }
    }

    // REFERENCE FOR: TRAIN BEHAVIOR - Logan
    // Simulate train traversing the intersection
    void traverseIntersection(const char* intersection_name) {
        std::cout << "Train " << train_id << " is traversing intersection " << intersection_name << std::endl;
        sleep(2);  // Simulate time spent traversing the intersection
    }

    // REFERENCE FOR: TRAIN BEHAVIOR - Logan
    // Simulate train's journey
    void travel() {
        for (const auto& intersection : route) {
            requestIntersection(intersection.c_str());   // Request intersection
            waitForResponse();                           // Wait for server response
            traverseIntersection(intersection.c_str()); // Simulate traversing intersection
        }
    }
};

// REFERENCE FOR: TRAIN FORKING (this file) - Logan
void fork_train_processes(std::vector<Train> &trains) {
    for (auto &train : trains) {
        pid_t pid = fork();
        if (pid == -1) {
            std::cerr << "Error forking process for Train " << train.train_id << std::endl;
            exit(1);
        }

        if (pid == 0) {
            // Child process: Train's journey starts here
            train.travel();
            exit(0);  // Exit child process after completing its journey
        }
    }
}

// REFERENCE FOR: SERVER - Logan
int main() {
    // Setup message queues for communication between server and trains
    key_t request_key = ftok("request_queue", 65);
    key_t response_key = ftok("response_queue", 75);

    int request_queue_id = msgget(request_key, 0666 | IPC_CREAT);
    int response_queue_id = msgget(response_key, 0666 | IPC_CREAT);

    if (request_queue_id == -1 || response_queue_id == -1) {
        std::cerr << "Error creating message queues." << std::endl;
        exit(1);
    }

    // Example route data for trains (you will typically read this from a file)
    std::vector<std::string> route1 = {"IntersectionA", "IntersectionB", "IntersectionC"};
    std::vector<std::string> route2 = {"IntersectionB", "IntersectionD", "IntersectionE"};

    // Create trains
    std::vector<Train> trains = {
        Train(1, route1, request_queue_id, response_queue_id),
        Train(2, route2, request_queue_id, response_queue_id)
    };

    // Fork train processes
    fork_train_processes(trains);

    // Wait for all child processes to finish
    for (auto &train : trains) {
        wait(NULL);
    }

    // Cleanup message queues after all trains have finished
    msgctl(request_queue_id, IPC_RMID, NULL);
    msgctl(response_queue_id, IPC_RMID, NULL);

    return 0;
}


