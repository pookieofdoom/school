/**
 * Provided basic compile test for Box quiz. 
 *
 * Verifies that all expected methods are present and that they potentially
 * throw the expected exceptions.
 *
 * ************************************************************************
 * *** NOTE THAT THIS IS A COMPILE TEST ONLY - NO BEHAVIOR IS VERIFIED! ***
 * ************************************************************************
 *
 * @author Kurt Mammen
 * @version CPE 102 Lab Quiz 3
 */
import java.io.*;
import java.util.*;

public class BoxCompileVerification
{
   public static void main(String[] args)
   {
      System.out.print("*\n* NOTE: BoxCompileVerification DOES NOT verify functionality\n");
      System.out.print("*       That is for you to do during the quiz!\n*\n");
      double d;
      boolean b;
      Box box = new Box(1.1, 2.2, 3.3, 4.4);

      d = box.getLength();
      d = box.getWidth();
      d = box.getHeight();
      d = box.getWeight();
      d = box.getVolume();
      d = box.getMaxDimension();
      b = box.equals(new Object());
      ArrayList<Box> hi = new ArrayList<Box>();
      hi.add(box);
      try
      {
         Box.write("SomeFile", hi);
         
      }
      catch(FileNotFoundException e)
      {
      }
      catch(IOException e)
      {
      }
      
      try
      {
         hi = Box.read("SomeFile");
         for(int i=0; i<hi.size();i++)
         {
            System.out.println(hi.get(i).getWeight());
         }
      }
      catch(FileNotFoundException e)
      {
      }
      catch(EOFException e)
      {
      }
      catch(IOException e)
      {
      }
   }
}
