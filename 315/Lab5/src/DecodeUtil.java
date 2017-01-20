
public class DecodeUtil
{
   public static final int R = 0;
   public static final int I = 1;
   public static final int J = 2;
   public static final int NOT_VALID = 3;
   
   public static int r_execute(R_Instruction r_instr, int pc, int[] register,
         int num_instr, int num_mem, int num_clock)
   {
      int rd = (int) r_instr.getRd();
      int rs = (int) r_instr.getRs();
      int rt = (int) r_instr.getRt();
      
      switch ((int) r_instr.getFunct())
      {
         case 0x00: /* sll */
            register[rd] = register[rt] << (int) r_instr.getShamt();
            pc += 4;
            break;

         case 0x02: /* srl */
            register[rd] = register[rt] >>> (int) r_instr.getShamt();
            pc += 4;
            break;

         case 0x03: /* sra */
            register[rd] = register[rt] >> (int) r_instr.getShamt();
            pc += 4;
            break;
            
         case 0x04: /*sllv*/
            register[rd] = register[rt] << register[rs];   
            pc += 4;
            break;

         case 0x06: /* srlv */
            register[rd] = register[rt] >>> register[rs];
            pc += 4;
            break;

         case 0x07: /* srav */
            register[rd] = register[rt] >> register[rs];
            pc += 4;
            break;
            
         case 0x08: /*jr*/
            pc = register[rs];
            break;
         case 0x09: /*jal*/
            register[31] = pc + 4;
            pc = register[rs];
            break;
         
         case 0x0C: /*syscall*/
            if (register[2] == 10)
            {
               System.out.println("End of Program");
               System.out.printf("%d instructions simulated\t%d mem references\t%d "
                     + "clock cycles expended\n", num_instr, num_mem, num_clock);
               System.exit(0);
            }
            pc+=4;
            break;
            
         case 0x20: /* add */
            register[rd] = register[rs] + register[rt];
            pc += 4;
            break;
         
         case 0x21: /*addu*/
            /*this might be wrong.. overflow??*/
            register[rd] = register[rs] + register[rt];
            pc += 4;
            break;
            
         case 0x22: /* sub */
            register[rd] = register[rs] - register[rt];
            pc += 4;
            break;
            
         case 0x23: /*subu*/
            register[rd] = register[rs] - register[rt];
            pc += 4;
            break;
            
         case 0x24: /*and*/
            register[rd] = register[rs] & register[rt];
            pc += 4;
            break;
            
         case 0x25: /* or*/
            register[rd] = register[rs] | register[rt];
            pc += 4;
            break;
            
         case 0x26: /*xor*/
            register[rd] = register[rs] ^ register[rt];
            pc += 4;
            break;
            
         case 0x27: /*nor*/
            register[rd] = ~(register[rs] | register[rt]);
            pc += 4;
            break;
            
         case 0x2A: /*slt*/
            register[rd] = (register[rs] < register[rt]) ? 1 : 0;
            pc += 4;
            break;
            
         case 0x2B: /*sltu*/
            register[rd] = (register[rs] < register[rt]) ? 1 : 0;
            pc += 4;
            break;
            
      }
      return pc;
      
   }
   
