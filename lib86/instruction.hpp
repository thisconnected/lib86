#pragma once

namespace Lib86 {
  
  enum reg_8 {
    al = 0,
    cl,
    dl,
    bl,
    ah,
    ch,
    dh,
    bh,
  };
  enum reg_16 {
    ax = 0,
    cx,
    dx,
    bx,
    sp,
    bp,
    si,
    di,
  };
  enum rm_table1 {
  };
  enum rm_table2 {
  };
  
  
  class Instruction
  {
  public:
   bool direction();
  };


}
