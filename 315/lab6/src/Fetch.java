
/* Fetch Cycle (IF)
 * Fetch a new instruction every cycle
 *  Current PC is index to instruction memory
 *  Increment the PC at the end of cycle(assume no branches for now)
 */

public class Fetch
{
   private int pc;
   private long mem[];
   private int memp;
   
   public Fetch(long mem[], int pc, int memp)
   {
      this.mem = mem;
      this.pc = pc;
      this.memp = memp;
   }

   
   public IF_ID run()
   {
      
      long instruction = 0;
      if (this.pc < this.memp)
      {
         instruction = mem[pc / 4];
      }
      this.pc += 4;
      return new IF_ID(instruction, this.pc);
   }


}
