/*Memory Cycle (MEM
 * Read EX/MEM pipeline register to get values and control bits
 * Perform memory load/store if needed
 * (address = ALU result)
 */

/*
 * If load or store, access memory
 * If branch, replace PC with destination address (flush if branch taken)
 * Otherwise, do nothing
 * 
 */

public class Mem 
{
	
   public void run(EX_MEM ex_mem_pipeline)
   {
      Register reg_values = ex_mem_pipeline.getRegister();
      /*do the load and store operations manually in this file*/
      
   }
	
}
