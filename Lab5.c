#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mips_asm_header.h"

static unsigned int findInstruc(unsigned int opcode)
{
   if (opcode == 0x00)
   {
      return 0;   /*Indicates R type instruction*/
   }
   else if (opcode == 0x02 || opcode == 0x03)
   {
      return 2;   /*Indicates J type instruction*/
   }
   else if (opcode == 0x04 || opcode == 0x05 || opcode == 0x08 || opcode == 0x09\
      || opcode == 0x0A || opcode == 0x0B || opcode == 0x0C || opcode == 0x0D\
      || opcode == 0x0E || opcode == 0x0F || opcode == 0x20 || opcode == 0x21\
      || opcode == 0x23 || opcode == 0x24 || opcode == 0x25 || opcode == 0x28\
      || opcode == 0x29 || opcode == 0x2B)
   {
      return 1;   /*Indicates I type instruction*/
   }
   else
   {
      return -1;  /*Indicates invalid type instruction*/
   }
}

void mainDecoder(unsigned int m)
{
   unsigned int opcode, mask = 0xFC000000;
   opcode = m & mask;

   opcode = findInstruc(opcode);
   printf("%u\n", opcode);
}
