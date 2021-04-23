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
  };





}
