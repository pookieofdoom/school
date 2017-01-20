import java.io.*;
import java.util.*;
public class sup
{
   public static void main(String[] args) throws IOException
   {
      
      ArrayList<Object> poop = new ArrayList<Object>();
      poop = Lab14.read("file.bin");
      for(int i=0; i<poop.size();i++)
      {
         System.out.println(poop.get(i));
      }
     
      
      ArrayList<Object> hi = new ArrayList<Object>();
      hi.add(1);
      hi.add(69.69);
      hi.add(1);
      hi.add(14.4);
      hi.add(2);
      hi.add(14.1);
      hi.add(14.4);
 
      
      Lab14.write("poop.bin", hi);
      hi = Lab14.read("poop.bin");
      for(int i =0; i<hi.size();i++)
      {
         System.out.println(hi.get(i));
      }
   }
}
