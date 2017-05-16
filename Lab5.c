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
   else if (opcode == 0x04 || opcode == 0x05 || opcode == 0x08\
      || opcode == 0x09 || opcode == 0x0A || opcode == 0x0B || opcode == 0x0C\
      || opcode == 0x0D || opcode == 0x0E || opcode == 0x0F || opcode == 0x20\
      || opcode == 0x21 || opcode == 0x23 || opcode == 0x24 || opcode == 0x25\
      || opcode == 0x28 || opcode == 0x29 || opcode == 0x2B)
   {
      return 1;   /*Indicates I type instruction*/
   }
   else
   {
      return -1;  /*Indicates invalid type instruction*/
   }
}

static void rType(unsigned int instr, unsigned int opcode)
{
   /*unsigned int rs, rt, rd, shamt, funct;
   rs = instr & 0x03E00000;
   rs >>= 21;
   rt = instr & 0x001F0000;
   rt >>= 16;
   rd = instr & 0x0000F800;
   rd >>= 11;
   shamt = instr & 0x000007A;
   shamt >>= 6;
   funct = instr & 0x0000003F;*/
}

static unsigned int branchAddr(unsigned int immed)
{
   unsigned int brAdd = 0x00000000, immed15 = immed & 0x8000,\
      immedS = immed << 2;

   if (immed15 == 1)
   {
      brAdd |= 0xFFFC0000;
   }
   brAdd |= immedS;
   return brAdd;
}

static unsigned int zeroExtImmed(unsigned int immed)
{
   int ret = 0x00000000 | immed;
   return ret;
}

static unsigned int signExtImmed(unsigned int immed)
{
   int ret = 0x00000000 | immed, immed15 = immed & 0x8000;
   
   if (immed15 == 1)
   {
      ret |= 0xFFFF0000;
   }
   return ret;
}

static void iType(unsigned int instr, unsigned int opcode)
{
   unsigned int rs, rt, immed;
   rs = instr & 0x03E00000;
   rs >>= 21;
   rt = instr & 0x001F0000;
   rt >>= 16;
   immed = instr & 0x0000FFFF;

   if (opcode == 0x04 || opcode == 0x05)
   {
      immed = branchAddr(immed);
   }
   else if (opcode == 0x08 || opcode == 0x09 || opcode == 0x0A\
      || opcode == 0x0B || opcode == 0x20 || opcode == 0x21 || opcode == 0x23\
      || opcode == 0x24 || opcode == 0x28 || opcode == 0x29 || opcode == 0x2B)
   {
      immed = signExtImmed(immed);
   }
   else if (opcode == 0x0C || opcode == 0x0D || opcode == 0x0E\
      || opcode == 0x25)
   {
      immed = zeroExtImmed(immed);
   }

   printf("   Immediate Instruction\n");
   printf("   Rs: 0x%02X, Rt: 0x%02X, Formatted Immediate: 0x%08X\n", rs, rt, immed);
}

static void jType(int pc, unsigned int instr, unsigned int opcode)
{
   unsigned int tempPC, tempWord, word = 0x00000000;
   tempPC = pc & 0xF0000000;
   word |= tempPC;
   tempWord = instr & 0x03FFFFFF;
   tempWord <<= 2;
   word |= tempWord;

   printf("   Jump Instruction: ");
   if (opcode == 0x02)
   {
      printf("Jump\n");
   }
   else if (opcode == 0x03)
   {
      printf("Jump and Link\n");
   }
   printf("   Jump Address: 0x%08X\n", word);
}

void mainDecoder(int i, unsigned int m)
{
   unsigned int opcode, sOpcode, mask = 0xFC000000;
   opcode = m & mask;
   opcode >>= 26;
   sOpcode = findInstruc(opcode);
   if (sOpcode == -1)
   {
      printf("Invalid Instruction: %08X\n", m);
   }
   else if (sOpcode == 0)
   {
      rType(m, opcode);
   }
   else if (sOpcode == 1)
   {
      iType(m, opcode);
   }
   else if (sOpcode == 2)
   {
      jType(i, m, opcode);
   }
}
