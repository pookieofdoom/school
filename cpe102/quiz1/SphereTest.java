public class SphereTest
{
   public static void testGetRadius()
   {
      Sphere s = new Sphere(5);
      if(s.getRadius() == 5.0)
      {
         System.out.println("" +s.getRadius());
         System.out.println("snap it works");
      }
   }
   
   public static void defaultSphere()
   {
      Sphere s = new Sphere();
      if(s.getRadius() == 1.0)
      {
         System.out.println("default sphere works..");
      }
   }
   
   public static void testSetRadius()
   {
      Sphere s = new Sphere(15.1);
      s.setRadius(69.69);
      if(s.getRadius() == 69.69)
      {
         System.out.println("that 69!");
      }
   }
   
   public static void testSurfaceArea()
   {
      Sphere s = new Sphere (1);
      if(s.getSurfaceArea() != 59971.6136)
      {
         System.out.println("dude its.." +s.getSurfaceArea());
      } 
      if (s.getVolume() != 4.2)
      {
         System.out.println("volume is..." +s.getVolume());
      }
   }
   
   public static void testequals()
   {
      Sphere s = new Sphere (69.69);
      Sphere a = new Sphere (69.690);
      if (s.equals(a))
      {
         System.out.println("boolean works");
      }
      else
      {
         System.out.println("HAHA FAILS");
      }
   }
   public static void testString()
   {
      String s = ("There Sphere class isz mutable!");
      String a = "";
      a.toString();
      if (s.equals(a))
      {
         System.out.println("dhas");
      }
   }  
      
   public static void main (String[] args)
   {
      testGetRadius();
      defaultSphere();
      testSetRadius();
      testSurfaceArea();
      testequals();
      
   }
}