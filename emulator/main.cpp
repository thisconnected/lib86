#include "cpu.hpp"

int main(int argc, char **argv)
{
  Lib86::CPU cpu;
  auto ip = cpu.ip();
  cpu.dump();
  std::cout << ip << std::endl;
  cpu.pointerAtAdress(400);

  return 0;
}






