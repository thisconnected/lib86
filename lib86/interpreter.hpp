#include <iostream>


namespace Lib86 {

  class Instruction;


  class Interpreter
  {
    //pure virtual all instructions
    virtual void RET(const Instruction&);
    virtual void MOV_ax_imm16(const Instruction&);
  };





}
