#ifndef FILEHEADER_H
#define FILEHEADER_H
#include "global.hpp"

class FileHeader
{
public:
    FileHeader();
    ~FileHeader() = default;
    void Clear();
    //void Read(int fd);//
    //void Write(int fd);//

    void Read(istream& is);
    void Write(ostream& os);
    /**<amount of blocks*/
    int64_t m_number;
    /**<memery space this header take place*/
    static const int BYTES = FILE_HEARER_SIZE;
};

#endif // FILEHEADER_H
