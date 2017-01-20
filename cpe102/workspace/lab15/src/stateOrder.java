import java.util.Comparator;


public class stateOrder implements Comparator<Person>
{
   private Comparator<Person> next;

   public stateOrder(Comparator<Person> next)
   {
      this.next = next;
   }

   public stateOrder()
   {

   }


   public int compare(Person a, Person b)
   {
      String aState = a.getState();
      String bState = b.getState();
      int order = aState.compareTo(bState);
      if(order !=0 || next ==null)
      {
         return order;
      }
      return next.compare(a, b);

   }
}
