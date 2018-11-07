#ifndef FILEHEADER_H
#define FILEHEADER_H


class FileHeader
{
public:
    FileHeader();
    ~FileHeader() = default;
    void Clear();
    void Read(int fd);
    void Write(int fd);

    int m_number;// amount of blocks
    static const int BYTES = 8;//memery space this header take place
};

#endif // FILEHEADER_H
