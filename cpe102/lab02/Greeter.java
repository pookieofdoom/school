 /**
           * Greeter class for driver
           *
           * Anthony Dinh
           * Lab02 Part 1
           */

public class Greeter
{
   private String name;
   public Greeter(String name)
   {
      this.name = name;
   }
   public String greet()
   {
      return "Hello" + " " + name;
   }
}