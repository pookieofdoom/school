//http://www.cs.cornell.edu/courses/cs3410/2012sp/lecture/09-pipelined-cpu-i-g.pdf
//https://www.cs.cmu.edu/afs/cs/academic/class/15740-f97/public/info/pipeline-slide.pdf
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;
import java.nio.file.Path;

public class PipeLine 
{
   
   public static void main(String[] args)
   {
       long opcode = 0;
       long instruction = 0;
       int aluout = 0;
       System.out.print("Enter .mb filename: ");
       Scanner in = new Scanner(System.in);
       //String filename = "C:/Users/pooki/workspace/lab6/src/countbits_benchmark.mb";
       //String filename = in.nextLine();
       //String filename = "C:/Users/pooki/workspace/lab6/src/countbits_benchmark.mb";
       String filename = "C:/Users/tomto_000/Desktop/anthony/lab6/src/countbits_benchmark.mb";
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
       Register reg_values = null;
   
   
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
       
       Fetch fetch = new Fetch(mem, pc, memp);
       Decode decode = new Decode();
       Execute execute = new Execute();
       Mem memory = new Mem();
       WriteBack write_back = new WriteBack();
       while (fetch.getPc() < memp)
       {
          System.out.println(fetch.getPc());
           
          if (fetch.check_out(decode))
          {
             instruction = fetch.run();
          }
          
          if (fetch.isBusy() && !execute.isBusy()) //and execute not busy
          {
             decode.setInstruction_register(instruction);
             reg_values = decode.run(register);
             System.out.println(reg_values);
             fetch.setBusy(false);
          }
          
          if (decode.isBusy() && !memory.isBusy())
          {
        	  //aluout might be a long
             aluout = execute.run(reg_values, fetch.getPc());
             decode.setBusy(false);
          }
          
          if (execute.isBusy() && !write_back.isBusy())
          {
        	  memory.setBusy(true);
          }
          
          if (memory.isBusy())
          {
        	  write_back.run(reg_values, aluout);
          }

          
          System.out.printf("%08X\n", instruction);
       }
   }



   public static long byteAsULong(byte b)
   {
      return ((long) b) & 0x00000000000000FFL;
   }
}