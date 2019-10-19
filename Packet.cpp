#include "Packet.hpp"
#include <bitset>
#include <iostream>
#include <fstream>

Packet::Packet() : Data("")
{
    current = 0;
    pos = 0;
}
void Packet::AddBit(bool Value)
{
    if (Value)
    {
        SET_BIT(current, 7 - pos);
    }
    else
    {
        RESET_BIT(current, 7 - pos);
    }
    pos++;
    if (pos >= 8)
    {
        Data.push_back(current);
        current = 0;
        pos = 0;
    }
}
void Packet::AddByte(char Value)
{
    for (unsigned short i = 0; i < 8; i++)
    {
        AddBit(GET_BIT_VALUE(Value, i));
    }
}
void Packet::Flush()
{
    Data.push_back(current);
}
void Packet::Unflush()
{
    if (Data.size() > 0 && pos != 0)
    {
        current = Data[Data.size() - 1];
        Data.pop_back();
    }
}
void Packet::WriteToFile(std::string file)
{
    std::ofstream outstream(file, std::ios::binary);
    if (outstream)
    {
        outstream.write(reinterpret_cast<const char *>(&pos), sizeof(pos));
        outstream.write(&Data[0], Data.size());
        outstream.close();
    }
}
void Packet::ReadFromFile(std::string file)
{
    std::ifstream instream(file, std::ifstream::ate | std::ios::binary);
    if (instream)
    {
        unsigned int size = instream.tellg();
        instream.seekg(0, std::ios::beg);
        instream.read(reinterpret_cast<char *>(&pos), sizeof(pos));
        Data.resize(size - 2);
        instream.read(&Data[0], size - 2);
        instream.read(reinterpret_cast<char *>(&current), sizeof(current));
        instream.close();
    }
    else
    {
        pos = 8;
    }
    
    
    
}
bool Packet::GetBit(unsigned int ppos) const
{
    unsigned int index = ppos / 8;
    unsigned short bindex = ppos % 8;
    return GET_BIT_VALUE(Data[index], (7 - bindex));
}
char Packet::GetByte(unsigned int ppos)
{
    char output = 0;
    for (unsigned short i = 0; i < 8; i++)
    {
        if (GetBit(ppos + i))
        {
            SET_BIT(output, (i));
        }
        else
        {
            RESET_BIT(output, (i));
        }
    }
    return output;
}
void Packet::print()
{
    for (auto x = Data.begin(); x != Data.end(); x++)
    {
        std::bitset<8> bset(*x);
        std::cout << bset << " ";
    }
    std::cout << std::endl;
}
unsigned int Packet::GetSize()
{
    return Data.size() * 8 - (8 - pos);
}

std::string Packet::GetString()
{
    return pos + Data.c_str();
}
void Packet::LoadFromString(std::string *str)
{
    pos = (*str)[0];
    for (auto x = str->begin() + 1; x != str->end() - 1; x++)
    {
        Data.push_back(*x);
    }
    current = *(str->end() - 1);
}

void Packet::Compress() const
{
    char max = 0;
    Packet npack;
    bool current = GetBit(0);
    char num = 1;
    std::vector<char> l;
    for (unsigned int i = 1; i < Data.size() * 8; i++)
    {
        bool bit = GetBit(i);
        if (current == bit)
        {
            num++;
        }
        else
        {
            if (max < num)
            {
                max = num;
            }
            l.push_back(num);
            current = bit;
            num = 1;
        }
    }
    std::cout << (int)max << std::endl;

    for (auto x = l.begin(); x != l.end(); x++)
    {
    }

    npack.Flush();
}
void Packet::Decompress()
{
}
