#include "block_tail.h"
#include "global.h"

void BlockTail::Read(unsigned int& cursor)
{
    cursor += BYTES;
}

void BlockTail::Write(int fd, unsigned int& cursor)
{
    unsigned char buff[BYTES] = {0};
    lseek(fd,cursor, SEEK_SET);
    write(fd,buff,BYTES);
    cursor += BYTES;
}
