#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cmath>
#include <cstring>

using namespace std;

static const unsigned int BLOCK_SIZE = 10 * 1024 * 1024; // origin file division
static const unsigned int ENCRIPT_SIZE = 128;
static const unsigned int UNENCRIPT_SIZE = BLOCK_SIZE - ENCRIPT_SIZE * 2;
static const unsigned int MODE = S_IRWXU | S_IXGRP | S_IROTH | S_IXOTH;
static const int ENCRYPT = 0;
static const int ORIGIN = 1;
static char KEY[] = "QiaoWang";
#endif // GLOBAL_H_INCLUDED
