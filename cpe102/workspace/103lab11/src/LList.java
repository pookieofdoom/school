import java.util.*;

public class LList<T> 
{
   private Node head;
   
   private class Node
   {
      T element;
      Node next;
   }
   
   private class Iter implements Iterator<T>
   {
      public Node cursor;
      public Iter()
      {
         cursor = head;
      }
      
      public boolean hasNext()
      {
         return cursor != null;
      }
      
      public T next()
      {
         if(!hasNext())
         {
            throw new NoSuchElementException();
         }
         
         T answer = cursor.element;
         cursor = cursor.next;
         return answer;
         
      }
      
      public void remove()
      {
         throw new UnsupportedOperationException();
      }
      
   }
   
   public LList()
   {
      head = null;
   }
   
   public Iterator<T> iterator()
   {
      return new Iter();
   }
   
   public void add (T item)
   {
      if(head == null)
      {
         Node temp = new Node();
         temp.element = item;
         head = temp;
      }
      else
      {
         Node temp = head;
         Node insert = new Node();
         while(temp.next != null)
         {
            temp = temp.next;
         }
         
         insert.element = item;
         temp.next = insert;
         
      }
   }
   
}
