#include "crypt.hpp"
#include "sha2.h"
#include "global.hpp"

/**generate file hash code*/
string Crypt::GenerateSHA256(const string& file_path)
{
    
    static const int BUFLEN = 16384;
    SHA256_CTX	ctx256;
    unsigned char	buf[BUFLEN] = {0};
    string hashCode;
    SHA256_Init(&ctx256);
    ifstream fs(file_path, fs.in);
    int l = 0;
    while ((l = fs.readsome((char*)buf,BUFLEN)) > 0)
    {
        SHA256_Update(&ctx256, (unsigned char*)buf, l);
    }
    SHA256_End(&ctx256, (char*)buf);
    hashCode = (const char*)buf;
    return hashCode;
}

void Crypt::Encrypt(const string& infile_path, const string& outfile_path)
{
    CleanUp();
    m_infilePath = infile_path;
    m_outfilePath = outfile_path;
    EncryptFile();
}

void Crypt::Decrypt(const string& infile_path, const string& outfile_path)
{
    CleanUp();
    m_infilePath = infile_path;
    m_outfilePath = outfile_path;
    DecryptFile();
}

void Crypt::CleanUp()
{
    m_header.Clear();
}

void Crypt::EncryptFile()
{
    unsigned int cnt = GetFileSize(m_infilePath);
    unsigned int blockNumber = ceil(cnt * 1.0 / BLOCK_SIZE);
    fstream ifs(m_infilePath, fstream::in);
    fstream ofs(m_outfilePath, fstream::out | fstream::trunc);
    m_header.m_number = blockNumber;
    m_header.Write(ofs);
    Block block(ifs, ofs, blockNumber);
    for(unsigned int i = 0; i < blockNumber; ++i)
    {
        block.Clear();
        block.Read(i, blockNumber, ORIGIN);
        block.Encrypt();
        block.Write();
    }
    ifs.close();
    ofs.close();
}

void Crypt::DecryptFile()
{
    fstream ifs(m_infilePath, fstream::in);
    fstream ofs(m_outfilePath, fstream::out | fstream::trunc);
    m_header.Read(ifs);
    int blockNumber = m_header.m_number;
    Block block(ifs, ofs, blockNumber);
    for(int i = 0; i < blockNumber; ++i)
    {
        block.Read(i, blockNumber, ENCRYPT);
        block.Decrypt();
        block.Write();
    }
    ifs.close();
    ofs.close();
}

unsigned long Crypt::GetFileSize(const string& file_path)
{
    unsigned long filesize = -1;
    ifstream ifs(file_path, ifs.in);
    if(ifs)
    {
        ifs.seekg(0, ifs.end);
        filesize = ifs.tellg();
    }
    return filesize;
}
