
/**
 * 
 * @author Anthony Dinh
 * @version Lab Quiz 3
 */

import java.io.*;
import java.util.*;

public class Box 
{
   private double length, width, height, weight;

   public Box(double length, double width, double height, double weight)
   {
      this.length = length;
      this.width = width;
      this.height = height;
      this.weight = weight;

   }

   public double getLength()
   {
      return this.length;
   }

   public double getWidth()
   {
      return this.width;
   }

   public double getHeight()
   {
      return this.height;
   }

   public double getWeight()
   {
      return this.weight;
   }

   public double getVolume()
   {
      return this.length * this.width * this.height;
   }

   public double getMaxDimension()
   {
      if(this.length> this.width && this.length > this.height)
      {
         return this.length;
      }

      if(this.width > this.length && this.width > this.height)
      {
         return this.width;
      }

      else
      {
         return this.height;
      }
   }

   public boolean equals(Object obj)
   {

      if(!(obj instanceof Box) )
      {
         return false;
      }
      if(this.height != ((Box)obj).height)
      {
         return false;
      }
      if(this.width != ((Box) obj).getWidth())
      {
         return false;

      }

      if(this.length != ((Box)obj).getLength())
      {
         return false;
      }

      if(this.weight != ((Box)obj).getWeight())
      {
         return false;
      }

      if(getVolume() != ((Box)obj).getVolume())
      {
         return false;
      }

      return true;
   }

   public static void write(String fileName, ArrayList<Box> list) throws FileNotFoundException, IOException
   {
      FileOutputStream a = new FileOutputStream(fileName);
      DataOutputStream b = new DataOutputStream(a);
      int i;

      for(i=0; i<list.size();i++)
      {
         
            if(list.get(i) instanceof Box)
            {
               b.writeDouble(list.get(i).getLength());
               b.writeDouble(list.get(i).getWidth());
               b.writeDouble(list.get(i).getHeight());
               b.writeDouble(list.get(i).getWeight());
            }
         
      }

   }

   public static ArrayList<Box> read(String fileName) throws FileNotFoundException, IOException
   {
      FileInputStream a = new FileInputStream (fileName);
      DataInputStream b = new DataInputStream(a);
      ArrayList<Box> c = new ArrayList<Box>();
      double length,width,height,weight;

      while(true)
      {
         try
         {

            length = b.readDouble();
            width = b.readDouble();
            height = b.readDouble();
            weight = b.readDouble();
            Box d = new Box(length, width, height, weight);
            c.add(d);
         }
         catch(EOFException e)
         {
            return c;
         }
      }
   }

}