   public static int i_execute(I_Instruction i_instr, long instruction, int pc, int[] register, long[] mem_reg)
   {
      int sign_immed = 0;
      int rt = (int) i_instr.getRt();
      int rs = (int) i_instr.getRs();
      int immed = (int) i_instr.getImmed();
      switch ((int) i_instr.getOpcode())
      {

         case 0x04: /* beq */
            sign_immed = DecodeUtil.sign_extend(i_instr, instruction);
            if (register[rs] == register[rt])
               pc = pc + 4 + (sign_immed << 2);
            else
               pc += 4;
            break;

         case 0x05: /* bne */
            sign_immed = DecodeUtil.sign_extend(i_instr, instruction);
            if (register[rs] != register[rt])
               pc = pc + 4 + (sign_immed << 2);
            else
               pc += 4;
            break;

         case 0x08: /* addi */
            sign_immed = DecodeUtil.sign_extend(i_instr, instruction);
            register[rt] = (int) (register[rs] + sign_immed);
            pc += 4;
            break;

         case 0x09: /* addiu */
            sign_immed = DecodeUtil.sign_extend(i_instr, instruction);
            register[rt] = (int) (register[rs] + sign_immed);
            pc += 4;
            break;

         case 0x0A: /* slti */
            sign_immed = DecodeUtil.sign_extend(i_instr, instruction);
            register[rt] = (register[rs] < sign_immed) ? 1 : 0;
            pc += 4;
            break;

         case 0x0B: /* sltiu */
            sign_immed = DecodeUtil.sign_extend(i_instr, instruction);
            register[rt] = (register[rs] < sign_immed) ? 1 : 0;
            pc += 4;
            break;

         case 0x0C: /* andi */
            register[rt] = register[rs] & immed;
            pc += 4;
            break;

         case 0x0D: /* ori */
            register[rt] = (int) (register[rs] | immed);
            pc += 4;
            break;

         case 0x0E: /* xori */
            register[rt] = register[rs] ^ immed;
            pc += 4;
            break;

         case 0x0F: /* lui */
            /* test this */
            register[rt] = immed << 16;
            pc += 4;
            break;

         case 0x20: /* lb */
            int sign_extend = 0;
            sign_immed = DecodeUtil.sign_extend(i_instr, instruction);
            register[rt] = (int) mem_reg[register[rs] + sign_immed];
            sign_extend = (register[rt] << 24) & 0x80000000;
            sign_extend >>= 23;
            register[rt] |= sign_extend;
            pc += 4;
            break;

         case 0x21: /* lh */
            sign_extend = 0;
            sign_immed = DecodeUtil.sign_extend(i_instr, instruction);
            register[rt] = (int) mem_reg[register[rs] + sign_immed];
            sign_extend = (register[rt] << 16) & 0x80000000;
            sign_extend >>= 15;
            register[rt] |= sign_extend;
            pc += 4;
            break;
            
         case 0x23: /* lw */
            sign_immed = DecodeUtil.sign_extend(i_instr, instruction);
            register[rt] = (int) mem_reg[register[rs] + sign_immed];
            pc += 4;
            break;

         case 0x24: /* lbu */
            sign_immed = DecodeUtil.sign_extend(i_instr, instruction);
            register[rt] = (int) mem_reg[register[rs] + sign_immed] & 0xFF;
            pc += 4;
            break;
            
         case 0x25: /* lhu */
            sign_immed = DecodeUtil.sign_extend(i_instr, instruction);
            register[rt] = (int) mem_reg[register[rs] + sign_immed] & 0xFFFF;
            pc += 4;
            break;
            
         case 0x28: /* sb */
            sign_immed = DecodeUtil.sign_extend(i_instr, instruction);
            mem_reg[register[rs] + sign_immed] = register[rt] & 0xFF;
            pc += 4;
            break;
            
         case 0x29: /* sh */
            sign_immed = DecodeUtil.sign_extend(i_instr, instruction);
            mem_reg[register[rs] + sign_immed] = register[rt] & 0xFFFF;
            pc += 4;
            break;
            
         case 0x2B: /* sw */
            sign_immed = DecodeUtil.sign_extend(i_instr, instruction);
            mem_reg[register[rs] + sign_immed] = register[rt];
            pc += 4;
            break;
      }
      return pc;
   }
   public static boolean check_nop(R_Instruction r_instr)
   {
      boolean flag = false;
      if (r_instr.getOpcode() != 0)
      {
         flag = true;
      }
      if (r_instr.getRd() != 0)
      {
         flag = true;
      }
      if (r_instr.getRs() != 0)
      {
         flag = true;
      }
      if (r_instr.getRd() != 0)
      {
         flag = true;
      }
      if (r_instr.getShamt() != 0)
      {
         flag = true;
      }
      if (r_instr.getFunct() != 0)
      {
         flag = true;
      }
      return flag;

   }
   
