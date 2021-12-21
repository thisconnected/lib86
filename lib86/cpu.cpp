#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "cpu.hpp"
#include <assert.h>
#include "types.hpp"
#include "flags.hpp"

#include <unistd.h>

namespace Lib86
{
  CPU * Instruction::fakeCPU = nullptr;

  CPU::CPU() : m_gpr {},
	       m_spr {},
	       m_segr {}
  {
    printf("spawning cpu\n");
    Instruction::fakeCPU = this;
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
	   *ah(),*al(),*bp(),*bh(),*bl(),*di(),*ch(),*cl(),*si(),*dh(),*dl(),*sp());
    dumpflags();
  }

  void CPU::dump_decimal()
  {
    printf("ip:\t%d\n",m_ip);
    printf("   \th   l\n");
    printf("ax:\t%03d %d\t" "bp:\t%d\n"
	   "bx:\t%03d %d\t" "di:\t%d\n"
	   "cx:\t%03d %d\t" "si:\t%d\n"
	   "dx:\t%03d %d\t" "sp:\t%d\n",
	   *ah(),*al(),*bp(),*bh(),*bl(),*di(),*ch(),*cl(),*si(),*dh(),*dl(),*sp());
    dumpflags();
  }

  void CPU::dumpflags()
  {
    printf("flags: %d%d%d%d%d\n"
	   "flags: CPZSO\n", flags_reg & FLAG_CARRY, flags_reg & FLAG_PARITY ? true : false,flags_reg & FLAG_ZERO ? true : false ,flags_reg & FLAG_SIGN ? true : false,flags_reg & FLAG_OVERFLOW ? true : false );
  }


  void CPU::example()
  {
    m_spr.sp.low_u16 = 0xff00;
    set_ax(0xffff);
    set_bx(0xFFFF);
    set_cx(0xffff);
    set_dx(0xffff);
  }
  
  bool CPU::initdos(std::string filename)
  {
    //TODO: actually map .com files AT 100h not 100h of 0's
    std::cout << "initdos\n";
    char tempstr[1024];
    getcwd(tempstr, sizeof(tempstr));
    printf("CWD: %s\n",tempstr);
    std::cout << "loading file: " << filename << "\n";

    memory = malloc(MAXMEM);
    m_ip = 0x0100; //entry point

    printf("memory at %p\n", memory);
    if(memory==nullptr)
      return false;
    //here mmap the executable at 0100h for dos
    fflush(stdout);
    auto fd = open(filename.c_str(), O_RDONLY);
    if(fd == -1)
      {
	perror("open");
	assert(false && "open");
      }
    
    auto* pointer = mmap(pointerAtOffset<void>(ip()), 64*100, PROT_READ | PROT_WRITE | MAP_FIXED, MAP_PRIVATE, fd, 0);

    printf("map at %p\n",pointer);

    if(pointer==MAP_FAILED)
      {
	perror("mmap");
	return false;
      }

    //TODO this is bad;
    memory = pointer;
    
    dumpmemory(0,1000);

    return true;
  }

  void CPU::dumpmemory(u_int16_t offset, int bytes)
  {
    if(offset+bytes>MAXMEM)
      assert("out of bands dump");
    
    
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

  }

  void CPU::fillMemAt(uint16_t offset, uint8_t fill , int bytes)
  {
    if(offset+bytes>MAXMEM)
      assert("out of bands dump");
    
    auto * ptr = pointerAtOffset<uint8_t>(offset);
    
    for(int i=0; i<bytes;i++)
      {
	*ptr = fill;
	ptr++;
      }
  }

  void CPU::next()
  {
    printf("CPU::next()\n");
    auto value = disassembler.run(ip(),pointerAtOffset<void>(ip()),interpreter);
    value += ip();
    printf("CPU::next() setting ip to %#x\n", value);
    set_ip(value);
  }

}
