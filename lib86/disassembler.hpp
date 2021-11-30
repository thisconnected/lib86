#pragma once

#include <iostream>
#include "interpreter.hpp"
#include "types.hpp"


namespace Lib86 {

  typedef void (Interpreter::*handler)(Instruction&); //wtf


  struct opcode_entry
  {
    uint8_t opcode;
    const char* mnemonic;
    void (Interpreter::*handler)(Instruction&);
    enum immidiate imm = no;
  };
  
  class Disassembler
  {
     opcode_entry * opcode_table;
  
  
    void build(uint8_t op, const char * mnemonic , void (Interpreter::*handler)(Instruction&));
    void build(uint8_t op, const char * mnemonic , void (Interpreter::*handler)(Instruction&), enum immidiate imm);
    void build_opcode_table();
    
  public:
    Disassembler();
    ~Disassembler();
    uint16_t run(uint16_t,void *, Interpreter&);
    void disassembleAtPoint(void *);
    void dumpInstruction(void *);
  };

  
  // here we build opcode table

  

  






}
