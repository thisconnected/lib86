#include <iostream>

#include "interpreter.cpp"

namespace Lib86 {

  
class CPU {
private:
  
  //general purpose registers
  uint16_t m_ax = 0;
  uint16_t m_bx = 0;
  uint16_t m_cx = 0;
  uint16_t m_dx = 0;
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

  void * memory;
  
public:
  void dump();
  void dump(Instruction&);
  CPU();

  uint32_t ip() {return m_ip;};
  uint8_t al() {return (uint8_t)(m_ax & 0x00ff) >> 8;}
  uint8_t ah() {return (uint8_t)(m_ax & 0xff00);}

  
  
};

}
