#include "block_content.h"
#include <rpc/des_crypt.h>

BlockContent::BlockContent()
{
    //ctor
    m_data = new unsigned char[BLOCK_SIZE];
    memset(m_data, 0, BLOCK_SIZE * sizeof(unsigned char));
}

BlockContent::~BlockContent()
{
    //dtor
    if(m_data)
        delete [] m_data;
}

void BlockContent::Read(int fd, unsigned int size, unsigned int& cursor)//add a parameter direction 0-encrypt 1-decrypt
{
    unsigned int count = 0, nRead = 0;
    static const int BUF_SIZE = 1024;
    unsigned char buff[BUF_SIZE] = {0};
    lseek(fd, cursor, SEEK_SET);
    unsigned char* target = nullptr;
    while(true)
    {
        if(count >= size)
            break;
        if(count + BUF_SIZE > size)
        {
            nRead = read(fd, buff, size % BUF_SIZE);
        }
        else
        {
            nRead = read(fd, buff, BUF_SIZE);
        }
        if(nRead <= 0)
            break;
        target = m_data + count;
        memcpy(target, buff, nRead);
        count += nRead;
    }
    cursor += size;
}

void BlockContent::Write(int fd, unsigned int size, unsigned int& cursor)
{
    lseek(fd, cursor, SEEK_SET);
    unsigned char* src = m_data;
    write(fd, src, size);
    cursor += size;
}

void BlockContent::Clear()
{
    memset(m_data, 0, BLOCK_SIZE * sizeof(unsigned char));
}