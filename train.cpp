/*
Group B
Author: Myron Peoples
Email: myron.peoples@okstate.edu
Date: 
Description: 
*/
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int train_forking() {
    // Declare the names of the trains and their routes manually
    std::string train1Name = "Train1";
    std::string train2Name = "Train2";
    std::string train3Name = "Train3";
    std::string train4Name = "Train4";
    
    std::string train1Route[] = {"IntersectionA", "IntersectionB", "IntersectionC"};
    std::string train2Route[] = {"IntersectionB", "IntersectionD", "IntersectionE"};
    std::string train3Route[] = {"IntersectionC", "IntersectionD", "IntersectionA"};
    std::string train4Route[] = {"IntersectionE", "IntersectionB", "IntersectionD"};
    
    // Fork a child process for Train 1
    pid_t pid1 = fork();
    
    if (pid1 == 0) {
        // This is the child process for Train 1
        std::cout << train1Name << " starting its journey!" << std::endl;
        
        for (int i = 0; i < 3; ++i) {
            std::cout << train1Name << " passing through " << train1Route[i] << std::endl;
            sleep(1); // Sleep for 1 second to simulate time passing
        }
        
        std::cout << train1Name << " completed its route!" << std::endl;
        exit(0); // End child process for Train 1
    }
    
    // Fork a child process for Train 2
    pid_t pid2 = fork();
    
    if (pid2 == 0) {
        // This is the child process for Train 2
        std::cout << train2Name << " starting its journey!" << std::endl;
        
        for (int i = 0; i < 3; ++i) {
            std::cout << train2Name << " passing through " << train2Route[i] << std::endl;
            sleep(1); // Sleep for 1 second to simulate time passing
        }
        
        std::cout << train2Name << " completed its route!" << std::endl;
        exit(0); // End child process for Train 2
    }
    
    // Fork a child process for Train 3
    pid_t pid3 = fork();
    
    if (pid3 == 0) {
        // This is the child process for Train 3
        std::cout << train3Name << " starting its journey!" << std::endl;
        
        for (int i = 0; i < 3; ++i) {
            std::cout << train3Name << " passing through " << train3Route[i] << std::endl;
            sleep(1); // Sleep for 1 second to simulate time passing
        }
        
        std::cout << train3Name << " completed its route!" << std::endl;
        exit(0); // End child process for Train 3
    }
    
    // Fork a child process for Train 4
    pid_t pid4 = fork();
    
    if (pid4 == 0) {
        // This is the child process for Train 4
        std::cout << train4Name << " starting its journey!" << std::endl;
        
        for (int i = 0; i < 3; ++i) {
            std::cout << train4Name << " passing through " << train4Route[i] << std::endl;
            sleep(1); // Sleep for 1 second to simulate time passing
        }
        
        std::cout << train4Name << " completed its route!" << std::endl;
        exit(0); // End child process for Train 4
    }
    
    // Parent process waits for all child processes to finish
    wait(NULL); // Wait for Train 1 to finish
    wait(NULL); // Wait for Train 2 to finish
    wait(NULL); // Wait for Train 3 to finish
    wait(NULL); // Wait for Train 4 to finish
    
    std::cout << "All trains have completed their routes!" << std::endl;
    
    return 0;
}

