#pragma once
#include <vector>
#include <string>

#define SET_BIT(where, bit_number) ((where) |= 1 << (bit_number))
#define RESET_BIT(where, bit_number) ((where) &= ~(1 << (bit_number)))
#define FLIP_BIT(where, bit_number) ((where) ^= 1 << (bit_number))
#define GET_BIT_VALUE(where, bit_number) (((where) & (1 << (bit_number))) >> bit_number)

class Packet
{
  public:
    Packet();
    void AddBit(bool Value);
    void AddByte(char Value);
    void Flush();
    void Unflush();
    void WriteToFile(std::string file);
    void ReadFromFile(std::string file);
    bool GetBit(unsigned int ppos)const;
    char GetByte(unsigned int ppos);
    void print();
    unsigned int GetSize();
    std::string GetString();
    void LoadFromString(std::string *str);
    void Compress()const;
    void Decompress();

  private:
    char current;
    unsigned char pos;
    std::string Data;
};
