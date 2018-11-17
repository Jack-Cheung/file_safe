#pragma once

#include "global.h"
#include "file_header.h"
/*
* class Block
* contain data of one file block, read and write function should be used in pair
*/
class Block
{
    public:

        Block(int ifd, int ofd);
        ~Block();

        void Clear();

        void Read(unsigned int nIdx, unsigned int nTotalNum, unsigned int type = ORIGIN);
        void Write(unsigned int type = ORIGIN);
        void Encrypt();
        void Decrypt();

        unsigned int GetSize();

    protected:

    private:

        void DoEncrypt();
        void DoDecrypt();

        unsigned char* m_headerData;
        unsigned char* m_contentData;
        unsigned char* m_tailData;
        unsigned char* m_data;

        unsigned int m_bytes;
        unsigned int m_fileType;// encrypt or decrypt
        unsigned int m_totalBlocksNum;
        unsigned int m_idx;

        int m_ifd;
        int m_ofd;
};
