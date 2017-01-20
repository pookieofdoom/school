public class Animal
{
   private int legs;
   
   public Animal(int legs)
   {
      this.legs = legs;
   }
   
   public boolean equals(Object o)
   {
      //null check
      //type check
      if(this.legs != ((Animal)o).legs)
      {
         return false;
      }
      return true;
   }
   
   public String toString()
   {
      return "I am an Animal object with " +this.legs  +" legs";
   }
}