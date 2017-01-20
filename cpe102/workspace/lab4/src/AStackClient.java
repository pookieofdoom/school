import java.io.*;
import java.util.*;

public class AStackClient 
{
   public static void main(String[] arg)
   {
      File file = null;
      Scanner scanner = new Scanner(System.in);
      
      AStack<Integer> intStack = new AStack<Integer>(5);
      AStack<Float> floatStack = new AStack<Float>(5);
      AStack<String> stringStack = new AStack<String>(5);
      
      System.out.print("Enter file name: ");
      try
      {
         file = new File(scanner.next());
         scanner = new Scanner(file);
         
         while(scanner.hasNext())
         {
            if(scanner.hasNextInt())
            {
               intStack.push(scanner.nextInt());
            }
            else if(scanner.hasNextFloat())
            {
               floatStack.push(scanner.nextFloat());
            }
            else
            {
               stringStack.push(scanner.next());
            }
         }
      }
      catch(FileNotFoundException e)
      {
         System.out.println("File not found");
      }
      finally
      {
         scanner.close();
      }
      
      System.out.print("Strings: ");
      while(!stringStack.isEmpty())
      {
         String pop = stringStack.pop();
         System.out.print(pop + " ");
      }
      System.out.print("\n");
      
      System.out.print("Floats: ");
      while(!floatStack.isEmpty())
      {
         float pop = floatStack.pop();
         System.out.print(pop + " ");
      }
      System.out.print("\n");
      
      System.out.print("Integers: ");
      while(!intStack.isEmpty())
      {
         int pop = intStack.pop();
         System.out.print(pop + " ");
      }
      System.out.print("\n");
   }
}
