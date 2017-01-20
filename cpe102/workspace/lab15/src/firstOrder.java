import java.util.Comparator;


public class firstOrder implements Comparator<Person>
{
   
   private Comparator<Person> next;
   
   public firstOrder(Comparator<Person> next)
   {
      this.next = next;
   }
   
   public firstOrder()
   {
      
   }


   public int compare(Person a, Person b)
   {
      String aFirst = a.getFirst();
      String bFirst = b.getFirst();
      int order = aFirst.compareTo(bFirst);
      if(order !=0 || next ==null)
      {
         return order;
      }
      return next.compare(a, b);
      
   }

}
