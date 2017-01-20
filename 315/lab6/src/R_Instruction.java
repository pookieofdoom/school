
public class R_Instruction extends Register
{
   private long rd;
   private long shamt;
   private long funct;
   
   
   public R_Instruction(long reg_a, long reg_b, long opcode,
         long rd, long shamt, long funct)
   {
      super(reg_a, reg_b, opcode);
      this.rd = rd;
      this.shamt = shamt;
      this.funct = funct;
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
   
   
   public int r_execute(int pc)
   {
      //int rd = (int) this.rd;
      int rs = (int) this.reg_a;
      int rt = (int) this.reg_b;
      int output = 0;
      switch ((int) this.funct)
      {
         case 0x00: /* sll */
            output = rt << (int) this.shamt;
             
            break;

         case 0x02: /* srl */
            output = rt >>> (int) this.shamt;
            break;

         case 0x03: /* sra */
            output = rt >> (int) this.shamt;
            break;
            
         case 0x04: /*sllv*/
            output = rt << rs;   
            break;

         case 0x06: /* srlv */
            output = rt >>> rs; 
            break;

         case 0x07: /* srav */
            output = rt >> rs;
            break;
            
         case 0x08: /*jr*/
            output = rs;
            break;
         case 0x09: /*jal*/
            output = pc + 4;
            //pc = rs;
            break;
         
//         case 0x0C: /*syscall*/
//            if (register[2] == 10)
//            {
//               System.out.println("End of Program");
//               System.out.printf("%d instructions simulated\t%d mem references\t%d "
//                     + "clock cycles expended\n", num_instr, num_mem, num_clock);
//               System.exit(0);
//            }
//            break;
           
         case 0x20: /* add */
            output = rs + rt;
            break;
         
         case 0x21: /*addu*/
            /*this might be wrong.. overflow??*/
            output = rs + rt;
            break;
            
         case 0x22: /* sub */
            output = rs - rt;
            break;
            
         case 0x23: /*subu*/
            output = rs - rt;
            break;
            
         case 0x24: /*and*/
            output = rs & rt;
            break;
            
         case 0x25: /* or*/
            output = rs | rt;
            break;
            
         case 0x26: /*xor*/
            output = rs ^ rt;
            break;
            
         case 0x27: /*nor*/
            output = ~(rs | rt);
            break;
            
         case 0x2A: /*slt*/
            output = (rs < rt) ? 1 : 0;
            break;
            
         case 0x2B: /*sltu*/
            output = (rs < rt) ? 1 : 0;  
            break;
            
      }
      return output;
      
   }
   
   public static final String[] func_lookup = { "Logical Shift Left", "Not Available", "Logical Shift Right",
         "Shift Right Arithmetic", "Shift Left Logical Var.", "Not Available", "Shift Right Logical Var.",
         "Shift Right Arithmetic Var.", "Jump Register", "Jump And Link Register", "Not Available", "Not Available",
         "Syscall", "Not Available", "Not Available", "Not Available", "Move From HI", "Not Available", "Move From LO",
         "Not Available", "Not Available", "Not Available", "Not Available", "Not Available", "Multiply",
         "Multiply Unsigned", "Divide", "Divide Unsigned", "Not Available", "Not Available", "Not Available",
         "Not Available", "Add", "Add Unsigned", "Subtract", "Subtract Unsigned", "And", "Or", "Xor", "Nor",
         "Not Available", "Not Available", "Set Less Than", "Set Less Than Unsigned" };

   
}