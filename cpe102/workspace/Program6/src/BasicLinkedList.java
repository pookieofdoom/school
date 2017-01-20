import java.util.Iterator;


public class BasicLinkedList<E> implements BasicList<E>, java.lang.Iterable<E>
{
   private int size;
   private Node head;


   private class Node
   {
      public E data;
      public Node next, prev;

   }

   public BasicLinkedList()
   {
      this.head = new Node();
      head.next = head;
      head.prev = head;
      this.size = 0;


   }

   public void add(E element) 
   {

      Node n = new Node();
      n.data = element;
      n.next = head;
      n.prev = head.prev;
      head.prev.next = n;
      head.prev = n;
      size++;

   }


   public void add(int index, E element) 
   {
      if(index <0 || index > size )
      {
         throw new java.lang.IndexOutOfBoundsException();
      }
      Node n = new Node();
      n.data = element;
      Node temp = head;




      for(int i=0; i<index+1; i++)
      {
         temp = temp.next;
      }


      n.next = temp; 
      n.prev = temp.prev;
      temp.prev.next = n;
      temp.prev = n;

      size++;


   }


   public void clear() 
   {
      this.head = new Node();
      head.next = head;
      head.prev = head;
      this.size = 0;

   }


   public boolean contains(E element) 
   {
      Node temp = head.next;
      for(int i=0; i<size; i++)
      {

         if(temp.data ==null && element != null)
         {
         }
         else if(temp.data !=null && element == null)
         {
         }

         else if(temp.data == null && element == null)
         {
            return true;
         }

         else if(temp.data.equals(element))
         {
            return true;
         }

         temp = temp.next;
      }
      return false;
   }


   public E get(int index) 
   {
      if(index < 0 || index >= size)
      {
         throw new java.lang.IndexOutOfBoundsException();

      }
      Node temp = head;
      for(int i=0; i<index+1; i++)
      {
         temp = temp.next;
      }

      return temp.data;
   }


   public int indexOf(E element) 
   {
      Node temp = head.next;
      for(int i=0; i<size;i++)
      {
        
         if(temp.data == null && element == null)
         {
            return i;
         }
         else if(temp.data.equals(element))
         {
            return i;
         }
         temp= temp.next;
      }
      throw new java.util.NoSuchElementException();
   }


   public E remove(int index) 
   {
      if(index < 0 || index >= size)
      {
         throw new java.lang.IndexOutOfBoundsException();

      }

      Node temp = head;
      for(int i=0; i<index+1; i++)
      {
         temp = temp.next;
      }

      temp.next.prev = temp.prev;
      temp.prev.next = temp.next;

      size--;
      return temp.data;

   }


   public E set(int index, E element) 
   {
      if(index < 0 || index >= size)
      {
         throw new java.lang.IndexOutOfBoundsException();

      }

      Node temp = head;

      for(int i=0; i<index+1; i++)
      {
         temp = temp.next;
      }
      E stuff = temp.data;
      temp.data = element;
      return stuff;

   }


   public int size() 
   {
      return this.size;
   }



   public Iterator<E> iterator() 
   {
      return new MyIt();
   }
   public BasicListIterator<E> basicListIterator()
   {
      return new MyIt();
   }

   private class MyIt implements BasicListIterator<E>
   {
      private Node cursor = head;


      public boolean hasPrevious() 
      {
         return cursor.prev != head.prev;
      }


      public E previous() 
      {
         if(!hasPrevious())
         {
            throw new java.util.NoSuchElementException();
         } 

         cursor = cursor.prev;

         return cursor.next.data;
      }


      public boolean hasNext() 
      {
         return cursor.next!= head;
      }


      public E next() 
      {

         if(!hasNext())
         {
            throw new java.util.NoSuchElementException();
         }


         cursor = cursor.next;

         return cursor.data;
      }


      public void remove() 
      {
         throw new java.lang.UnsupportedOperationException(); 

      }

   }





}
