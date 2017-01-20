import java.util.Comparator;


public class lastOrder implements Comparator<Person>
{
   private Comparator<Person> next;

   public lastOrder(Comparator<Person> next)
   {
      this.next = next;
   }

   public lastOrder()
   {

   }


   public int compare(Person a, Person b)
   {
      String aLast = a.getLast();
      String bLast = b.getLast();
      int order = aLast.compareTo(bLast);
      if(order !=0 || next ==null)
      {
         return order;
      }
      return next.compare(a, b);

   }
}
