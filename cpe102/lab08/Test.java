public class Test
{
   public static void main(String[] args)
   {
      int legs = 5;
      double gpa = 3.5;
      String name = "Kevin";
      Animal a = new Animal(legs);
      Animal b = new Animal(legs);
      Animal c = new Animal(6);
      
      if(!a.equals(b))
      {
         System.out.println("FK");
      }
      
      if(a.equals(c))
      {
         System.out.println("fk");
      }
      System.out.println(a.toString());
      
      Person d = new Person(name, legs);
      Person e = new Person(name, legs);
      Person f = new Person("Anthony",legs);
      
      
      if(!d.equals(e))
      {
         System.out.println("Fk");
      }
      if(d.equals(f))
      {
         System.out.println("fk");
      }
      
      System.out.println(d.toString());
      
      Student s = new Student(gpa, name, legs);
      Student t = new Student(gpa, name, legs);
      Student u = new Student(0.0, name, legs);
      
      if(!s.equals(t))
      {
         System.out.println("fk");
      }
      
      if(s.equals(u))
      {
         System.out.println("fk");
      }
      
      System.out.println(s.toString());
     
      
      
   }
}
      