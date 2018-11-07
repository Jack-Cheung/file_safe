#include "file_header.h"
#include "global.h"
FileHeader::FileHeader()
{
    //ctor
    Clear();
}

void FileHeader::Clear()
{
    m_number = 0;
}

void FileHeader::Read(int fd)
{
    read(fd, &m_number, sizeof(m_number));
}

void FileHeader::Write(int fd)
{
    unsigned char buff[BYTES] = {0};
    memcpy(buff, (const void*)&m_number, sizeof(m_number));
    lseek(fd,0, SEEK_SET);
    write(fd,buff,BYTES);
}
