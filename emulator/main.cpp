#include "cpu.hpp"
#include <iostream>

void test(Lib86::CPU * );

int main(int argc, char **argv)
{
  std::cout << argc << argv << std::endl;

  Lib86::CPU cpu;
  
  cpu.dump_decimal();
  cpu.dump();

  test(&cpu);
  auto ip = cpu.ip();
  printf("readAt 0x%2x = %d\nreadAt 0x%2x = %d\n", ip, cpu.readAt<uint8_t>(ip), ip+1, cpu.readAt<uint8_t>(ip+1));
  cpu.dumpmemory(0x100,0x80);
  cpu.dump();
  cpu.next();
  cpu.dump();
  cpu.next();
  cpu.dump();

  return 0;
}

void test(Lib86::CPU * cpu)
{
  auto ip = cpu->ip();
  //ADD DL, 16h
  cpu->writeAt<uint8_t>(ip,0x80);
  cpu->writeAt<uint8_t>(ip+1,0xc2);
  cpu->writeAt<uint8_t>(ip+2,0x16);
  //INT 23h (DOS exit)
  cpu->writeAt<uint8_t>(ip+3,0xCD);
  cpu->writeAt<uint8_t>(ip+4,0x23);
  //ADD DL, CH
  cpu->writeAt<uint8_t>(ip+5,0x02);
  cpu->writeAt<uint8_t>(ip+6,0xD5);
  //ADD AL, bh
  cpu->writeAt<uint8_t>(ip+7,0x02);
  cpu->writeAt<uint8_t>(ip+8,0xc7);

  cpu->set_ip(ip+5);
}






