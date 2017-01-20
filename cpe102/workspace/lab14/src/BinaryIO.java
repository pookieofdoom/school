import java.io.*;
import java.util.ArrayList;

public class BinaryIO 
{


   public static ArrayList<Object> read(String fileName) throws IOException
   {
      ArrayList<Object> c = new ArrayList<Object>();

      FileInputStream a = new FileInputStream(fileName);
      DataInputStream b = new DataInputStream(a);
      while(true)
      {
         try
         {
            int temp = b.readInt();
            c.add((Integer)temp);
            for(int i =0; i < temp;i++)
            {
               c.add((Double)b.readDouble());
            }

         }

         catch (EOFException e)
         {
            return c;
         }
      }
   }


   public static void write(String fileName, ArrayList<Object> list) throws FileNotFoundException, IOException
   {
      FileOutputStream a = new FileOutputStream(fileName);
      DataOutputStream b = new DataOutputStream(a);
      int temp;
      int i,j;
      for(i=0; i<list.size(); i++)
      {
         try
         {

            if(list.get(i) instanceof Integer)
            {
               temp = ((Integer)list.get(i));
               b.writeInt(temp);



               for(j = i+1; j < temp + i + 1; j++)
               {
                  if(list.get(j) instanceof Double)
                  {
                     b.writeDouble((Double)list.get(j));
                  }
                  else
                  {

                     throw new IllegalArgumentException();
                  }
               }
               i = j-1;
            }
            else
            {
               throw new IllegalArgumentException();
            }
            
         }
         catch(IndexOutOfBoundsException e)
         {
            throw new IllegalArgumentException();
         }
         
         catch(EOFException e)
         {
            throw new IllegalArgumentException();
         }
      }


   }


}



