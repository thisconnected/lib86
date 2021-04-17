#include "instruction.hpp"

namespace Lib86 {

template <typename t>
void Instruction::writeFirstArgument(t input)
{
  *(t)m_first = input;
}
  
template <typename t>
void Instruction::writeSecondArgument(t input)
{
  *(t)m_second = input;
}
  
template <typename t>
t Instruction::readFirstArgument()
{
  return *(t)m_first;
}
  
template <typename t>
t Instruction::readSecondArgument()
{
  return *(t) m_second;
}


}