   public static int sign_extend(I_Instruction i_instr, long instruction)
   {
      int immed = (int) i_instr.getImmed();
      int sign_extension = (int) ((instruction << 16) & 0x80000000);
      sign_extension >>= 15;
      i_instr.setImmed(immed | sign_extension);
      return (int) i_instr.getImmed();
   }

   public static int j_execute(Jump_Instruction j_instr, int pc, int[] register)
   {
      int idx = (int) j_instr.getIndex();
      switch ((int) j_instr.getOpcode())
      {
         case 0x02: /*j*/
            pc = (pc & 0xF0000000) | (idx << 2);
            break;
         
         case 0x03: /*jal*/
            register[31] = pc + 4;
            pc = (pc & 0xF0000000) | (idx << 2);
            break;
      }
      return pc;
   }
   
   public static void add_instruction(int pc, long opcode, int address, long instruction)
   {

      int type = check_op(opcode);

      if (type == R)
      {
         print_r(opcode, address, instruction);
      }
      else if (type == I)
      {
         print_i(opcode, address, instruction);
      }
      else if (type == J)
      {
         print_j(opcode, address, instruction);
      }
      else
      {
         System.out.printf("Invalid Instruction @ %08X : %08X\n", address, instruction);
      }
      System.out.format("\n\n");

   }
   
   public static void print_j(long opcode, int address, long instr)
   {
      /* decode the instruction */
      Jump_Instruction jump = new Jump_Instruction();
      jump.setOpcode(opcode);
      jump.setIndex(instr & 0x3FFFFFF);

      /* print the decode */
      System.out.printf("Instruction at %08X : %08x\n", address, instr);
      System.out.printf("\tJ Type Instruction w/ Opcode : %02X (%s)\n", opcode, op_lookup[(int) opcode]);
      System.out.printf("\tEffective Address (PC) : %08X\n", (instr & 0xF0000000) | (jump.getIndex() * 4));

   }

   public static void print_i(long opcode, int address, long instr)
   {
      /* decode the instruction */
      I_Instruction i_instr = new I_Instruction();
      i_instr.setOpcode(opcode);
      int sign_extension = 0;
      System.out.printf("Instruction at %08X : %08x\n", address, instr);
      i_instr.setRs((instr >> 21) & 0x1F);
      i_instr.setRt((instr >> 16) & 0x1F);

      System.out.printf("\tI Type Instruction w/ Opcode : %02X (%s)\n", opcode, op_lookup[(int) opcode]);
      /* if instruction is beq or bne */
      if (opcode == 0x04 || opcode == 0x05)
      { /* beq or bne */
         System.out.printf("\tRegister Compare : RS : %02X \t RT: %02X\n", i_instr.getRs(), i_instr.getRt());
         sign_extension = (int) (instr << 16) & 0x80000000;
         sign_extension >>= 13;
         i_instr.setImmed(instr & 0xFFFF);
         System.out.printf("\tEffective Address (PC) if taken : %08X \tnot taken : %08X\n",
               address + 4 + (sign_extension | (int) i_instr.getImmed()), address + 4);
      }
      /* any other immediate instructions */
      else
      {
         /* change the sign extension if its addi or addiu */
         if (opcode == 0x08 || opcode == 0x09)
         { /* addi and addiu sign extension */
            sign_extension = (int) ((instr << 16) & 0x80000000);
            sign_extension >>= 15;
         }
         /* note may be a problem later */
         i_instr.setImmed(sign_extension | (int) (instr & 0xFFFF));
         System.out.printf("\tRS : %02X \tRT : %02X \tImmed : %08X\n", i_instr.getRs(), i_instr.getRt(),
               i_instr.getImmed());
      }

   }

