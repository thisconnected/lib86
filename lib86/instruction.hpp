#pragma once
#include <iostream>

#define wordOrBytePtr uint16_t *

namespace Lib86 {
  

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
    wordOrBytePtr m_first;
    wordOrBytePtr m_second;
    //opcode_entry& m_opentry;
    
  public:
    Instruction(void * instptr) :
      m_instruction_ptr(instptr) {};
    
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
    //HACK: think about real way to do it later 
    // u16 -> u8 casting is -fpermissive prolly with bitshifts?
    auto size = sizeof(t);
    uint8_t * input_ptr = &input;
    uint8_t * argument_ptr = (uint8_t*) m_first;
    for(int i = 0; i<size; i++)
      {
	*input_ptr = *argument_ptr;
	input_ptr++;
	argument_ptr++;
      }
  }
  template <typename t>
  void Instruction::writeSecondArgument(t input)
  {
    //HACK: think about real way to do it later 
    // u16 -> u8 casting is -fpermissive prolly with bitshifts?
    auto size = sizeof(t);
    uint8_t * input_ptr = &input;
    uint8_t * argument_ptr = (uint8_t*) m_second;
    for(int i = 0; i<size; i++)
      {
	*argument_ptr = *input_ptr;
	input_ptr++;
	argument_ptr++;
      }
  }

  template <typename t>
  t Instruction::readFirstArgument()
  {
    t output;
    //HACK: think about real way to do it later 
    // u16 -> u8 casting is -fpermissive prolly with bitshifts?
    auto size = sizeof(t);
    uint8_t * output_ptr = &output;
    uint8_t * argument_ptr = (uint8_t*) m_first;
    for(int i = 0; i<size; i++)
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
    t output;
    //HACK: think about real way to do it later 
    // u16 -> u8 casting is -fpermissive prolly with bitshifts?
    auto size = sizeof(t);
    uint8_t * output_ptr = &output;
    uint8_t * argument_ptr = (uint8_t*) m_first;
    for(int i = 0; i<size; i++)
      {
	*output_ptr = *argument_ptr;
	output_ptr++;
	argument_ptr++;
      }
    return output;
  }



  

  

}