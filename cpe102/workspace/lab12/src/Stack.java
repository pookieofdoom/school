
import java.util.*;
public class Stack<E>
{
   private LinkedList<E> a = new LinkedList<E>();
   
   public void push(E b)
   {
      a.addFirst(b); 
   }

   public E pop() {
      return a.remove();
   }
}
