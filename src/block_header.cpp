#include "block_header.h"
#include "global.h"

BlockHeader::BlockHeader()
{
    m_data = (unsigned char*)(new char[ENCRIPT_SIZE + 8]);
    memset(m_data, 0, ENCRIPT_SIZE + 8);
}

BlockHeader::~BlockHeader()
{
    if(m_data)
    {
        delete [] m_data;
        m_data = nullptr;
    }
}

void BlockHeader::Read(int fd, unsigned int size, unsigned int& cursor)// to do
{

    //d
    lseek(fd,cursor, SEEK_SET);
    read(fd, &m_posBeg, sizeof(m_posBeg));
    read(fd, &m_posEnd, sizeof(m_posEnd));//unsigned int m_ifEncrypted;
    read(fd, &m_ifEncrypted, sizeof(m_ifEncrypted));
    read(fd, &m_originalSize, sizeof(m_originalSize));
    read(fd, &m_rawDataSize, sizeof(m_rawDataSize));
    cursor += sizeof(unsigned int) * 5;
    ReadContent(fd, m_posEnd - m_posBeg, cursor);

    //e

}

void BlockHeader::Write(int fd, unsigned int size, unsigned int& cursor)// to do
{
    unsigned char buff[BYTES] = {0};
    lseek(fd,cursor, SEEK_SET);
    unsigned char* dest = buff;
    memcpy(dest, (const void*)&m_posBeg, sizeof(m_posBeg));
    dest += sizeof(m_posBeg);
    memcpy(dest, (const void*)&m_posEnd, sizeof(m_posEnd));
    dest += sizeof(m_posEnd);
    memcpy(dest, (const void*)&m_ifEncrypted, sizeof(m_ifEncrypted));
    dest += sizeof(m_ifEncrypted);
    memcpy(dest, (const void*)&m_originalSize, sizeof(m_originalSize));
    dest += sizeof(m_originalSize);
    memcpy(dest, (const void*)&m_rawDataSize, sizeof(m_rawDataSize));
    dest += sizeof(m_rawDataSize);
    memcpy(dest, (const void*)&m_data, m_originalSize);
    write(fd,buff,BYTES);
}

void BlockHeader::ReadContent(int fd, unsigned int size, unsigned int& cursor)
{
    // block size less than 512bytes don not need to encrypt
    unsigned int count = 0, nRead = 0;
    static const int BUF_SIZE = 1024;
    unsigned char buff[BUF_SIZE] = {0};
    lseek(fd, cursor, SEEK_SET);
    unsigned char* target = m_data;
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
        target += count;
        memcpy(target, buff, nRead);
        count += nRead;
    }
    cursor += size;
}

void BlockHeader::WriteContent(int fd, unsigned int size, unsigned int& cursor)
{
    lseek(fd, cursor, SEEK_SET);
    unsigned char* src = m_data;
    write(fd, src, size);
    cursor += size;
}
