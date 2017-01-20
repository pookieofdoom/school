import java.util.*;

public class SeparateAndMerge 
{
   public static void main(String[] args)
   {
      LList<Integer> listint = new LList<Integer>();
      LList<Float> listFloat = new LList<Float>();
      
      Scanner sc = new Scanner(System.in);
      
      while(sc.hasNext())
      {
         if(sc.hasNextInt())
         {
            listint.add(sc.nextInt());
            
         }
         else if(sc.hasNextFloat())
         {
            listFloat.add(sc.nextFloat());
         }
         else
         {
            sc.next();
         }
      }
      
      Iterator<Integer> intIter = listint.iterator();
      Iterator<Float> floatIter = listFloat.iterator();
      
      System.out.print("\nInputted values: ");
      
      while(intIter.hasNext() || floatIter.hasNext())
      {
         if(intIter.hasNext())
         {
            System.out.print(intIter.next() + " ");
         }
         if(floatIter.hasNext())
         {
            System.out.print(floatIter.next() + " ");
         }
      }
      System.out.println("");
   }
}
