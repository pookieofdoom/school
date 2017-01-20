/*Decode Cycle (ID)
 * Read IF/ID pipline register to get instruction bits
 * Decode instruction, generate control signals
 * Read from register file
 */
public class Decode
{
   
   public static final int R = 0;
   public static final int I = 1;
   public static final int J = 2;
   public static final int NOT_VALID = 3;
   

   
   private static int check_op(long opcode)
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
   
   
   public ID_EX run(int[] reg_val, IF_ID if_id_pipe)
   { 
      /*determines what instruction is and read registers*/
    
      Register reg = null;
      long instruction = if_id_pipe.getInstruction();

      long a = (instruction >> 21) & 0x1F;
      System.out.print(Register.reg_lookup[(int) a] + ", ");
      
      long b = (instruction >> 16) & 0x1F;
      System.out.println(Register.reg_lookup[(int) b]);    
      long opcode = (instruction >> 26) & 0x3F;
      int type = check_op(opcode);
      
      if (type == R)
      {
         long rd = (instruction >> 11) & 0x1F;
         long shamt = (instruction >> 6) & 0x1F;
         long funct = instruction & 0x3F;
         reg = new R_Instruction(reg_val[(int)a], reg_val[(int)b], opcode,
               rd, shamt, funct);
      }
      else if (type == J)
      {
         long index = instruction & 0x3FFFFFF;
         reg = new Jump_Instruction(reg_val[(int)a], reg_val[(int)b], opcode,
               index);
      }
      else //type == i
      {
         long immed = instruction & 0xFFFF;
         int sign_extension = (int) ((instruction << 16) & 0x80000000);
         sign_extension >>= 15;
         reg = new I_Instruction(reg_val[(int)a], reg_val[(int)b], opcode,
               immed, sign_extension);
      }
      
      return new ID_EX(reg, if_id_pipe.getPc());
   }
   
}
