#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "cpu.hpp"
#include <assert.h>
#define NDEBUG

namespace Lib86
{

  CPU::CPU() : m_gpr {},
	       m_spr {},
	       m_segr {}
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


  void CPU::example()
  {
    m_ax.low_u16 = 50769;
    m_ip = 15000;
    m_bx.low_u16 = 144;
    m_cx.low_u16 = 69;
    initdos("../tests/test.com");
  }
  
  bool CPU::initdos(std::string filename)
  {
    std::cout << "initdos\n";
    memory = malloc(64*1000);
    m_ip = 0x0100; //entry point
    if(memory==nullptr)
      return false;
    //here mmap the executable at 0100h for dos

    auto fd = open(filename.c_str(), O_RDONLY);
    if(fd == -1)
      {
	perror("open");
	return false;
      }
    
    auto pointer = mmap(pointerAtOffset<void>(ip()), 64*100, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

    if(pointer==MAP_FAILED)
      {
	perror("mmap");
	return false;
      }
    
    
    uint8_t * temp = (uint8_t*) memory;
    temp+=m_ip;
    for(int i=0; i<10;i++)
      {
	*temp++ = 0x00;
      }
    
    return true;
  }

  void CPU::dumpmemory(u_int16_t offset, int bytes)
  {
    
    auto * ptr = pointerAtOffset<uint8_t>(offset);

    printf("dumpmemory %d bytes at 0x%x\n", bytes, offset);
    for(int i = 0; i<bytes; i+=2)
      {
	if(i%8==0)
	  std::cout << std::endl;
	
        printf("%04x ", (uint8_t)*ptr);
	ptr++;
      }
    //FIXME: bounds checking
  }

  void CPU::fillMemAt(uint16_t offset, uint8_t fill , int bytes)
  {
    auto * ptr = pointerAtOffset<uint8_t>(offset);
    
    for(int i=0; i<bytes;i++)
      {
	*ptr = fill;
	ptr++;
      }
    //FIXME: bounds checking
  }

}
