#include "disassembler.hpp"
#include <iostream>

namespace Lib86 {

  void Disassembler::disassembleAtPoint(void * memory)
  {
    uint8_t opcode = *(uint8_t*)memory;
    printf("op:%d mne:%s ", opcode_table[opcode].opcode, opcode_table[opcode].mnemonic);
  }
  

}
