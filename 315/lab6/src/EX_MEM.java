/*Basket between Ex and Mem
 * Contains: Control information
 * Rd index
 * result of alu operation
 * Value (Rb??) in case it is a memory store instruction
 */

public class EX_MEM
{
   private Register register;
   private boolean busy;
   private int aluout;
   
   public EX_MEM(Register register, int aluout)
   {
      this.register = register;
      this.aluout = aluout;
      this.busy = true;
   }
   
   public Register getRegister()
   {
      return register;
   }
   
   public void setRegister(Register register)
   {
      this.register = register;
   }
   
   public boolean isBusy()
   {
      return busy;
   }
   
   public void setBusy(boolean busy)
   {
      this.busy = busy;
   }
   
   public int getAluout()
   {
      return aluout;
   }
   
   public void setAluout(int aluout)
   {
      this.aluout = aluout;
   }


   
   
}