   public static void print_r(long opcode, int address, long instr)
   {
      /* decode the r instruction into struct */
      R_Instruction r_instr = new R_Instruction();
      r_instr.setOpcode(opcode);
      r_instr.setRs((instr >> 21) & 0x1F);
      r_instr.setRt((instr >> 16) & 0x1F);
      r_instr.setRd((instr >> 11) & 0x1F);
      r_instr.setShamt((instr >> 6) & 0x1F);
      r_instr.setFunct(instr & 0x3F);

      /* print out the decode */
      System.out.printf("Instruction at %08X : %08x\n", address, instr);
      System.out.printf("\tR Type Instruction w/ Function Code : %02X ", r_instr.getFunct());
      /* this will use the look up table to see what function it is */
      System.out.printf("(%s)\n", func_lookup[(int) r_instr.getFunct()]);

      if (r_instr.getFunct() == 0x00 || r_instr.getFunct() == 0x02 || r_instr.getFunct() == 0x03)
      /* shift functions */
      {
         System.out.printf("\tRegister %02X will be shifted by %d and placed into Register %02X\n", r_instr.getRt(),
               r_instr.getShamt(), r_instr.getRd());
      }

      else if (r_instr.getFunct() == 0x04 || r_instr.getFunct() == 0x06 || r_instr.getFunct() == 0x07)
      /* shift variable functions */
      {
         System.out.printf("\tRegister %02X will be shifted by Register %02X " + "and placed into Register %02X\n",
               r_instr.getRt(), r_instr.getRs(), r_instr.getRd());
      }

      else /* non shift functions or the rest */
      {
         System.out.printf("\tRS : %02X \tRT : %02X \tRD : %02X\n", r_instr.getRs(), r_instr.getRt(), r_instr.getRd());
      }

   }

   public static int check_op(long opcode)
   {
      if (opcode == 0)
         return R;
      else if (opcode == 0x02 || opcode == 0x03)
         return J;
      else if (opcode == 0x01 || (opcode > 0x03 && opcode < 0x3F))
         return I;
      else
         return NOT_VALID;
   }
   
   public static final String[] func_lookup = { "Logical Shift Left", "Not Available", "Logical Shift Right",
         "Shift Right Arithmetic", "Shift Left Logical Var.", "Not Available", "Shift Right Logical Var.",
         "Shift Right Arithmetic Var.", "Jump Register", "Jump And Link Register", "Not Available", "Not Available",
         "Syscall", "Not Available", "Not Available", "Not Available", "Move From HI", "Not Available", "Move From LO",
         "Not Available", "Not Available", "Not Available", "Not Available", "Not Available", "Multiply",
         "Multiply Unsigned", "Divide", "Divide Unsigned", "Not Available", "Not Available", "Not Available",
         "Not Available", "Add", "Add Unsigned", "Subtract", "Subtract Unsigned", "And", "Or", "Xor", "Nor",
         "Not Available", "Not Available", "Set Less Than", "Set Less Than Unsigned" };

   public static final String[] op_lookup = { "Register Instruction", "Not Available", "Jump Instruction",
         "Jump And Link", "Branch On Equal", "Branch On Not Equal", "Not Available", "Not Available", "Add Immediate",
         "Add Immediate Unsigned", "Set Less Than Immediate", "Set Less Than Immediate Unsigned", "And Immediate",
         "Or Immediate", "Xor Immediate", "Load Upper Immediate", "Not Available", "Not Available", "Not Available",
         "Not Available", "Not Available", "Not Available", "Not Available", "Not Available", "Not Available",
         "Not Available", "Not Available", "Not Available", "Not Available", "Not Available", "Not Available",
         "Not Available", "Load Byte", "Load Halfword", "Not Available", "Load Word", "Load Byte Unsigned",
         "Load Halfword Unsigned", "Not Available", "Not Available", "Store Byte", "Store Halfword", "Not Available",
         "Store Word" };

   public static final String[] reg_lookup = { "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1",
         "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9",
         "$k0", "$k1", "$gp", "$sp", "$fp", "$ra" };
}
