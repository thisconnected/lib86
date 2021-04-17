#pragma once
#include <iostream>

#include "disassembler.hpp"
#include "interpreter.hpp"


namespace Lib86 {

  union divisibleRegister //useful later for 32bit
  {
    struct {
      uint16_t low_u16;
    };
    struct {
      uint8_t low_u8;
      uint8_t high_u8;
    };
  };

  union staticRegister
  {
    uint16_t low_u16;
  };
  
  class CPU {
  private:
    Interpreter interpreter;
    Disassembler disassembler;
  
    //general purpose registers
    divisibleRegister m_ax;
    divisibleRegister m_bx;
    divisibleRegister m_cx;
    divisibleRegister m_dx;
    //
    staticRegister m_bp;
    staticRegister m_di;
    staticRegister m_si;
    staticRegister m_sp;
    //bus interface unit
    staticRegister m_cs;
    staticRegister m_es;
    staticRegister m_ss;
    staticRegister m_ds;
    //instruction point
    int16_t m_ip = 0;

    struct Flags {
      enum Flag
	{
	  CF = 0x0001,
	  PF = 0x0004,
	  AF = 0x0010,
	  ZF = 0x0040,
	  SF = 0x0080,
	  TF = 0x0100,
	  IF = 0x0200,
	  DF = 0x0400,
	  OF = 0x0800,
	};
    };
  
    void * memory;
  
  public:
    CPU();
    void dump();
    void dump(Instruction&);
    void dumpmemory(uint16_t offset, int bytes);
    void dumpbacktrace();
    void next();

    bool initdos(std::string filename);

    template <typename T> T* pointerAtOffset(uint16_t offset);


    //DEBUG
    void example();
    void fillMemAt(uint16_t offset, uint8_t fill , int bytes);
    template <typename T> void writeAt(uint16_t offset, T input);
    template <typename T> T readAt(uint16_t offset);
    //END_DEBUG
   
    uint32_t ip() {return m_ip;}

    //GETTERS
    //8bit GPR
    uint8_t al() {return m_ax.low_u8;}
    uint8_t ah() {return m_ax.high_u8;}
    uint8_t bl() {return m_bx.low_u8;}
    uint8_t bh() {return m_bx.high_u8;}
    uint8_t cl() {return m_cx.low_u8;}
    uint8_t ch() {return m_cx.high_u8;}
    uint8_t dl() {return m_dx.low_u8;}
    uint8_t dh() {return m_dx.high_u8;}
    //16bit GPR
    uint16_t ax() { return m_ax.low_u16;}
    uint16_t bx() { return m_bx.low_u16;}
    uint16_t cx() { return m_cx.low_u16;}
    uint16_t dx() { return m_dx.low_u16;}

  };


  template <typename T> void CPU::writeAt(uint16_t offset, T input)
  {
    auto ptr = pointerAtOffset<T>(offset);

    *ptr = input;
    //FIXME: bounds checking
  }
  template <typename T> T CPU::readAt(uint16_t offset)
  {
    return *pointerAtOffset<T>(offset);
    //FIXME: bounds checking
  } 

  template <typename T> T* CPU::pointerAtOffset(uint16_t offset)
  {
    uint8_t * ptr = (uint8_t*) memory;
    ptr+=offset;
    printf("ptrAtOffset(): %p offset: 0x%x computed: %p\n", memory, offset, ptr);
    return (T*) ptr;
  }
}
