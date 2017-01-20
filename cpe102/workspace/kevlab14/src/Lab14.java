import java.io.*;
import java.util.ArrayList;
public class Lab14
{
   public static ArrayList<Object> read(String fileName) throws FileNotFoundException, IOException
   {
      DataInputStream a = new DataInputStream(new FileInputStream (fileName));
      ArrayList<Object> b = new ArrayList<Object>();

      try
      {
         while(true)
         {
            int num = a.readInt();
            b.add((Integer)num);
            for(int i=0; i<num;i++)
            {
               b.add((Double)a.readDouble());
            }
         }
      }
      catch(EOFException e)
      {
         return b;
      }
   }

   public static void write(String fileName, ArrayList<Object> list) throws FileNotFoundException, IOException
   {
      DataOutputStream c = new DataOutputStream(new FileOutputStream(fileName));
      int j,i=0;
      
      for(i=0; i<list.size();i++)
      {
         if(list.get(i) instanceof Integer)
         {
            int temp = (Integer) list.get(i);
            c.writeInt(temp);

            for(j=i+1; j<temp +i +1;j++)
            {
               if(list.get(j) instanceof Double)
               {
                  
                  c.writeDouble((Double)list.get(j));
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

   }
}