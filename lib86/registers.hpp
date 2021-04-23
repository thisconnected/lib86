#pragma once

namespace Lib86
{
  enum MOD_TABLE {
    RM_TABLE_1 = 0b00,
    RM_TABLE_2_BYTE,
    RM_TABLE_2_WORD,
    REG,
  };

  enum REG_TABLE_BYTE {
    AL = 0b000,
    CL,
    DL,
    BL,
    AH,
    CH,
    DH,
    BH,
  };

  enum SREG {
    ES =0b000,
    CS =0b001,
    SS =0b010,
    DS =0b110,
  };

  




}
