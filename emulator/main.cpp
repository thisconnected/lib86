#include "cpu.hpp"
#include <iostream>
#include <assert.h>

void test(Lib86::CPU * );

int main(int argc, char **argv)
{
  std::cout << argc << argv << std::endl;

  std::string filename;

  if(argc > 1)
    {
      printf("reading from file %s\n", argv[1]);

      filename = argv[1];
    }
  else
    assert(false && "no file specified");

  Lib86::CPU cpu;
  
  cpu.initdos(filename);
  //cpu.dump_decimal();
  //cpu.dump();

  //test(&cpu);
  auto ip = cpu.ip();
  printf("readAt 0x%2x = %d\nreadAt 0x%2x = %d\n", ip, cpu.readAt<uint8_t>(ip), ip+1, cpu.readAt<uint8_t>(ip+1));
  //cpu.dumpmemory(0x100,0x80);
  //cpu.dump();

  //for(int i=0;i<100;i++)0
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
  cpu->writeAt<uint8_t>(++ip,0xc2);
  cpu->writeAt<uint8_t>(++ip,0x16);
  //ADD DL, CH
  cpu->writeAt<uint8_t>(++ip,0x02);
  cpu->writeAt<uint8_t>(++ip,0xD5);

  //ADD DL, CH
  cpu->writeAt<uint8_t>(++ip,0x02);
  cpu->writeAt<uint8_t>(++ip,0xD5);
  //ADD AL, BH
  cpu->writeAt<uint8_t>(++ip,0x02);
  cpu->writeAt<uint8_t>(++ip,0xc7);

  cpu->set_ip(0x100);


  //POP AX
  cpu->writeAt<uint8_t>(++ip,0x8f);
  cpu->writeAt<uint8_t>(++ip,0xc0);
  //ADD AH, CH
  cpu->writeAt<uint8_t>(++ip,0x02);
  cpu->writeAt<uint8_t>(++ip,0xe5);
  //MOV DL, 69h
  cpu->writeAt<uint8_t>(++ip,0xc6);
  cpu->writeAt<uint8_t>(++ip,0xD5);
  cpu->writeAt<uint8_t>(++ip,0x69);
  //MOV AH, 0h
  cpu->writeAt<uint8_t>(++ip,0xc6);
  cpu->writeAt<uint8_t>(++ip,0xE4);
  cpu->writeAt<uint8_t>(++ip,0x0);
  //ADD AH, 0h
  cpu->writeAt<uint8_t>(++ip,0x80);
  cpu->writeAt<uint8_t>(++ip,0xE4);
  cpu->writeAt<uint8_t>(++ip,0x0);
  //JE 3d
  cpu->writeAt<uint8_t>(++ip,0x74);
  cpu->writeAt<uint8_t>(++ip,0x3);
  //ADD AH, 0h
  cpu->writeAt<uint8_t>(++ip,0x80);
  cpu->writeAt<uint8_t>(++ip,0xE4);
  cpu->writeAt<uint8_t>(++ip,0x0);
  
  //int 21h
  cpu->writeAt<uint8_t>(++ip, 0xCD);
  cpu->writeAt<uint8_t>(++ip, 0x21);

}






