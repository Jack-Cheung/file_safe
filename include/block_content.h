#ifndef BLOCKCONTENT_H
#define BLOCKCONTENT_H
#include "global.h"
class BlockContent //data unencypted
{
public:
    BlockContent();
    ~BlockContent();
    void Read(int fd, unsigned int size, unsigned int& cursor, int direction = ENCRYPT);// 0 - input data is origin data, 1 - input data is encrypted data
    void Write(int fd,  unsigned int size, unsigned int& cursor, int direction = ENCRYPT);
    void Clear();
    //unsigned int Encrpt(unsigned int size);
    //unsigned int Decrpt(unsigned int size);

    static const int ENCRYPT = 0;// to do
    static const int DECRYPT = 1;

protected:

private:
//    unsigned char* m_originData;
//    unsigned char* m_encrypedData;
//    unsigned int m_plainTextlen;
//    unsigned int m_cipherTextLen;
      unsigned char* m_data;

};

#endif // BLOCKCONTENT_H
