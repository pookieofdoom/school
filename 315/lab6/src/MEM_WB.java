/*Basket between Mem and WB
 * Contains: Control information
 * Rd index,...
 * Result of memory operation
 * result of ALU operation
 */

public class MEM_WB
{
   private Register register;
   private int mem_data;
   private int alu_out;
   private boolean busy;
   
   public MEM_WB(Register register, int mem_data, int alu_out)
   {
      this.register = register;
      this.mem_data = mem_data;
      this.alu_out = alu_out;
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
   
   public int getMem_data()
   {
      return mem_data;
   }
   
   public void setMem_data(int mem_data)
   {
      this.mem_data = mem_data;
   }
   
   public boolean isBusy()
   {
      return busy;
   }
   
   public void setBusy(boolean busy)
   {
      this.busy = busy;
   }
   
   public int getAlu_out()
   {
      return alu_out;
   }
   
   public void setAlu_out(int alu_out)
   {
      this.alu_out = alu_out;
   }
   

}
