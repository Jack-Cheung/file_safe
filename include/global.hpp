/*
*   an encrypted file :
*   
*   file_header             one block                                   and several other blocks ...                    the last block tends to smaller than 10M
*   _____________________   ________________________________________                                    ________________________________________         ________________________________________ 
*   |num of blocks| 8bytes| |block header(encrypted)  | 128 bytes   |                                   |block header(encrypted)  | 128 bytes   |       |content data(original )  | <128*2 B    |
*   |_____________|______ | |_________________________|_____________|                                   |_________________________|_____________|       |_________________________|_____________|
*                           | content data (original) |10M - 128*2B |                                   | content data (original) |all left data|  or 
*                           |_________________________|_____________|     ...   ...                     |_________________________|_____________|
*                           |block tail (encrypted)   | 128 B       |                                   |block tail (encrypted)   | 128 B       |
*                           |_________________________|_____________|                                   |_________________________|_____________|
*
*/

#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/types.h>//
#include <sys/stat.h>//
#include <fcntl.h>//
#include <unistd.h>//
#include <cmath>
#include <cstring>

using namespace std;

static const unsigned int FILE_HEARER_SIZE = 8;
static const unsigned int BLOCK_SIZE = 10 * 1024 * 1024; // origin file division
static const unsigned int ENCRIPT_SIZE = 128;
static const unsigned int UNENCRIPT_SIZE = BLOCK_SIZE - ENCRIPT_SIZE * 2;
//static const unsigned int MODE = S_IRWXU | S_IXGRP | S_IROTH | S_IXOTH;
static const int ENCRYPT = 0;
static const int ORIGIN = 1;
static char KEY[] = "QiaoWang";
#endif // GLOBAL_H_INCLUDED
