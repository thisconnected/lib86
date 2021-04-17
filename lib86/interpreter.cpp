#include "interpreter.hpp"
#include "instruction.hpp"

namespace Lib86 {

void Interpreter::ADD_byte(Instruction& insn)
{
  //FIXME: this is actually just for debugging
  uint8_t src1 = insn.readFirstArgument<uint8_t>();
  uint8_t src2 = insn.readSecondArgument<uint8_t>();

  //FIXME: update flags
  uint8_t dest = src1 + src2;

  printf("ADD %d + %d = %d ", src1,src2,dest);
  insn.writeFirstArgument<uint8_t>(dest);

}
  
// void Interpreter::ADD_word(Instruction& insn)
// {
//   //FIXME: this is actually just for debugging
//   uint16_t src1 = insn.readFirstArgument<uint16_t>();
//   uint16_t src2 = insn.readSecondArgument<uint16_t>();

//   //FIXME: update flags
//   uint16_t dest = src1 + src2;

//   printf("ADD %d + %d = %d ", src1,src2,dest);
//   insn.writeFirstArgument<uint16_t>(dest);
// }




}
