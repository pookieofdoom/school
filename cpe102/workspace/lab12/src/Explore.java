import java.util.*;
class Explore 
{
   public static void main(String[] args)
   {
      LinkedList<String> a = new LinkedList<String>();
      LinkedList<Integer> b = new LinkedList<Integer>();
      

      a.add("sup");
      a.add("dsadsa");
      a.add("djaodjas");
      a.add("herro");
      a.add("WHY");

      b.add(5);
      b.add(13);
      b.add(14);
      b.add(69);
      b.add(1337);
      b.add(6969);
      
      Iterator<String> it = a.iterator();
      while(it.hasNext())
      {
         String s = it.next();
         System.out.println(s);
         
      }
      
      for(Integer d : b)
      {
         System.out.println(d);
      }
      
   }





}
