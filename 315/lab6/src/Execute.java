/*Execute Cycle (EX)
 * Read ID/EX pipeline register to get values + control bits
 * Perform ALU operation
 * Compute targets(PC+4+offset, etc.) in case that this is a branch
 * Decide if jump/branch should be taken
 */

/*on a memory reference, add up base and offset
 on an arithmetic instruction, do the math*/


/*Might do
 * Make an ALUOP class that performs operation and spits output
 * Make register object have a instance variable and determine 
 * which R it is
 */

public class Execute
{
  
   public EX_MEM run(ID_EX id_ex_pipeline)
   {
	  int aluout;
	  Register reg_values = id_ex_pipeline.getRegister();
	  int pc = id_ex_pipeline.getPc();
	  
      if (reg_values instanceof R_Instruction) //check for nop later
      {
         System.out.println("R_Instruction");
         aluout = ((R_Instruction) reg_values).r_execute(pc);
      }
      else if (reg_values instanceof Jump_Instruction)
      {
         System.out.println("Jump_Instruction");
         aluout = ((Jump_Instruction) reg_values).j_execute(pc);
         
      }
      else //must be I
      {
         System.out.println("I_Instruction");
         aluout = ((I_Instruction) reg_values).i_execute(pc);
         
      }
      System.out.printf("VALUE IS %08X\n", aluout);
      
      return new EX_MEM(reg_values, aluout);
   }


}
