#include "interrupt.hpp"


namespace Lib86 {

  void handle_interrupt(int number, CPU * cpustate)
  {
    //takes service from AH

    uint8_t service = *cpustate->ah();

    printf("Interrupt %x Service %x\n",number, service);

    switch (service)
      {
      case 0x01:
	interrupt_sysexit();
	break;

      }
    
  }

  void interrupt_sysexit()
  {
    printf("exiting\n");
    fflush(stdout);
    exit(0);

  }

}
