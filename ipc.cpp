/*
Group B
Author: Richard Powers
Email: richard.w.powers@okstate.edu
Date: 4/1/2025

Description: 
*/

// Create shared memory

// Create message queues

// Store the mutexes and semaphores, set the values to match specified capacities

#include "ipc.hpp"

#define shm_name "/shared_mem"
#define mq_name "/msg_queue"
#define SHARED_MEMORY_SIZE sizeof(int)

int ipc_setup() {
    
    // Shared Memory
    const int size = 1024;
    int shm_fd;

    long long int * ptr;

    shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666); // Create shared memory

    ftruncate(shm_fd, size); // Set memory size
    ptr = (long long int*)mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0); // Shared memory pointer

    // Message Queue
    key_t key;
    int msgid;

    key = ftok(mq_name, 'A');

    msgid = msgget(key, 0666 | IPC_CREAT);

    long mtype = 1;
    msg_request message;
    msgrcv(msgid, &message, sizeof(message), mtype, 0);

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}