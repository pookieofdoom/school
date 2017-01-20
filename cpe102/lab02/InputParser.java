 /**
           * My coding for InputParser
           *
           * Anthony Dinh
           * Lab 02 Part 2
*/

import java.util.Scanner;

public class InputParser
{
   public static void main(String[] args)
   {
      Scanner scanner = new Scanner(System.in);
      scanner.useDelimiter("\n");
      System.out.print("Enter the number of values you want to parse? ");
     
      int i;
      int count1 = 0, count2 = 0, count3 = 0;
      int sum1 = 0;  
      double sum2 = 0;
      String cat = "";
      while(!scanner.hasNextInt())
      {
         scanner.next();
         System.out.print("Not valid, please reenter the number of values you want to parse ");
      }
      
       i = scanner.nextInt();  
      
      System.out.println("Please enter in " + i + " values ");      
      for(int j = 0; j < i; j++)
      {
         if(scanner.hasNextInt())
         {
            count1++;
            sum1 = sum1 + scanner.nextInt();
         }
         else if(scanner.hasNextDouble())
         {
            count2++;
            sum2 = sum2 + scanner.nextDouble();
         }
         else
         {
            count3++;
            cat = cat + " " + scanner.next();
         }
      }
      System.out.println("A total of " + count1 + " integer(s) with a sum " + sum1);
      System.out.println("A total of " + count2 + " double(s) with a sum " + sum2);                          
      System.out.println("A total of " + count3 + " string value(s) with the concatenation of " + cat);
   }
}     