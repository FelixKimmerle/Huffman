#pragma once
#include <string>
#include "Packet.hpp"
std::string * DecompressFile(const std::string &file);
std::string * Decompress(Packet * str);