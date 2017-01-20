
public class Register
{
   protected long reg_a;
   protected long reg_b;
   protected long opcode;
   
   
   public Register(long reg_a, long reg_b, long opcode)
   {
      this.reg_a = reg_a;
      this.reg_b = reg_b;
      this.opcode = opcode;
   }
   
   
   
   public long getOpcode()
   {
      return opcode;
   }



   public void setOpcode(long opcode)
   {
      this.opcode = opcode;
   }
   


   @Override
   public String toString()
   {
      return "Register [reg_a=" + reg_a + ", reg_b=" + reg_b + ", opcode=" + opcode + "]";
   }

   

   public static final String[] reg_lookup = { "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1",
         "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9",
         "$k0", "$k1", "$gp", "$sp", "$fp", "$ra" };
}
   

