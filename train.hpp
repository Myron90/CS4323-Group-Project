#ifndef TRAIN_FORKING_H
#define TRAIN_FORKING_H
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "parsing.hpp"

int train_forking();

void train_behavior();
#endif