#include <stdio.h>
#include "cpu.hpp"

namespace Lib86
{

  void CPU::dump()
  {
    printf("ip:%x\n",m_ip);
    printf("ah:%x\tal:%x\tbh:%x\tbl:%x\tch:%x\tcl:%x\tdh:%x\tdl:%x\n",ah(),al(),0,0,0,0,0,0);

  }

  CPU::CPU()
  {
    printf("spawning cpu\n");
    m_ax = 128;
    m_ip = 15000;
  }

}
