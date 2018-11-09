#ifndef BLOCKHEADER_H
#define BLOCKHEADER_H

#include "global.h"
class BlockHeader
{
public:
    BlockHeader();
    ~BlockHeader();

    void Read(int fd, unsigned int size, unsigned int& cursor);
    void Write(int fd, unsigned int size, unsigned int& cursor);

    void ReadContent(int fd, unsigned int size, unsigned int& cursor);
    void WriteContent(int fd, unsigned int size, unsigned int& cursor);

    void Encrypt();


    unsigned int m_posBeg;//the index of this block content
    unsigned int m_posEnd;// to do
    unsigned int m_ifEncrypted;
    unsigned int m_originalSize;
    unsigned int m_rawDataSize;
    static const int BYTES = sizeof(unsigned int) * 5 + ENCRIPT_SIZE;// bytes of current header

private:
    unsigned char* m_data;
};

#endif // BLOCKHEADER_H
