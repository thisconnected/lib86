#include "interpreter.hpp"
#include "instruction.hpp"
#include <stdio.h>
#include "cpu.hpp"
#include "flags.hpp"
#include <limits>
#include "interrupt.hpp"
#include <assert.h>

namespace Lib86 {

  template <typename t> inline void flags_add(uint16_t* flags, t first, t second)
  {
    printf("\tflags_add(%d, %d)\n",first,second);
    //TODO
    *flags = 0x0; //should clean only arithmetic flags

    if((first+second)==0)
	*flags = *flags | FLAG_ZERO;
    t diff = std::numeric_limits<t>::max() - first;
    if(diff < second)
      *flags |= FLAG_OVERFLOW;
    if((first+second) < 0)
      *flags |= FLAG_SIGN;
    fflush(stdout);

    printf("flags: %#x\n", *flags);
  }

void Interpreter::ADD_byte(Instruction& insn)
{
  printf("Interpreter::ADD_byte(%p)\n", &insn);
  int8_t src1 = insn.readFirstArgument<int8_t>();
  int8_t src2 = insn.readSecondArgument<int8_t>();

  int8_t dest = src1 + src2;

  flags_add<int8_t>(insn.fakeCPU->flags(), src1 ,src2);
  printf("\tADD %d + %d = %d\n", src1,src2,dest);

  insn.writeFirstArgument<uint8_t>(dest);
}

  
void Interpreter::ADD_word(Instruction& insn)
{
  printf("Interpreter::ADD_word(%p)\n", &insn);
  //FIXME: this is actually just for debugging
  int16_t src1 = insn.readFirstArgument<int16_t>();
  int16_t src2 = insn.readSecondArgument<int16_t>();

  int16_t dest = src1 + src2;

  flags_add<int16_t>(insn.fakeCPU->flags(), src1, src2);

  printf("ADD %d + %d = %d ", src1,src2,dest);
  insn.writeFirstArgument<uint16_t>(dest);
}


  void Interpreter::INT_byte(Instruction& insn)
  {
    printf("Interpreter::INT_byte(%p)\n", &insn);
    auto interrupt_number = insn.getByte(1);
    printf("Called interrupt number %#4x\n", interrupt_number);
    handle_interrupt(interrupt_number, insn.fakeCPU);
  }

  void Interpreter::PUSH_word(Instruction& insn)
  {
    printf("Interpreter::PUSH_WORD(%p)\n", &insn);
    CPU * cpu = insn.fakeCPU;
    uint16_t * sp = cpu->sp();
    uint16_t value = insn.readFirstArgument<uint16_t>();

    printf("PUSH %x\n", value);
    printf("\tPRE SP = %x\n", *sp);

    *sp = *sp - 2;
    cpu->writeAt<uint16_t>(*sp,value);


    printf("\tPOST SP = %x\n", *sp);

  }

  void Interpreter::POP_word(Instruction& insn)
  {
    printf("Interpreter::POP_WORD(%p)\n", &insn);

    CPU * cpu = insn.fakeCPU;
    uint16_t * sp = cpu->sp();
    uint16_t popped = cpu->readAt<uint16_t>(*sp);

    printf("\tPRE SP = %x\n", *sp);

    *sp = *sp + 2;

    printf("\tPRE SP = %x\n", *sp);


    insn.writeFirstArgument<uint16_t>(popped);

  }

  void Interpreter::MOV_word(Instruction& insn)
  {

    printf("Interpreter::MOV_word(%p)\n", &insn);
    uint16_t src = insn.readFirstArgument<uint16_t>();
    uint16_t dest = insn.readSecondArgument<uint16_t>();

    insn.writeSecondArgument<uint16_t>(src);

  }

  void Interpreter::CMP_byte(Instruction& insn)
  {
    //TODO
  }
  void Interpreter::MOV_byte(Instruction& insn)
  {
    //TODO
  }


}
