#pragma once
#include <iostream>

#define wordOrBytePtr uint16_t *

namespace Lib86 {

  class CPU;

  // union wordOrBytePtr {
  //   uint8_t * (*byte)(uint16_t);
  //   uint16_t * (*word)(uint16_t);
  // };

  // union wordOrByte {
  //   uint8_t * (*byte)(uint16_t);
  //   uint16_t * (*word)(uint16_t);
  // };

  
  class Instruction
  {
  private:
    const void * m_instruction_ptr;
    wordOrBytePtr m_first = {};
    wordOrBytePtr m_second = {};
    //opcode_entry& m_opentry;
    
    //plumbing for finding operands

    bool word() { return  *(uint8_t*)m_instruction_ptr & 0b10000000 ? true : false ;};
    bool direction();
    uint8_t mod();
    uint8_t reg();
    uint8_t rm();
    void populate();
    void* getRegister(uint8_t REG);

  public:
    static CPU * fakeCPU;
    Instruction(void * instptr);
    uint8_t getByte(int index);
    template <typename t> void writeFirstArgument(t input);
    template <typename t> void writeSecondArgument(t input);
    template <typename t> t readFirstArgument();
    template <typename t> t readSecondArgument();

    void test() {
      *m_first = 0xFF00;
      *m_second = 0x00DD;
    };
    
    
  };

  template <typename t>
  void Instruction::writeFirstArgument(t input)
  {
    std::cout << "\tInstruction::writeFirstArgument(" << (int) input << ")" << " to mem " << m_first  << std::endl;
    //HACK: think about real way to do it later 
    // u16 -> u8 casting is -fpermissive prolly with bitshifts?
    auto size = sizeof(t);
    uint8_t * input_ptr = &input;
    uint8_t * argument_ptr = (uint8_t*) m_first;
    printf("\targument_ptr=%p\n",argument_ptr);
    printf("\t*argument_ptr=%d\n",*argument_ptr);
    for(uint i = 0; i<size; i++)
      {
	*argument_ptr = *input_ptr;
	input_ptr++;
	argument_ptr++;
      }
  }
  template <typename t>
  void Instruction::writeSecondArgument(t input)
  {
    std::cout << "\tInstruction::writeSecondArgument(" << (int) input << ")" << " to mem " << m_second  << std::endl;
    //HACK: think about real way to do it later 
    // u16 -> u8 casting is -fpermissive prolly with bitshifts?
    auto size = sizeof(t);
    uint8_t * input_ptr = &input;
    uint8_t * argument_ptr = (uint8_t*) m_second;
    for(uint i = 0; i<size; i++)
      {
	*argument_ptr = *input_ptr;
	input_ptr++;
	argument_ptr++;
      }
  }

  template <typename t>
  t Instruction::readFirstArgument()
  {
    std::cout << "\tInstruction::readFirstArgument(" <<  ")" << " from mem " << m_first  << std::endl;
    t output;
    //HACK: think about real way to do it later 
    // u16 -> u8 casting is -fpermissive prolly with bitshifts?
    auto size = sizeof(t);
    uint8_t * output_ptr = &output;
    uint8_t * argument_ptr = (uint8_t*) m_first;
    for(uint i = 0; i<size; i++)
      {
	*output_ptr = *argument_ptr;
	output_ptr++;
	argument_ptr++;
      }
    return output;
  }
  
  template <typename t>
  t Instruction::readSecondArgument()
  {
    std::cout << "\tInstruction::readSecondArgument(" <<  ")" << " from mem " << m_second  << std::endl;
    t output;
    //HACK: think about real way to do it later 
    // u16 -> u8 casting is -fpermissive prolly with bitshifts?
    auto size = sizeof(t);
    uint8_t * output_ptr = &output;
    uint8_t * argument_ptr = (uint8_t*) m_second;
    for(uint i = 0; i<size; i++)
      {
	*output_ptr = *argument_ptr;
	output_ptr++;
	argument_ptr++;
      }
    return output;
  }



  

  

}
