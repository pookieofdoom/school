import java.util.Comparator;


public class ageOrder implements Comparator<Person> 
{
   private Comparator<Person> next;

   public ageOrder(Comparator<Person> next)
   {
      this.next = next;
   }

   public ageOrder()
   {

   }


   public int compare(Person a, Person b)
   {
      int aAge = a.getAge();
      int bAge = b.getAge();
      
      if(aAge != bAge || next ==null)
      {
         return aAge-bAge;
      }
      return next.compare(a, b);

   }
}
