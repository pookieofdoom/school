import java.util.ArrayList;

public class ArrayListx
{
   private ArrayList<Object> myList;

   public ArrayListx() 
   {
      myList = new ArrayList<Object>();

   }
   
   public void add(Object x)
   {
      myList.add(x);
   }
   
   public Integer minimumInt()
   {
      int num;
      Integer temp = null;
      if (myList.isEmpty())
      {
         temp = 0;
         return (Integer) temp;
      }
      num = myList.size();
      
      for(int i=0;i<num;i++)
      {
         if (myList.get(i) instanceof Integer)
         {
            if(temp == null) {
               temp = (Integer) myList.get(i);
            }
            else if ((Integer)myList.get(i) < (Integer)temp)
            {
               temp = (Integer) myList.get(i);
            }
         }  
      }
      
      return (Integer) temp;
     
   }  
   public Double averageDouble()
   {
      int num;
      Double temp = 0.0;
      if (myList.isEmpty())
      {
         return 0.0;
      }

      num = myList.size();
      for (int i=0; i<num; i++)
      {
         if (myList.get(i) instanceof Double)
         {
            temp = temp + (Double) myList.get(i);  
         }
      }
      
      return temp/ num;  
   }
      
   public int numberOfTrues()
   {
      int num = myList.size();
      int x=0;
      if (myList.isEmpty())
      {
         return 0;
      }

      
      for(int i =0; i<num;i++)
      {
        if(myList.get(i) instanceof Boolean)
        {
            x++;
        }
      }
      return x;
   }
  public Object numberOfStrings()
  {
      return (Integer)myList.size();
  }
  
  
    
  
       
         
   
   
}