#pragma once

#define MAXMEM 64*1000

enum immidiate
  {
    no,
    imm8,
    imm16
  };


union wordOrByte
  {
    struct {
      int16_t low_u16;
    };
    struct {
      int8_t low_u8;
      int8_t high_u8;
    };
  };
