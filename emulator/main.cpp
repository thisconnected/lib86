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
  //cpu.dumpmemory(0x100,0x80);
  while(true)
    {
      cpu.dump();
      cpu.next();
    }

  return 0;
}

void test(Lib86::CPU * cpu)
{
  auto ip = cpu->ip();
  //ADD DL, 16h
  cpu->writeAt<uint8_t>(ip,0x80);
  cpu->writeAt<uint8_t>(ip+1,0xc2);
  cpu->writeAt<uint8_t>(ip+2,0x16);
  //ADD DL, CH
  cpu->writeAt<uint8_t>(ip+5,0x02);
  cpu->writeAt<uint8_t>(ip+6,0xD5);
  //ADD AL, BH
  cpu->writeAt<uint8_t>(ip+7,0x02);
  cpu->writeAt<uint8_t>(ip+8,0xc7);

  cpu->set_ip(ip+7);


  //POP AX
  cpu->writeAt<uint8_t>(ip+9,0x8f);
  cpu->writeAt<uint8_t>(ip+10,0xc0);
  //ADD AH, CH
  cpu->writeAt<uint8_t>(ip+11,0x02);
  cpu->writeAt<uint8_t>(ip+12,0xe5);
  //int 21h
  cpu->writeAt<uint8_t>(ip+13, 0xCD);
  cpu->writeAt<uint8_t>(ip+14, 0x21);

}






