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
    uint16_t m_bp = 0;
    uint16_t m_di = 0;
    uint16_t m_si = 0;
    uint16_t m_sp = 0;
    //bus interface unit
    uint16_t m_cs = 0;
    uint16_t m_es = 0;
    uint16_t m_ss = 0;
    uint16_t m_ds = 0;
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
    void dumpmemory();
    void dumpbacktrace();
    void next() {disassembler.disassembleAtPoint(pointerAtAdress(ip()));};

    void * pointerAtAdress(uint16_t);
  
    void example();
    bool initdos(std::string filename);
  

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
    u_int16_t ax() { return m_ax.low_u16;}
    u_int16_t bx() { return m_bx.low_u16;}
    u_int16_t cx() { return m_cx.low_u16;}
    u_int16_t dx() { return m_dx.low_u16;}

  };


  
}
