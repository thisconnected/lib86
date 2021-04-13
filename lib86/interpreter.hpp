#pragma once

#include <iostream>


namespace Lib86 {

  class Instruction;


  class Interpreter
  {
  public:
    //virtual void INT(Instruction&);
    void ADD_rm8_reg8(Instruction&);
  };





}
