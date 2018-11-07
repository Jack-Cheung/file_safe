#ifndef BLOCKTAIL_H
#define BLOCKTAIL_H


class BlockTail
{
public:
    BlockTail() = default;
    ~BlockTail() = default;
    void Read(unsigned int& cursor);
    void Write(int fd, unsigned int& cursor);

    static const int BYTES = 4;
};

#endif // BLOCKTAIL_H
