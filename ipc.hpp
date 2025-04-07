#ifndef IPC_HPP
#define IPC_HPP

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/msg.h>

#define shm_name "/shared_mem"
#define mq_name "/msg_queue"
#define SHARED_MEMORY_SIZE sizeof(int)

struct msg_request {
    long mtype;
    int train_id;
    char intersection[50];
};

extern msg_request message;

int ipc_setup();

#endif
