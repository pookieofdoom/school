/*this is the connection basket between
 * IF and ID cycles
 * values of interest: 
 * instructions bits (for decoding)
 * PC + 4 (for later computing branch targets)
 */
public class IF_ID
{
   private long instruction;
   private int pc;
   private boolean busy;
   
   public IF_ID(long instruction, int pc)
   {
      this.instruction = instruction;
      this.pc = pc;
      this.busy = true;
   }
   
   public long getInstruction()
   {
      return instruction;
   }
   
   public void setInstruction(long instruction)
   {
      this.instruction = instruction;
   }
   
   public int getPc()
   {
      return pc;
   }
   
   public void setPc(int pc)
   {
      this.pc = pc;
   }

   public boolean isBusy()
   {
      return busy;
   }

   public void setBusy(boolean busy)
   {
      this.busy = busy;
   }
   
}
