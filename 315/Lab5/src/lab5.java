import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;
import java.nio.file.Path;

public class lab5
{
   public static final int R = 0;
   public static final int I = 1;
   public static final int J = 2;
   public static final int NOT_VALID = 3;
   public static int num_instr = 0;
   public static int num_mem = 0;
   public static int num_clock = 0;

   public static void main(String[] args)
   {
      long opcode = 0;
      System.out.print("Enter .mb filename: ");
      Scanner in = new Scanner(System.in);
      //String filename = "C:/Users/pooki/workspace/Lab5/src/diagnostics.mb";
      String filename = in.nextLine();
      /*check if file exist*/
      try
      {
         in = new Scanner(new File(filename));
      }
      catch (FileNotFoundException e)
      {
         System.out.println("No such file exist! Bye");
         System.exit(0);
      }
      /* given code that reads file and takes out the instructions into an array*/
      Path path = Paths.get(filename);
      long mem[] = new long[1024];
      int memp = 0;
      int fd;
      byte[] data = null;
      String input = null;
      int pc = 0;
      int[] register = new int[32];
      long[] mem_reg = new long[1024];
      


      if (args.length > 0)
      {
         for (int i = 0; i < args.length; i++)
         {
            if (args[i].equals("-d"))
            {
               System.out.println("Debug Mode");
               input = "Debug";
            }
         }

      }

      try
      {
         data = Files.readAllBytes(path);
      }
      catch (IOException e)
      {
         // TODO Auto-generated catch block
         e.printStackTrace();
      }
      mb_hdr hdr = new mb_hdr();

      for (int i = 0; i < 4; i++)
      {
         hdr.signature[i] = (char) data[i];
      }

      hdr.size = data[4];
      hdr.entry = data[8];
      pc = (int) hdr.entry;
      hdr.filler1 = data[12];
      for (int i = 16; i < 64; i++)
      {
         hdr.filler2[i - 16] = (char) data[i];
      }

      if (!String.valueOf(hdr.signature).equals("~MB\0"))
      {
         System.out.println("\nThis isn't really a mips_asm binary file - quitting.\n");
         return;
      }
      System.out.format("\n%s Loaded ok, program size=%d bytes.\n\n", filename, hdr.size);

      fd = 64;
      do
      {
         mem[memp / 4] = byteAsULong(data[fd]) | (byteAsULong(data[fd + 1]) << 8) | (byteAsULong(data[fd + 2]) << 16)
               | (byteAsULong(data[fd + 3]) << 24);
         fd += 4;
         memp += 4;

      }
      while (memp < 1024 && fd < data.length);

      /*--------------------start of my actual code ----------*/
     
      /*storing any defines*/
      for (int i = 0; i < pc; i += 4)
      {
         mem_reg[i] = mem[i / 4];
      }

      /*check user input for certain instructions*/
      Scanner reader = new Scanner(System.in);
      System.out.println("Enter command: "
            + "(s for step, d for debug, f for forward, r for run, e for exit");
      while (pc < memp)
      {
     
         opcode = (mem[pc / 4] >> 26) & 0x3F;
         if (input != null && input.equals("d"))
         {
            DecodeUtil.add_instruction(pc, opcode, pc, mem[pc / 4]);
            pc +=4;
         }
         else
         {
            input = reader.nextLine();
            if (input.equals("s"))
            {
               pc = step(pc, opcode, mem[pc / 4], register, mem_reg);

            }
            else if (input.equals("f"))
            {
               int fpc = 0;
               boolean valid = false;
               
               while (!valid)
               {
                  System.out.print("Forward to pc: ");
                  if(reader.hasNextInt(16))
                  {
                     fpc = reader.nextInt(16);
                     if (fpc % 4 != 0 || fpc < pc)
                        System.out.println("Invalid PC, try again");
                     else
                        valid = true;
                  }
                  else
                  {
                     System.out.println("Invalid PC, try again");
                  }
               }
               
               while (fpc > memp)
               {
                  System.out.println("Invalid PC, try again");
                  System.out.print("Forward to pc: ");
                  fpc = reader.nextInt(16);
               }
               while(pc <= fpc)
               {
                  opcode = (mem[pc / 4] >> 26) & 0x3F;
                  pc = step(pc, opcode, mem[pc / 4], register, mem_reg);
               }
                  
            }
            else if (input.equals("r"))
            {
               System.out.println("Running all");
               while (pc < memp)
               {
                  opcode = (mem[pc / 4] >> 26) & 0x3F;
                  pc = step(pc, opcode, mem[pc / 4], register, mem_reg);
               }
            }
            else if(input.equals("e"))
            {
               System.out.println("Quitting! Bye!!");
               System.exit(0);
            }
            System.out.println();
            System.out.println("Enter command: "
                  + "(s for step, d for debug, f for forward, r for run, e for exit");
         }
         
      }
      reader.close();
   }

   public static void print_registers(int pc, int[] register)
   {
      System.out.printf("\nPC: %08X                ", pc);
      for (int i = 0; i < 32; i++)
      {
         System.out.printf("%s: %08X        ", DecodeUtil.reg_lookup[i], register[i]);
         if (i % 4 == 0)
         {
            System.out.println();
         }
      }
      System.out.println();
   }



