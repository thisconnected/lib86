#include "cpu.hpp"
#include <iostream>

int main(int argc, char **argv)
{
  Lib86::CPU cpu;
  auto ip = cpu.ip();
  cpu.dump();
  cpu.fillMemAt(ip,0x04, 1);
  cpu.fillMemAt(ip+1,0x16, 1);
  cpu.dumpmemory(ip,0xF0);

  return 0;
}






