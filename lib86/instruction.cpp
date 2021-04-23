#include "instruction.hpp"
#include "registers.hpp"
#include <assert.h>
#include <iostream>
#include <bitset>

namespace Lib86 {

  Instruction::Instruction(void * instptr) :
    m_instruction_ptr(instptr),
    m_first { nullptr},
    m_second { nullptr}
  {
    populate();
  }

  uint8_t Instruction::getByte(int index)
  {
    assert(index<7);

    uint8_t * byte = (uint8_t*) m_instruction_ptr;
    for(int i=0;i<index;i++)
      {
	byte++;
      }

    return *byte;
  }

  bool Instruction::direction()
  {

    auto opcode = getByte(0);
    if(opcode & 0x10)
      return true;
    return false;
  }
  uint8_t Instruction::mod()
  {
    auto opcode = getByte(1);
    auto retval = (opcode & 0b11000000) >> 6;
    std::cout << "\tmod() " << std::bitset<8>(retval) << std::endl;
    return retval;
  }
  uint8_t Instruction::reg()
  {
    auto opcode = getByte(1);
    auto retval =  (opcode & 0b00111000) >> 3;
    std::cout << "\treg() " << std::bitset<8>(retval) << std::endl;
    return retval;
  }
  uint8_t Instruction::rm()
  {
    auto opcode = getByte(1);
    auto retval =  opcode & 0b00000111;
    std::cout << "\trm() " << std::bitset<8>(retval) << std::endl;
    return retval;
  }

  void Instruction::populate()
  {
    std::cout << "Instruction::populate()" << std::endl;
    auto m_mod = mod();
    switch(m_mod)
      {
      case RM_TABLE_1:
	printf ("\tMOD = RM_TABLE_1\n");
	break;
      case RM_TABLE_2_BYTE:
	printf ("\tMOD = RM_TABLE_2_BYTE\n");
	break;
      case RM_TABLE_2_WORD:
	printf ("\tMOD = RM_TABLE_2_WORD\n");
	break;
      case REG:
	printf ("\tMOD = REG\n");
	m_second = (uint16_t*) getRegister(rm());
	break;
      default:
	std::cerr << "\tUnrecognized Mod field of " << std::bitset<8>(m_mod) << std::endl;
      }

    m_first = (uint16_t*) getRegister(reg());

  }
  void * Instruction::getRegister(uint8_t REG)
  {
    //HACK: this just displays instead of getting the correct pointer
    std::cout << "\tInstruction::getRegister(" << std::bitset<8>(REG) << ")" << std::endl << "\t";

    if(word())
      assert("word size" && false);

    switch(REG)
      {
      case AL:
	std::cout << "\tREG "<< std::bitset<3>(REG) << " = AL" << std::endl;
	break;
      case CL:
	std::cout << "\tREG "<< std::bitset<3>(REG) << " = CL" << std::endl;
	break;
      case DL:
	std::cout << "\tREG "<< std::bitset<3>(REG) << " = DL" << std::endl;
	break;
      case BL:
	std::cout << "\tREG "<< std::bitset<3>(REG) << " = DL" << std::endl;
	break;

      case AH:
	std::cout << "\tREG "<< std::bitset<3>(REG) << " = AH" << std::endl;
	break;
      case CH:
	std::cout << "\tREG "<< std::bitset<3>(REG) << " = CH" << std::endl;
	break;
      case DH:
	std::cout << "\tREG "<< std::bitset<3>(REG) << " = DH" << std::endl;
	break;
      case BH:
	std::cout << "\tREG "<< std::bitset<3>(REG) << " = BH" << std::endl;
	break;

      default:
	std::cerr << "Unrecognized REG field of " << std::bitset<3>(REG) << std::endl;
      }


    return (void*) 0x1337;
  }

}
