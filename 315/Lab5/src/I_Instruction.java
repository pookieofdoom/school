
public class I_Instruction
{
   private long opcode;
   private long rs;
   private long rt;
   private long immed;
   
   
   public long getOpcode()
   {
      return opcode;
   }
   public void setOpcode(long opcode)
   {
      this.opcode = opcode;
   }
   public long getRs()
   {
      return rs;
   }
   public void setRs(long rs)
   {
      this.rs = rs;
   }
   public long getRt()
   {
      return rt;
   }
   public void setRt(long rt)
   {
      this.rt = rt;
   }
   public long getImmed()
   {
      return immed;
   }
   public void setImmed(long immed)
   {
      this.immed = immed;
   }
   
   
}
