#pragma once
#include <iostream>

namespace Lib86 {
  

  union wordOrBytePtr {
    uint8_t * (*byte)(uint16_t);
    uint16_t * (*word)(uint16_t);
  };

  union wordOrByte {
    uint8_t * (*byte)(uint16_t);
    uint16_t * (*word)(uint16_t);
  };

  
  class Instruction
  {
  private:
    const void * m_instruction_ptr;
    wordOrBytePtr m_first;
    wordOrBytePtr m_second;
    //opcode_entry& m_opentry;
    
  public:
    Instruction(void * instptr) :
      m_instruction_ptr(instptr) {};
    
    template <typename t> void writeFirstArgument(t input);
    template <typename t> void writeSecondArgument(t input);
    template <typename t> t readFirstArgument();
    template <typename t> t readSecondArgument();
    
  };


}
