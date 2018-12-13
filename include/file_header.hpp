#pragma once
#include "global.hpp"

class FileHeader
{
public:
    FileHeader();
    ~FileHeader() = default;
    void Clear();

    void Read(istream& is);
    void Write(ostream& os);
    /**<amount of blocks*/
    int64_t m_number;
    /**<memery space this header take place*/
    static const int BYTES = FILE_HEARER_SIZE;
};

