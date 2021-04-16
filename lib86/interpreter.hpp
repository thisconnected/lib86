#pragma once

#include <iostream>
#include "instruction.hpp"


namespace Lib86 {



  class Interpreter
  {
  public:
    //virtual void INT(Instruction&);
    void ADD_rm8_reg8(Instruction&);
  };





}
