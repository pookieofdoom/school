
public class I_Instruction extends Register
{
   private long immed;
   private int sign_extension;
   
   public I_Instruction(long reg_a, long reg_b, long opcode,
         long immed, int sign_extension)
   {
      super(reg_a, reg_b, opcode);
      this.immed = immed;
      this.sign_extension = sign_extension;
   }
   
   public static final String[] op_lookup = { "Register Instruction", "Not Available", "Jump Instruction",
         "Jump And Link", "Branch On Equal", "Branch On Not Equal", "Not Available", "Not Available", "Add Immediate",
         "Add Immediate Unsigned", "Set Less Than Immediate", "Set Less Than Immediate Unsigned", "And Immediate",
         "Or Immediate", "Xor Immediate", "Load Upper Immediate", "Not Available", "Not Available", "Not Available",
         "Not Available", "Not Available", "Not Available", "Not Available", "Not Available", "Not Available",
         "Not Available", "Not Available", "Not Available", "Not Available", "Not Available", "Not Available",
         "Not Available", "Load Byte", "Load Halfword", "Not Available", "Load Word", "Load Byte Unsigned",
         "Load Halfword Unsigned", "Not Available", "Not Available", "Store Byte", "Store Halfword", "Not Available",
         "Store Word" };

   private int sign_extend()
   {
      int immed = (int) this.immed;
      int sign_extension = this.sign_extension;
      this.immed = (immed | sign_extension);
      return (int) this.immed;
   }
   
   public int i_execute(int pc)
   {
      int sign_immed = 0;
      int rt = (int) this.reg_b;
      int rs = (int) this.reg_a;
      int immed = (int) this.immed;
      int output = 0;
      switch ((int) this.opcode)
      {

//         case 0x04: /* beq */
//            sign_immed = sign_extend();
//            if (rs == rt)
//               pc = pc + 4 + (sign_immed << 2);
//
//            break;
//
//         case 0x05: /* bne */
//            sign_immed = sign_extend();
//            if (rs != rt)
//               pc = pc + 4 + (sign_immed << 2);
//
//            break;

         case 0x08: /* addi */
            sign_immed = sign_extend();
            output = (int) (rs + sign_immed);
            break;

         case 0x09: /* addiu */
            sign_immed = sign_extend();
            output = (int) (rs + sign_immed);
            break;

         case 0x0A: /* slti */
            sign_immed = sign_extend();
            output = (rs < sign_immed) ? 1 : 0;
            break;

         case 0x0B: /* sltiu */
            sign_immed = sign_extend();
            output = (rs < sign_immed) ? 1 : 0;
            break;

         case 0x0C: /* andi */
            output = rs & immed;
            break;

         case 0x0D: /* ori */
            output = (int) (rs | immed);
            break;

         case 0x0E: /* xori */
            output = rs ^ immed;
            break;

         case 0x0F: /* lui */
            output = immed << 16;
            break;

         case 0x20: /* lb */
            sign_immed = sign_extend();
            output = rs + sign_immed;
            break;

         case 0x21: /* lh */
            sign_immed = sign_extend();
            output = (int) rs + sign_immed;
            break;
            
         case 0x23: /* lw */
            sign_immed = sign_extend();
            output = (int) rs + sign_immed;
            break;

         case 0x24: /* lbu */
            sign_immed = sign_extend();
            output = (int) rs + sign_immed;
            break;
            
         case 0x25: /* lhu */
            sign_immed = sign_extend();
            output = (int) rs + sign_immed;
            break;
            
         case 0x28: /* sb */
            sign_immed = sign_extend();
            output = (int) rs + sign_immed;
            break;
            
         case 0x29: /* sh */
            sign_immed = sign_extend();
            output = (int) rs + sign_immed;
            break;
            
         case 0x2B: /* sw */
            sign_immed = sign_extend();
            output = (int) rs + sign_immed;
            break;
      }
      return output;
   }

}