   public static int step(int pc, long opcode, long instruction, int[] register, long[] mem_reg)
   {
      int type = DecodeUtil.check_op(opcode);
      R_Instruction r_instr = new R_Instruction();
      I_Instruction i_instr = new I_Instruction();
      Jump_Instruction j_instr = new Jump_Instruction();
      print_registers(pc, register);
      num_instr++;
      if (type == R)
      {
         decode_r(r_instr, opcode, instruction);

         if (!DecodeUtil.check_nop(r_instr))
         {
            num_clock+=2;
            System.out.println("No op");
            System.out.printf("%d instructions simulated\t%d mem references\t%d "
                  + "clock cycles expended\n", num_instr, num_mem, num_clock);
            return pc + 4;
         }
         num_clock+=4;
         pc = DecodeUtil.r_execute(r_instr, pc, register, num_instr, num_mem, num_clock);

      }
      else if (type == I)
      {
         decode_i(i_instr, opcode, instruction);
         pc = DecodeUtil.i_execute(i_instr, instruction, pc, register, mem_reg);
         /*Branch*/
         if (opcode == 0x04 || opcode == 0x05)
         {
            num_clock +=3;
         }
         /*Load*/
         else if (opcode == 0x20 || opcode == 0x21 || opcode == 0x23
               || opcode == 0x24 || opcode == 0x25)
         {
            num_clock +=5;
            num_mem += 1;
         }
         else if (opcode == 0x28 || opcode == 0x29 || opcode == 0x2B)
         {
            num_clock +=4;
            num_mem +=1;
         }
         else
         {
            num_clock +=4;
         }
      }
      else if (type == J)
      {
         decode_j(j_instr, opcode, instruction);
         pc = DecodeUtil.j_execute(j_instr, pc, register);
         num_clock +=3;
      }
     
      System.out.printf("%d instructions simulated\t%d mem references\t%d "
            + "clock cycles expended\n", num_instr, num_mem, num_clock);
      return pc;

   }

   private static void decode_j(Jump_Instruction j_instr, long opcode, long instr)
   { 
      j_instr.setOpcode(opcode);
      j_instr.setIndex(instr & 0x3FFFFFF);
      System.out.printf("%s   0x%08X\n", 
            DecodeUtil.op_lookup[(int) j_instr.getOpcode()],
            j_instr.getIndex());
   }

   private static void decode_i(I_Instruction i_instr, long opcode, long instr)
   {
      i_instr.setOpcode(opcode);
      i_instr.setRs((instr >> 21) & 0x1F);
      i_instr.setRt((instr >> 16) & 0x1F);
      i_instr.setImmed(instr & 0xFFFF);

      System.out.printf("%s   %s, %s, 0x%04X\n", 
            DecodeUtil.op_lookup[(int) i_instr.getOpcode()],
            DecodeUtil.reg_lookup[(int) i_instr.getRt()], 
            DecodeUtil.reg_lookup[(int) i_instr.getRs()], 
            i_instr.getImmed());
   }

   private static void decode_r(R_Instruction r_instr, long opcode, long instr)
   {
      r_instr.setOpcode(opcode);
      r_instr.setRs((instr >> 21) & 0x1F);
      r_instr.setRt((instr >> 16) & 0x1F);
      r_instr.setRd((instr >> 11) & 0x1F);
      r_instr.setShamt((instr >> 6) & 0x1F);
      r_instr.setFunct(instr & 0x3F);
      int func = (int) r_instr.getFunct();
      if (DecodeUtil.check_nop(r_instr) == true)
      {
         if (func != 0x00 && func != 0x02 && func != 0x03)
         {
            if (func == 0x04 || func == 0x06 || func == 0x07)
            {
               System.out.printf("%s   %s, %s, %s\n", 
                     DecodeUtil.func_lookup[(int) r_instr.getFunct()],
                     DecodeUtil.reg_lookup[(int) r_instr.getRd()], 
                     DecodeUtil.reg_lookup[(int) r_instr.getRt()],
                     DecodeUtil.reg_lookup[(int) r_instr.getRs()]);
            }
            else if (func == 0x08 || func ==0x09)
            {
               System.out.printf("%s   %s\n", 
                     DecodeUtil.func_lookup[(int) r_instr.getOpcode()],
                     DecodeUtil.reg_lookup[(int) r_instr.getRs()]);
            }
            else
            {
               System.out.printf("%s   %s, %s, %s\n", 
                     DecodeUtil.func_lookup[(int) r_instr.getFunct()],
                     DecodeUtil.reg_lookup[(int) r_instr.getRd()], 
                     DecodeUtil.reg_lookup[(int) r_instr.getRs()],
                     DecodeUtil.reg_lookup[(int) r_instr.getRt()]);
            }

         }

         else
         {
            System.out.printf("%s   %s, %s, %d\n", 
                  DecodeUtil.func_lookup[(int) r_instr.getFunct()], 
                  DecodeUtil.reg_lookup[(int) r_instr.getRd()], 
                  DecodeUtil.reg_lookup[(int) r_instr.getRt()], (int) r_instr.getShamt());
         }

      }

   }

   

   public static long byteAsULong(byte b)
   {
      return ((long) b) & 0x00000000000000FFL;
   }



}
