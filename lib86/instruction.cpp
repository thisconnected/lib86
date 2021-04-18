#include "instruction.hpp"
#include <assert.h>

namespace Lib86 {

  Instruction::Instruction(void * instptr) :
    m_instruction_ptr(instptr),
    m_first { nullptr},
    m_second { nullptr}
  {

  }

  uint8_t Instruction::byte(int index)
  {
    assert(index<7);

    uint8_t * byte = (uint8_t*) m_instruction_ptr;
    for(int i=0;i<index;i++)
      {
	byte++;
      }

    return *byte;
  }


}
