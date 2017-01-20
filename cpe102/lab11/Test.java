
import java.io.*;
import java.util.*;

public class Test 
{
   public static void main(String[] args) 
   {
      File x = new File ("randomWords.txt");
      ArrayList<String> poop = new ArrayList<String>(); 

      Scanner sc;
      try 
      {
         sc = new Scanner (x);



         while(sc.hasNextLine())
         {
            poop.add(sc.nextLine());
         }

         SelectionSorter hi = new SelectionSorter(poop);
         hi.sort();


         for(int i = 0; i < poop.size(); i++)
         {
            System.out.println(poop.get(i));
         }
         BinarySearcher pee = new BinarySearcher(poop); 
         System.out.println(pee.search("IMPEDES"));
      }
      catch (FileNotFoundException e) 
      {
         e.printStackTrace();
      }

   }


}
