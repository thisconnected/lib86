#include "cpu.hpp"
#include <iostream>

int main(int argc, char **argv)
{
  Lib86::CPU cpu;
  auto ip = cpu.ip();
  cpu.dump();
  cpu.writeAt<uint8_t>(ip,0x04);
  cpu.writeAt<uint8_t>(ip+1,0x16);
  printf("readAt 0x%x = %d; readAt 0x%x = %d", ip, cpu.readAt<uint8_t>(ip), ip+1, cpu.readAt<uint8_t>(ip+1));
  cpu.dumpmemory(ip,0xF0);

  return 0;
}






