#pragma once

#include <iostream>
#include "instruction.hpp"


namespace Lib86 {



  class Interpreter
  {
  public:
    //virtual void INT(Instruction&);
    void ADD_byte(Instruction&);
    void ADD_word(Instruction&);
    void INT_byte(Instruction&);
    void PUSH_word(Instruction&);
    void PUSH_reg(Instruction&);
    void POP_word(Instruction&);
    void POP_reg(Instruction&);
    void MOV_word(Instruction&);
    void MOV_byte(Instruction&);
    void XOR_byte(Instruction&);
    void CMP_byte(Instruction&);
  };





}
