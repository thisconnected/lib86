#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "cpu.hpp"
#include <assert.h>

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
    printf("ip:\t%#x\n",m_ip);
    printf("   \th  l\t\th l\n");
    printf("ax:\t%02x %02x\t" "bp:\t%04x\n"
	   "bx:\t%02x %02x\t" "di:\t%04x\n"
	   "cx:\t%02x %02x\t" "si:\t%04x\n"
	   "dx:\t%02x %02x\t" "sp:\t%04x\n",
	   ah(),al(),bp(),bh(),bl(),di(),ch(),cl(),si(),dh(),dl(),sp());
  }

  void CPU::dump_decimal()
  {
    printf("ip:\t%d\n",m_ip);
    printf("   \th   l\n");
    printf("ax:\t%03d %d\t" "bp:\t%d\n"
	   "bx:\t%03d %d\t" "di:\t%d\n"
	   "cx:\t%03d %d\t" "si:\t%d\n"
	   "dx:\t%03d %d\t" "sp:\t%d\n",
	   ah(),al(),bp(),bh(),bl(),di(),ch(),cl(),si(),dh(),dl(),sp());
  }


  void CPU::example()
  {
    set_ah(50);
    set_bx(670);
    set_cx(500);
    set_dx(0xFFFF);
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
    for(int i = 0; i<bytes; i+=1)
      {
	if(i%8==0)
	  std::cout << std::endl;
	
        printf("%02x ", (uint8_t)*ptr);
	ptr++;
      }
    std::cout << std::endl;
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

  void CPU::next()
  {
    auto value = disassembler.run(ip(),pointerAtOffset<void>(ip()),interpreter);
    set_ip(value);
  }

}
