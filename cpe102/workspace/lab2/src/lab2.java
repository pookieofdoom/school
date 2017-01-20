import java.util.Scanner;


public class lab2 
{
   public static void main(String[] args)
   {
      final int n = 5;
      int[] integers = new int[n];
      float[] floats = new float[n];
      int sizeint = 0;
      int sizefloat =0;
     
      Scanner scanner = new Scanner(System.in);
      System.out.println("Enter values");
      while (scanner.hasNext())
      {
         if(scanner.hasNextInt())
         {
            if(sizeint != n)
            {
               integers[sizeint] = scanner.nextInt();
               sizeint++;
            }
            else
            {
                  break;
             
            }
         }
         else if (scanner.hasNextFloat())
         {
            if(sizefloat != n)
            {
               floats[sizefloat] = scanner.nextFloat();
               sizefloat++;
            }
            else
            {
              break;
            }
         }
         else
         {
            break;
         }
         
      }
      
      System.out.print("Integers: ");
      for (int i=0; i<sizeint;i++)
      {
         System.out.print(integers[i] + " ");
      }
      System.out.println("");
      System.out.print("Floats: ");
      for (int i=0; i< sizefloat; i++)
      {
         System.out.print(floats[i] + " ");
         
      }
      System.out.println("");
      
   }

}
