/*Basket between ID and EX
 * contains control information
 * Rd index, immediates, offsets,..
 * contents of Ra, Rb
 * PC+4(for computing branch targets later)
 */
public class ID_EX
{
   private boolean busy;
   private Register register;
   private int pc;
   
   public ID_EX(Register register, int pc)
   {
      this.register = register;
      this.pc = pc;
      this.busy = true;
   }
   
   public void setRegister(Register register)
   {
      this.register = register;
   }
   
   public Register getRegister()
   {
      return register;
   }

   public boolean isBusy()
   {
      return busy;
   }

   public void setBusy(boolean busy)
   {
      this.busy = busy;
   }

   public int getPc()
   {
      return pc;
   }

   public void setPc(int pc)
   {
      this.pc = pc;
   }   
}
