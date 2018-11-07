#include "block_content.h"
#include <rpc/des_crypt.h>

BlockContent::BlockContent()
{
    //ctor
    m_data = new unsigned char[BLOCK_SIZE];
    memset(m_data, 0, BLOCK_SIZE * sizeof(unsigned char));
}

BlockContent::~BlockContent()
{
    //dtor
    if(m_data)
        delete [] m_data;
}

void BlockContent::Read(int fd, unsigned int size, unsigned int& cursor, int direction)//add a parameter direction 0-encrypt 1-decrypt
{
    unsigned int count = 0, nRead = 0;
    static const int BUF_SIZE = 1024;
    unsigned char buff[BUF_SIZE] = {0};
    lseek(fd, cursor, SEEK_SET);
    unsigned char* target = nullptr;
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
        target = m_data + count;
        memcpy(target, buff, nRead);
        count += nRead;
    }
    cursor += size;
}

void BlockContent::Write(int fd, unsigned int size, unsigned int& cursor, int direction)
{
    lseek(fd, cursor, SEEK_SET);
    unsigned char* src = m_data;
    //direction == ENCRYPT ? src = m_encrypedData : src = m_originData;
    write(fd, src, size);
    cursor += size;
}

void BlockContent::Clear()
{
    memset(m_data, 0, BLOCK_SIZE * sizeof(unsigned char));
//    m_plainTextlen = 0;
//    m_cipherTextLen = 0;
}

//unsigned int BlockContent::Encrpt(unsigned int size)
//{
//    base64_encodestate es;
//    base64_init_encodestate(&es);
//    int cnt = 0, pos = 0;
//    cnt = base64_encode_block((const char*)m_originData, size + 1, (char*)m_encrypedData, &es);
//    pos += cnt;
//    cnt = base64_encode_blockend((char*)m_encrypedData + pos, &es);
//    return pos;
//}

//unsigned int RawContent::Encrpt(unsigned int size)
//{
//    m_plainTextlen = size;
//    if(size % 8)
//    {
//        size += 8 - size % 8;
//    }
//    m_cipherTextLen = size;
//    memcpy(m_encrypedData, m_originData, size);
//    ecb_crypt(KEY, (char*)m_encrypedData, size, DES_ENCRYPT);
//    printf("%s", m_encrypedData);
//    return size;
//}

//unsigned int BlockContent::Decrpt(unsigned int size)
//{
//    base64_decodestate s;
//    base64_init_decodestate(&s);
//    int cnt = 0, pos = 0;
//    cnt = base64_decode_block((const char*)m_encrypedData, size, (char*)m_originData, &s);
//    pos += cnt;
//    return pos;
//}

//unsigned int RawContent::Decrpt(unsigned int size)
//{
//    memcpy(m_originData, m_encrypedData, size);
//    ecb_crypt(KEY, (char*)m_originData, size, DES_DECRYPT);
//    if(size == 0)
//    {
//        throw "something go wrong";
//    }
//    return size;
//}
