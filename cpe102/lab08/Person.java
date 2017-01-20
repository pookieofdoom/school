public class Person extends Animal
{
   private String name;
   
   public Person(String name, int legs)
   {
      super(legs);
      this.name = name;
   }
   
   public boolean equals(Object o)
   {
      if(!super.equals(o))
      {
         return false;
      }
      if(this.name != ((Person)o).name)
      {
         return false;
      }
      return true;
   }
   
   public String toString()
   {
      return super.toString() +" and a Person object whose name is " +this.name;
   }
   
}