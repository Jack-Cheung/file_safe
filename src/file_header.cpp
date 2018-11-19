#include "file_header.hpp"
#include "global.hpp"
FileHeader::FileHeader()
{
    Clear();
}

void FileHeader::Clear()
{
    m_number = 0;
}


void FileHeader::Read(istream& is)
{
    is.read((char*)&m_number, sizeof(m_number));
}

void FileHeader::Write(ostream& os)
{
    unsigned char buff[BYTES] = {0};
    memcpy(buff, (const void*)&m_number, sizeof(m_number));
    os.write((const char*)buff,BYTES);
}
