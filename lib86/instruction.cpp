#include "instruction.hpp"
#include "registers.hpp"
#include <assert.h>
#include <iostream>
#include <bitset>
#include "cpu.hpp"

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
	size+=1;
	break;
      case RM_TABLE_2_BYTE:
	printf ("\tMOD = RM_TABLE_2_BYTE\n");
	size+=3;
	break;
      case RM_TABLE_2_WORD:
	printf ("\tMOD = RM_TABLE_2_WORD\n");
	size+=3;
	break;
      case REG:
	printf ("\tMOD = REG\n");
	m_second = (uint16_t*) getRegister(rm());
	size++;
	break;
      default:
	std::cerr << "\tUnrecognized Mod field of " << std::bitset<8>(m_mod) << std::endl;
      }

    m_first = (uint16_t*) getRegister(reg());

  }
  void * Instruction::getRegister(uint8_t REG)
  {
    void * retval = (void*) 0x1337;
    //HACK: this just displays instead of getting the correct pointer
    std::cout << "\tInstruction::getRegister(" << std::bitset<8>(REG) << ")" << std::endl << "\t";


    //this should be a jumptable to be faster
    if(word())
      {
	switch(REG)
	  {
	  case AL:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = AX" << std::endl;
	    retval = fakeCPU->ax();
	    break;
	  case CL:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = CX" << std::endl;
	    retval = fakeCPU->cx();
	    break;
	  case DL:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = DX" << std::endl;
	    retval = fakeCPU->dx();
	    break;
	  case BL:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = BX" << std::endl;
	    retval = fakeCPU->bx();
	    break;
	    
	  case AH:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = SP" << std::endl;
	    retval = fakeCPU->sp();
	    break;
	  case CH:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = BP" << std::endl;
	    retval = fakeCPU->bp();
	    break;
	  case DH:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = SI" << std::endl;
	    retval = fakeCPU->si();
	    break;
	  case BH:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = DI" << std::endl;
	    retval = fakeCPU->di();
	    break;
	    
	  default:
	    std::cerr << "Unrecognized REG field of " << std::bitset<3>(REG) << std::endl;
	  }
      }
    else
      {
        switch(REG)
	  {
	  case AL:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = AL" << std::endl;
	    retval = fakeCPU->al();
	    break;
	  case CL:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = CL" << std::endl;
	    retval = fakeCPU->cl();
	    break;
	  case DL:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = DL" << std::endl;
	    retval = fakeCPU->dl();
	    break;
	  case BL:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = BL" << std::endl;
	    retval = fakeCPU->bl();
	    break;

	  case AH:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = AH" << std::endl;
	    retval = fakeCPU->ah();
	    break;
	  case CH:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = CH" << std::endl;
	    retval = fakeCPU->ch();
	    break;
	  case DH:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = DH" << std::endl;
	    retval = fakeCPU->dh();
	    break;
	  case BH:
	    std::cout << "\tREG "<< std::bitset<3>(REG) << " = BH" << std::endl;
	    retval = fakeCPU->bh();
	break;
	  default:
	std::cerr << "Unrecognized REG field of " << std::bitset<3>(REG) << std::endl;
      }
      }

    return retval;
  }

}
