#pragma once
#include <iostream>

#include "disassembler.hpp"
#include "interpreter.hpp"


namespace Lib86 {

  class Instruction;

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
    struct {
    divisibleRegister ax;
    divisibleRegister bx;
    divisibleRegister cx;
    divisibleRegister dx;
    } m_gpr;
    //
    struct {
    staticRegister bp;
    staticRegister di;
    staticRegister si;
    staticRegister sp;
    } m_spr;
    //segment registers
    struct {
    staticRegister cs;
    staticRegister es;
    staticRegister ss;
    staticRegister ds;
    } m_segr;
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
    void dump_decimal();
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
   
    uint16_t ip() {return m_ip;}
    void set_ip(uint16_t input) {m_ip = input;}

    //GETTERS
    //8bit GPR
    uint8_t * al() {return &m_gpr.ax.low_u8;}
    uint8_t * ah() {return &m_gpr.ax.high_u8;}
    uint8_t * bl() {return &m_gpr.bx.low_u8;}
    uint8_t * bh() {return &m_gpr.bx.high_u8;}
    uint8_t * cl() {return &m_gpr.cx.low_u8;}
    uint8_t * ch() {return &m_gpr.cx.high_u8;}
    uint8_t * dl() {return &m_gpr.dx.low_u8;}
    uint8_t * dh() {return &m_gpr.dx.high_u8;}
    //16bit GPR
    uint16_t * ax() { return &m_gpr.ax.low_u16;}
    uint16_t * bx() { return &m_gpr.bx.low_u16;}
    uint16_t * cx() { return &m_gpr.cx.low_u16;}
    uint16_t * dx() { return &m_gpr.dx.low_u16;}
    //16bit special registers
    uint16_t * bp() { return &m_spr.bp.low_u16;}
    uint16_t * di() { return &m_spr.di.low_u16;}
    uint16_t * si() { return &m_spr.si.low_u16;}
    uint16_t * sp() { return &m_spr.sp.low_u16;}


    //SETTERS
    //8bit GPR
    void set_al(uint8_t input) {m_gpr.ax.low_u8 = input;} //this set_al is awkward -> nested classes dont have access to members so we cant set.al()
    void set_ah(uint8_t input) {m_gpr.ax.high_u8 = input;}
    void set_bl(uint8_t input) {m_gpr.ax.low_u8 = input;}
    void set_bh(uint8_t input) {m_gpr.ax.high_u8 = input;}
    void set_cl(uint8_t input) {m_gpr.ax.low_u8 = input;}
    void set_ch(uint8_t input) {m_gpr.ax.high_u8 = input;}
    void set_dl(uint8_t input) {m_gpr.ax.low_u8 = input;}
    void set_dh(uint8_t input) {m_gpr.ax.high_u8 = input;}
    //16bit GPR
    void set_ax(uint16_t input) {m_gpr.ax.low_u16 = input;}
    void set_bx(uint16_t input) {m_gpr.bx.low_u16 = input;}
    void set_cx(uint16_t input) {m_gpr.cx.low_u16 = input;}
    void set_dx(uint16_t input) {m_gpr.dx.low_u16 = input;}

  };
  //TEMPLATE

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
