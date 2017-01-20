
public class Jump_Instruction extends Register
{

   private long index;
   
   public Jump_Instruction(long reg_a, long reg_b, long opcode,
         long index)
   {
      super(reg_a, reg_b, opcode);
      this.index = index;
      
   }
   
   
   public int j_execute(int pc)
   {
      int idx = (int) this.index;
      int output = 0;
      switch ((int) this.opcode)
      {
         case 0x02: /*j*/
            output = (pc & 0xF0000000) | (idx << 2);
            break;
         
         case 0x03: /*jal*/
            output = pc + 4;
            pc = (pc & 0xF0000000) | (idx << 2);
            break;
      }
      return output;
   }

}
