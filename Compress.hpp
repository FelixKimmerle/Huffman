#pragma once
#include <string>
#include "Packet.hpp"
Packet * CompressFile(const std::string &file);
Packet * Compress(const std::string &str);