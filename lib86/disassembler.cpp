#include "disassembler.hpp"
#include <iostream>
#include <stdlib.h>
#include <cassert>
#include "instruction.hpp"
#include <memory>

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
    std::unique_ptr<Instruction> insn(new Instruction(instptr));
    auto opcode = *(uint8_t*)instptr;
    printf("Disassembler::run()\n"
	   "\topcode  :\t%#x\n"
	   "\tmnemonic:\t%s\n"
	   "\tmode    :\t%s\n"
	   "\thandler :\t%p\n",
	   opcode, opcode_table[opcode].mnemonic, opcode & 1 ? "word" : "byte", opcode_table[opcode].handler);

    if(!opcode_table[opcode].mnemonic)
      {
	fprintf(stderr,"at ip %#x unrecognized instruction with opcode %#x\n", ip, opcode);
	fflush(stdout);
	assert("Unrecogonized opcode" && false);
      }
    auto funptr = opcode_table[opcode].handler; //this needs to actually ignore direction bit (we do that internally in instruction

    if(opcode_table[opcode].imm != no)
      {
	printf("\t setting up immidiate value\n");
	insn->set_imm(opcode_table[opcode].imm);
      }

    (interpreter.*funptr)(*insn);
    //assert(false);

    if(opcode & 0b10000000)
      printf("calling %s with %d %d\n", opcode_table[opcode].mnemonic, insn->readFirstArgument<uint8_t>(),insn->readSecondArgument<uint8_t>());
    return insn->size;
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
      //      build(0x04, "ADD", &Interpreter::ADD_byte);
      // build(0x50, "PUSH", &Interpreter::PUSH_word); //PUSH REG only
      // build(0x5a, "POP", &Interpreter::POP_word); //POP REG only
      build(0xC6, "MOV imm8", &Interpreter::MOV_byte,imm8);
      build(0xC7, "MOV imm16", &Interpreter::MOV_word,imm16);
      build(0xC6, "MOV", &Interpreter::MOV_byte);
      build(0xC7, "MOV", &Interpreter::MOV_word);
      build(0x8f, "POP", &Interpreter::POP_word);
      build(0xff, "PUSH", &Interpreter::PUSH_word);
      build(0xCD, "INT", &Interpreter::INT_byte);
      build(0x74, "JE", &Interpreter::JE);
      build(0x75, "JNE", &Interpreter::JNE);
      build(0x3a, "CMP", &Interpreter::CMP_byte);
      build(0x80, "ADD/CMP imm8", &Interpreter::ADDCMP_imm,imm8);
    }
  void Disassembler::build(uint8_t op, const char * mnemonic , void (Interpreter::*handler)(Instruction&))
    {
      opcode_table[op].opcode = op;
      opcode_table[op].mnemonic = mnemonic;
      opcode_table[op].handler = handler;
    }
  void Disassembler::build(uint8_t op, const char * mnemonic , void (Interpreter::*handler)(Instruction&),enum immidiate imm)
    {
      opcode_table[op].opcode = op;
      opcode_table[op].mnemonic = mnemonic;
      opcode_table[op].handler = handler;
      opcode_table[op].imm = imm;
    }

}
