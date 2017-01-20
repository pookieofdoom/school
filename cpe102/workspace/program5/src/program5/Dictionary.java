package program5;

import java.io.*;
import java.util.*;
import java.lang.String;


public class Dictionary implements Iterable<String>
{
   private ArrayList<String> mylist;

   public Dictionary(String fileName, boolean sort) throws DictionaryException 
   {
      Scanner sc;
      try 
      {
         File x = new File (fileName);
         if(sort)
         {

            sc = new Scanner (x);
   
            while(sc.hasNextLine())
            {
               this.mylist.add(sc.nextLine());
            }

            for (int i = 0; i < mylist.size() - 1; i++)
            {
               int minPos = minimumPosition(i);
               swap(minPos, i);
            }
         }


      }
      catch (FileNotFoundException e) 
      {
         System.out.println("SUP");
         e.printStackTrace();
      }

   }

   public java.util.Iterator<String> iterator()
   {    
      return mylist.iterator();
   }


   public boolean lookUp(String word)
   {
      int lo = 0;
      int hi = mylist.size() - 1;

      while (lo <= hi)
      {
         int mid = (lo + hi) / 2;

         if (word.compareTo(mylist.get(mid)) < 0)
         {
            hi = mid - 1;
         }
         else if (word.compareTo(mylist.get(mid)) > 0)
         {
            lo = mid + 1;
         }
         else
         {
            return true;
         }
      }

      return false;
   }

   public void write(String fileName) throws DictionaryException 
   {
      PrintStream mystream; 
      try 
      {
         mystream = new PrintStream(fileName);
         for(int i=0; i < mylist.size(); i++)
         {
            mystream.println(mylist.get(i));
         }
      } 

      catch (FileNotFoundException e) 
      {
         e.printStackTrace();
      }

   }



   private int minimumPosition(int from)
   {
      int minPos = from;

      for (int i = from + 1; i < mylist.size(); i++)
      {
         if (mylist.get(i).compareTo( mylist.get(minPos)) < 0)
         {
            minPos = i;
         }
      }

      return minPos;
   }

   private void swap(int i, int j)
   {
      String temp = mylist.get(i);
      mylist.set(i,mylist.get(j));
      mylist.set(j,temp);
   }



}
