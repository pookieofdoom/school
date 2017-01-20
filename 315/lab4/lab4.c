/*----------------------------------------------------------------------*
*	Example mips_asm program loader. This loads the mips_asm binary	*
*	named "testcase1.mb" into an array in memory. It reads		*
*	the 64-byte header, then loads the code into the mem array.	*
*									*
*	DLR 4/18/16							*
*----------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mips_asm_header.h"
#define R 0
#define I 1
#define J 2
#define NOT_VALID 3

typedef unsigned int MIPS, *MIPS_PTR;

MB_HDR mb_hdr;		/* Header area */
MIPS mem[1024];		/* Room for 4K bytes */
Jump_Instruction jump;
R_Instruction r_instr;
I_Instruction i_instr;

int check_op(unsigned int opcode)
{
   if (!opcode)
   return R;
   else if (opcode == 0x02 || opcode == 0x03)
   return J;
   else if (opcode == 0x01 || (opcode > 0x03 && opcode < 0x3F))
   return I;
   else
   return NOT_VALID;
}

void print_r(unsigned int opcode, int address, unsigned int instr)
{
   /*decode the r instruction into struct*/
   r_instr.opcode = opcode;
   r_instr.rs = (instr >> 21) & 0x1F;
   r_instr.rt = (instr >> 16) & 0x1F;
   r_instr.rd = (instr >> 11) & 0x1F;
   r_instr.shamt = (instr >> 6) &0x1F;
   r_instr.funct = instr & 0x3F;
   
   /*print out the decode*/
   printf("Instruction at %08X : %08x\n", address, instr);
   printf("\tR Type Instruction w/ Function Code : %02X ", r_instr.funct);
   /*this will use the look up table to see what function it is*/
   printf("(%s)\n", func_lookup[r_instr.funct]);

   if (r_instr.funct == 0x00 || r_instr.funct == 0x02 || r_instr.funct == 0x03) /*shift functions*/
   {
      printf("\tRegister %02X will be shifted by %d and placed into Register %02X\n",
      r_instr.rt, r_instr.shamt, r_instr.rd);
   }

   else if (r_instr.funct == 0x04 || r_instr.funct == 0x06 || r_instr.funct == 0x07) /*shift variable functions*/
   {
      printf("\tRegister %02X will be shifted by Register %02X and placed into Register %02X\n", r_instr.rt, r_instr.rs, r_instr.rd);
   }

   else /*non shift functions or the rest*/
   {
      printf("\tRS : %02X \tRT : %02X \tRD : %02X\n",
      r_instr.rs, r_instr.rt, r_instr.rd);
   }
   
}

void print_j(unsigned int opcode, int address, unsigned int instr)
{
   /*decode the instruction*/
   jump.opcode = opcode;
   jump.index = instr & 0x3FFFFFF;
   
   /*print the decode*/
   printf("Instruction at %08X : %08x\n", address, instr);
   printf("\tJ Type Instruction w/ Opcode : %02X (%s)\n", opcode, op_lookup[opcode]);
   printf("\tEffective Address (PC) : %08X\n", (instr & 0xF0000000) | (jump.index * 4));
   
}

void print_i(unsigned int opcode, int address, unsigned int instr)
{
   /*decode the instruction*/
   i_instr.opcode = opcode;
   int sign_extension = 0;
   printf("Instruction at %08X : %08x\n", address, instr);
   i_instr.rs = (instr >>21) & 0x1F;
   i_instr.rt = (instr >>16) & 0x1F;
   
   printf("\tI Type Instruction w/ Opcode : %02X (%s)\n", opcode, op_lookup[opcode]);
   /*if instruction is beq or bne*/
   if (opcode == 0x04 || opcode == 0x05) { /*beq or bne*/
      printf("\tRegister Compare : RS : %02X \t RT: %02X\n", i_instr.rs, i_instr.rt);
      sign_extension = (instr << 16) & 0x80000000;
       printf("Hello %08X\n", sign_extension);
      sign_extension >>= 13;
      printf("Hello %08X\n", sign_extension);
      i_instr.immed = instr & 0xFFFF;
      printf("\tEffective Address (PC) if taken : %08X \tnot taken : %08X\n",
      address + 4 + (sign_extension | i_instr.immed), address + 4);  
   }
   /*any other immediate instructions*/
   else
   {
      /*change the sign extension if its addi or addiu*/
      if (opcode == 0x08 || opcode == 0x09) { /*addi and addiu sign extension*/
         sign_extension = (instr << 16) & 0x80000000;
         sign_extension >>= 15; 
      }

      i_instr.immed = sign_extension | (instr & 0xFFFF);
      printf("\tRS : %02X \tRT : %02X \tImmed : %08X\n",
      i_instr.rs, i_instr.rt, i_instr.immed);
   }

}

/*main function that decides what it is decoding*/
void add_instruction(unsigned int opcode, int address, unsigned int instruction)
{
   int type = check_op(opcode);
   if (type == R)
   {
      print_r(opcode, address, instruction);
   }
   else if(type == I)
   {
      print_i(opcode, address, instruction);
   }
   else if (type == J)
   {
      print_j(opcode, address, instruction);
   }
   else 
   {
      printf("Invalid Instruction @ %08X : %08X\n", address, instruction);
   }
}
int main()
{
   FILE *fd;
   int n;
   int memp;
   int i;
   char filename[] = "testcase1.mb";	/* This is the filename to be loaded */
   unsigned int opcode;
   int num = 1;
   /* format the MIPS Binary header */

   fd = fopen(filename, "rb");
   if (fd == NULL) { printf("\nCouldn't load test case - quitting.\n"); exit(99); }

   memp = 0;		/* This is the memory pointer, a byte offset */

   /* read the header and verify it. */
   fread((void *) &mb_hdr, sizeof(mb_hdr), 1, fd);
   if (! strcmp(mb_hdr.signature, "~MB")==0)
   { printf("\nThis isn't really a mips_asm binary file - quitting.\n"); exit(98); }

   printf("\n%s Loaded ok, program size=%d bytes.\n\n", filename, mb_hdr.size);

   /* read the binary code a word at a time */

   do {
      n = fread((void *) &mem[memp/4], 4, 1, fd); /* note div/4 to make word index */
      if (n) 
      memp += 4;	/* Increment byte pointer by size of instr */
      else
      break;       
   } while (memp < sizeof(mem)) ;

   fclose(fd);


   /* ok, now dump out the instructions loaded: */

   for (i = 0; i<memp; i+=4)	/* i contains byte offset addresses */
   {
      opcode = (mem[i/4] >> 26) & 0x3F;
      printf("%d. ", num++);
      add_instruction(opcode, i, mem[i/4]);
      printf("\n\n");     
   }

   exit(0);
}
