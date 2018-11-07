#ifndef CRYPT_H
#define CRYPT_H

#include "global.h"
#include "file_header.h"
#include "block.h"

class Crypt
{
public:
    Crypt() = default;
    ~Crypt() = default;
    static string GenerateSHA256(const string& file_path);
    void Encrypt(const string& infile_path, const string& outfile_path);
    void Decrypt(const string& infile_path, const string& outfile_path);

protected:

private:
    void GenerateFile();
    void CleanUp();
    void EncryptFile();
    void DecryptFile();
    unsigned long GetFileSize(const string& file_path);

    FileHeader m_header;
    string m_infilePath;
    string m_outfilePath;
};

#endif // CRYPT_H
