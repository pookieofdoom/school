import java.util.ArrayList;

public class ArrayListx
{
   private ArrayList<String> myList;
   private ArrayList<Integer> myList2;
   private ArrayList<Double> myList3;
   private ArrayList<Boolean> myList4;

   public ArrayListx() 
   {
      myList = new ArrayList<String>();
       myList2 = new ArrayList<Integer>();
       myList3 = new ArrayList<Double>();
       myList4 = new ArrayList<Boolean>();
   }
   
   public void add(int x)
   {
      myList2.add(x);
   }
   
   public void add(String x)
   {
      myList.add(x);
   }
   public void add(double x)
   {
      myList3.add(x);
   }
   public void add(boolean x)
   {
      myList4.add(x);
   }
   
   public int minimumInt()
   {
      int num, temp;
      if (myList2.isEmpty())
      {
         return 0;
      }
      num = myList2.size();
      temp = myList2.get(0);
      for(int i=0;i<num;i++)
      {
         if (myList2.get(i) < temp)
         {
            temp = myList2.get(i);
         }  
      }
      return temp;
   }  
   public double averageDouble()
   {
      int num;
      double temp = 0;
      if (myList3.isEmpty())
      {
         return 0;
      }

      num = myList3.size();
      for (int i=0; i<num; i++)
      {
         temp = temp + myList3.get(i);
      }
      return temp/num;
   }
      
   public int numberOfTrues()
   {
      int num = myList4.size();
      int x=0;
      if (myList4.isEmpty())
      {
         return 0;
      }

      
      for(int i =0; i<num;i++)
      {
        if(myList4.get(i))
        {
            x++;
        }
      }
      return x;
   }
  public int numberOfStrings()
  {
      return myList.size();
  }
  
  
    
  
       
         
   
   
}