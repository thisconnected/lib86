#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "cpu.hpp"

namespace Lib86
{

  CPU::CPU()
  {
    printf("spawning cpu\n");
    example();
  }
  
  void CPU::dump()
  {
    printf("ip:\t%x\n",m_ip);
    printf("   \th  l\n");
    printf("ax:\t%x %x\nbx:\t%x %x\ncx:\t%x %x\ndx:\t%x %x\n",ah(),al(),bh(),bl(),ch(),cl(),dh(),dl());
  }

  void * CPU::pointerAtAdress(uint16_t offset)
  {
    auto * ptr = (uint8_t*)memory;
    return (void *)ptr[offset];
  }

  void CPU::example()
  {
    m_ax.low_u16 = 50769;
    m_ip = 15000;
    m_bx.low_u16 = 144;
    m_cx.low_u16 = 69;
    initdos("../../tests/test.com");
  }
  
  bool CPU::initdos(std::string filename)
  {
    memory = malloc(64*1000);
    m_ip = 0x0100; //entry point
    if(memory==nullptr)
      return false;
    //here mmap the executable at 0100h for dos
    /*
    auto * file = fopen(filename.c_str(), "rb");
    
    auto pointer = mmap(NULL, 64, PROT_READ | PROT_WRITE, MAP_PRIVATE, file, 0);
    */
    uint8_t * temp = (uint8_t*) memory;
    temp+=m_ip;
    for(int i=0; i<10;i++)
      {
	*temp++ = 0x00;
      }
    
    return true;
  }
  
}
