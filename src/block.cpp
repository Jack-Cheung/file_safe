#include "block.hpp"
#include <rpc/des_crypt.h>// openssl


Block::Block(istream& is, ostream& os, int totalBlock):m_is(is),m_os(os)
{
    m_headerData = new unsigned char[ENCRIPT_SIZE];
    //m_contentData = new unsigned char[UNENCRIPT_SIZE];
    m_tailData = new unsigned char[ENCRIPT_SIZE];
    m_data = new unsigned char[BLOCK_SIZE];
    if(!m_headerData /* || !m_contentData */ || !m_tailData || !m_data)
    {
        throw "low memory!";
    }
}


Block::~Block()
{
    if(m_headerData)
        delete [] m_headerData;
    if(m_tailData)
        delete [] m_tailData;
    if(m_data)
        delete [] m_data;
}

void Block::Clear()
{
    //printf("clear =%p   %p   %p   %p", m_headerData, m_contentData, m_tailData, m_data);
    memset(m_headerData, 0, ENCRIPT_SIZE * sizeof(unsigned char));
    memset(m_tailData, 0, ENCRIPT_SIZE * sizeof(unsigned char));
    memset(m_data, 0, BLOCK_SIZE * sizeof(unsigned char));
    m_bytes = 0;
    m_usage = 0;
    m_totalBlocksNum = 0;
    m_idx = 0;
}

void Block::Read(unsigned int nIdx, unsigned int nTotalNum, unsigned int type )
{
    unsigned int cursor = 0;
    m_totalBlocksNum = nTotalNum;
    m_idx = nIdx;
    m_usage = type;
    if(m_usage == ENCRYPT)
    {
        cursor = m_idx * BLOCK_SIZE + FileHeader::BYTES;
    }
    else
    {
        cursor = m_idx * BLOCK_SIZE;
    }
    m_is.seekg(cursor);
    if(nIdx < nTotalNum - 1)
    {
        m_is.read((char*)m_data, BLOCK_SIZE);
        m_bytes = BLOCK_SIZE;
    }
    else
    {
        unsigned int count = 0, nRead = 0;
        static const int BUF_SIZE = 1024;
        unsigned char buff[BUF_SIZE] = {0};
        unsigned char* target = nullptr;
        while(true)
        {
            if(count >= BLOCK_SIZE)
                break;
            if(count + BUF_SIZE > BLOCK_SIZE)
            {
                nRead = m_is.readsome((char*)buff, BLOCK_SIZE % BUF_SIZE);
            }
            else
            {
                nRead = m_is.readsome((char*)buff, BUF_SIZE);
            }
            if(nRead <= 0)
                break;
            target = m_data + count;
            memcpy(target, buff, nRead);
            count += nRead;
        }
        m_bytes = count;
    }
}

void Block::Write(unsigned int type /*= ORIGINAL*/)
{
    unsigned int cursor = 0;
    if(m_usage == ENCRYPT)
    {
        cursor = m_idx * BLOCK_SIZE;
    }
    else
    {
        cursor = m_idx * BLOCK_SIZE + FileHeader::BYTES;
    }
    m_os.seekp(cursor);
    if(m_bytes >= ENCRIPT_SIZE * 2)
    {
        memcpy(m_data, m_headerData, ENCRIPT_SIZE);
        memcpy(m_data + m_bytes - ENCRIPT_SIZE, m_tailData, ENCRIPT_SIZE);
    }
    m_os.write((const char*)m_data, m_bytes);
}

void Block::Encrypt()
{
    if(m_totalBlocksNum - 1 == m_idx)
    {
        // last block
        unsigned int bytes = GetSize();
        if(bytes >= ENCRIPT_SIZE * 2)
        {
            DoEncrypt();
        }

    }
    else
    {
        DoEncrypt();
    }
}
//same
void Block::Decrypt()
{
    if(m_totalBlocksNum - 1 == m_idx)
    {
        // last block
        unsigned int bytes = GetSize();
        if(bytes >= ENCRIPT_SIZE * 2)
        {
            DoDecrypt();
        }
    }
    else
    {
        DoDecrypt();
    }
}

unsigned int Block::GetSize()
{
    return m_bytes;
}

void Block::DoEncrypt()
{
    memcpy(m_headerData, m_data, ENCRIPT_SIZE);
    memcpy(m_tailData, m_data + m_bytes - ENCRIPT_SIZE, ENCRIPT_SIZE);
    ecb_crypt(KEY, (char*)m_headerData, ENCRIPT_SIZE, DES_ENCRYPT);
    ecb_crypt(KEY, (char*)m_tailData, ENCRIPT_SIZE, DES_ENCRYPT);
    //printf("%s", m_headerData);
}

void Block::DoDecrypt()
{
    memcpy(m_headerData, m_data, ENCRIPT_SIZE);
    memcpy(m_tailData, m_data + m_bytes - ENCRIPT_SIZE, ENCRIPT_SIZE);
    ecb_crypt(KEY, (char*)m_headerData, ENCRIPT_SIZE, DES_DECRYPT);
    ecb_crypt(KEY, (char*)m_tailData, ENCRIPT_SIZE, DES_DECRYPT);
}
