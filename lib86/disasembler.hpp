#include <iostream>
#include "interpreter.hpp"

namespace Lib86 {

  // here we build opcode table

  

  struct opcode_entry
  {
    uint8_t opcode;
    const char* mnemonic;
    void (Interpreter::*handler)(Instruction&);
    //need to get length of parameters and/or type here
  };


  opcode_entry opcode_entry[256];
  
  void build(uint8_t op, const char * mnemonic , void (Interpreter::*handler)(Instruction&))
  {
    opcode_entry[op].opcode = op;
    opcode_entry[op].mnemonic = mnemonic;
    opcode_entry[op].handler = handler;
  }

  void build_opcode_table()
  {
    build(0x00, "ADD", &Interpreter::ADD_rm8_reg8);
  }

  class Disassembler
  {
    
    
  public:
    void disassembleAtPoint(void * );
    void dumpInstruction(void *);
  };



}
