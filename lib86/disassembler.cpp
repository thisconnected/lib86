#include "disassembler.hpp"
#include <iostream>
#include <stdlib.h>
#include <cassert>
#include "instruction.hpp"

namespace Lib86 {

  Disassembler::Disassembler()
  {
    printf("construction Disassembler");
    opcode_table = (opcode_entry*) malloc(256*sizeof(opcode_table));
    if(!opcode_table)
      assert(false);
    build_opcode_table();
  }

  Disassembler::~Disassembler()
  {
    free(opcode_table);
  }

  uint16_t Disassembler::run(uint16_t ip, void * instptr, Interpreter& interpreter)
  {
    auto insn = new Instruction(instptr);
    auto opcode = *(uint8_t*)instptr;
    printf("Disassembler::run()\n"
	   "\topcode  :\t%d\n"
	   "\tmnemonic:\t%s\n"
	   "\tmode    :\t%s\n"
	   "\thandler :\t%p\n",
	   opcode, opcode_table[opcode].mnemonic, opcode & 1 ? "word" : "byte", opcode_table[opcode].handler);

    if(!opcode_table[opcode].mnemonic)
      {
	fprintf(stderr,"at ip %#x unrecognized instruction with opcode %#x\n", ip, opcode);
	fflush(stdout);
	assert("Unregonized opcode" && false);
      }
    auto funptr = opcode_table[opcode].handler;
    (interpreter.*funptr)(*insn);
    //assert(false);

    if(opcode & 0b10000000)
      printf("calling %s with %d %d", opcode_table[opcode].mnemonic, insn->readFirstArgument<uint8_t>(),insn->readSecondArgument<uint8_t>());
    return ip+opcode_table[opcode].size;
  }

  void Disassembler::disassembleAtPoint(void * memory)
  {
    uint8_t opcode = *(uint8_t*)memory;
    printf("op:%d mne:%s ", opcode_table[opcode].opcode, opcode_table[opcode].mnemonic);
  }


  void Disassembler::build_opcode_table()
    {
      build(0x00, "ADD", &Interpreter::ADD_byte);
      build(0x02, "ADD", &Interpreter::ADD_byte);
      build(0x04, "ADD", &Interpreter::ADD_byte);
      build(0x80, "ADD", &Interpreter::ADD_byte);
      build(0xCD, "INT", &Interpreter::INT_byte);
    }
  void Disassembler::build(uint8_t op, const char * mnemonic , void (Interpreter::*handler)(Instruction&))
    {
      opcode_table[op].opcode = op;
      opcode_table[op].mnemonic = mnemonic;
      opcode_table[op].handler = handler;
    }

}
