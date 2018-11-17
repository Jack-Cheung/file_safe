#pragma once

#include "global.h"
class BlockContent
{
public:
    BlockContent();
    ~BlockContent();
    void Read(int fd, unsigned int size, unsigned int& cursor);
    void Write(int fd,  unsigned int size, unsigned int& cursor);
    void Clear();

private:
      unsigned char* m_data;

};
