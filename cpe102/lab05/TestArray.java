import java.util.Scanner;
public class TestArray
{
   public static void main(String[] args)
   {
      Scanner sc = new Scanner(System.in);
      ArrayListx list = new ArrayListx();
      
      boolean flag = true;
      
      
      while(flag == true) 
      {
         System.out.println("Enter in values");
         
         if(sc.hasNextInt())
         {
            list.add(sc.nextInt());
         }
         
         else if(sc.hasNextDouble())
         {
            list.add(sc.nextDouble());
         }
         else if(sc.hasNextBoolean())
         {
            list.add(sc.nextBoolean());
         }
         
         
         else if(sc.hasNext())
         {
            if(sc.next().equals("quit"))
            {
               flag = false;
            }
            else
            {
               list.add(sc.nextLine());
            }  
         }
      }
      System.out.println("The minimum int value: " +list.minimumInt());
      System.out.println("The average double value: " +list.averageDouble());
      System.out.println("The number of trues : " +list.numberOfTrues());
      System.out.println("The number of strings: " +list.numberOfStrings());
   }
}
         
      

         