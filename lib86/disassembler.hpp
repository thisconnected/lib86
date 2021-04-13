#pragma once

#include <iostream>
#include "interpreter.hpp"


namespace Lib86 {

  struct opcode_entry
  {
    uint8_t opcode;
    const char* mnemonic;
    void (Interpreter::*handler)(Instruction&);
    //need to get length of parameters and/or type here
  };
  
  class Disassembler
  {
     opcode_entry opcode_table[256];
  
  
    void build(uint8_t op, const char * mnemonic , void (Interpreter::*handler)(Instruction&))
    {
      opcode_table[op].opcode = op;
      opcode_table[op].mnemonic = mnemonic;
      opcode_table[op].handler = handler;
    }

    void build_opcode_table()
    {
      build(0x00, "ADD", &Interpreter::ADD_rm8_reg8);
    }
    
  public:
    Disassembler() { build_opcode_table(); }
    void disassembleAtPoint(void *);
    void dumpInstruction(void *);
  };

  
  // here we build opcode table

  

  






}
