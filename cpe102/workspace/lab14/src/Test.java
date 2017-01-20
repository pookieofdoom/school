import java.io.*;
import java.util.*;
public class Test 
{
   public static void main(String[] args) throws IOException
   {
      
      ArrayList<Object> poop = new ArrayList<Object>();
      poop = BinaryIO.read("file.bin");
      for(int i=0; i<poop.size();i++)
      {
         System.out.println(poop.get(i));
      }
     
      
      File x = new File("poop.bin");
      ArrayList<Object> hi = new ArrayList<Object>();
      hi.add(2);
      hi.add(69.9);
      
      
 
      
      BinaryIO.write("poop.bin", hi);
      hi = BinaryIO.read("poop.bin");
      for(int i =0; i<hi.size();i++)
      {
         System.out.println(hi.get(i));
      }
   }
}
