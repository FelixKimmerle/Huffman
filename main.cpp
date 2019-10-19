#include <iostream>
#include "Compress.hpp"
#include "Decompress.hpp"
#include "InputParser.hpp"
#include <fstream>

int main(int argc, char **argv)
{
    
    InputParser parser(argc, argv);
    if(argc == 1 || parser.cmdOptionExists("-help") || parser.cmdOptionExists("-h") || parser.cmdOptionExists("--help"))
    {
        std::cout << argv[0] << " (-d|-c) inputfile [-o outputfile]" << std::endl;
        std::cout << "-d Decompress" << std::endl;
        std::cout << "-c Compress" << std::endl;
    }
    if (parser.cmdOptionExists("-d"))
    {
        std::string file = parser.getCmdOption("-d");
        std::string * str = DecompressFile(file);
        if(parser.cmdOptionExists("-o"))
        {
            std::string outfile = parser.getCmdOption("-o");
            std::ofstream out(outfile);
            out << *str;
            out.close();
        }
        else
        {
            std::cout << *str << std::endl;
        }
        delete str;
    }
    if (parser.cmdOptionExists("-c"))
    {
        std::string file = parser.getCmdOption("-c");
        Packet *packet = CompressFile(file);
        
        if (parser.cmdOptionExists("-o"))
        {
            std::string outfile = parser.getCmdOption("-o");
            packet->WriteToFile(outfile);
        }
        else
        {
            std::cout << packet->GetString() << std::endl;
        }
        delete packet;
    }

    return 0;
}