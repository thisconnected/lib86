#include "cpu.hpp"
#include <iostream>

int main(int argc, char **argv)
{
  Lib86::CPU cpu;
  auto ip = cpu.ip();
  cpu.dump();
  cpu.fillMemAt(ip+10,0x01, 0x10);
  cpu.dumpmemory(ip,0xF0);

  return 0;
}






