
public class R_Instruction
{
   private long opcode;
   private long rs;
   private long rt;
   private long rd;
   private long shamt;
   private long funct;
   


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

   public long getRd()
   {
      return rd;
   }

   public void setRd(long rd)
   {
      this.rd = rd;
   }

   public long getShamt()
   {
      return shamt;
   }

   public void setShamt(long shamt)
   {
      this.shamt = shamt;
   }

   public long getFunct()
   {
      return funct;
   }

   public void setFunct(long funct)
   {
      this.funct = funct;
   }
}
