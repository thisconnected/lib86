#include "node.hpp"

namespace assembler {
  class InsNode: Node
  {
    std::string mnemonic;
    std::string arg1;
    std::string arg2;
  };
}
