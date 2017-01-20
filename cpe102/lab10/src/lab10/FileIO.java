
import java.io.*;
import java.util.Scanner;


public class FileIO 
{
   public static void main(String[] args) 
   {
      File fl;
      PrintStream mystream;



      try 
      {
         mystream = new PrintStream("lab10file.txt");
         mystream.println("Mary had a little lamb");
         mystream.println("Its fleece was white as snow");
         mystream.println("And everywhere that Mary went");
         mystream.println("The lamb was sure to go!");

         mystream.close();


      } catch (FileNotFoundException e) 
      {

         e.printStackTrace();
      }


      try 
      {


         fl = new File("lab10file.txt");
         Scanner sc;
         sc = new Scanner (fl);
         while(sc.hasNextLine())
         {
            System.out.println(sc.nextLine());
         }

         sc.close();

      } 
      catch (FileNotFoundException e) 
      {

         e.printStackTrace();
      }









   }

}


