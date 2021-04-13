#include <cpu.cpp>

int main(int argc, char **argv)
{
  Lib86::CPU cpu;
  cpu.dump();
  auto ip = cpu.ip();
  std::cout << ip << std::endl;

  return 0;
}






