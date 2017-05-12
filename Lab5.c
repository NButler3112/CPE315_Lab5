#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mips_asm_header.h"

void printer(char c)
{
   switch(c)
   {
      case 'r':
         break;

      case 'i':
         break;

      case 'j':
         break;

      default:
         printf("Invalid instruction\n");
         break;
   }
}
