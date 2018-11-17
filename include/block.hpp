#pragma once

#include "global.hpp"
#include "file_header.hpp"
/**
* class Block
* contain data of one file block, read and write function should be used in pair
* block is composed of header, content, tail
* header and tail are encrypted, while the content is original
*/
class Block
{
    public:

        Block(istream& is, ostream& os, int totalBlock);
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
        /*<to hold encrypted header data or decrypted header data*/
        unsigned char* m_headerData;
        /*<to hold encrypted tail data or decrypted tail data*/
        unsigned char* m_tailData;
        unsigned char* m_data;
        /*<during the reading a block record the total bytes of the block (in case of the last block) */
        unsigned int m_bytes;
        /*<encrypt or decrypt*/
        unsigned int m_usage;
        unsigned int m_totalBlocksNum;
        unsigned int m_idx;

        istream& m_is;
        ostream& m_os;
};
