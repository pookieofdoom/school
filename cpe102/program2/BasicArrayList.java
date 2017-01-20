import java.util.*;

public class BasicArrayList implements BasicList
{
   public final static int DEFAULT_CAPACITY = 10;
   private Object[] list;
   private int size;
   
   
   public BasicArrayList()
   {  
      list = new Object[DEFAULT_CAPACITY];
      size = 0;
      
   }
   
   public BasicArrayList(int capacity)
   {
      if(capacity < DEFAULT_CAPACITY)
      {
         list = new Object[DEFAULT_CAPACITY];
      }
      else
      {
         list = new Object[capacity];
      }
      size = 0;
      
   }
   
   //methods
   public void add(int index, java.lang.Object element)  
   {              
      if (index <0 || index > list.length  || index > size)
      {
         throw new IndexOutOfBoundsException();
      }
      int i;
      Object[] temp;
      if (index != size)
      //if there is a element in the index, find the first spot that there isn't an element
      // and move everything down one over and place the element in the index
      {
         for ( i = index; i<list.length && i < size; i++)
         {
             
         }
         if(i >= list.length)
         {
             temp = new Object[2 * list.length];
             System.arraycopy(list, 0, temp, 0, list.length);
             list = temp;
         }
         for(; i != index; i--)
         {
            list[i] = list[i-1];
         }
      }
      list[index] = element;
      size = size +1;

         
   }
   public void add(java.lang.Object element)
   {
      int i;
      Object[] temp;
      for (i = 0; i<list.length && i < size; i++)
      {
         //check if the list is full of elements and if it is, double it
          
      }

      if(i >= list.length)
      {
         temp = new Object[2 * list.length];
         System.arraycopy(list, 0, temp, 0, list.length);
         list = temp;
      } 
          
      list[i] = element;
      size = size+1;

   }
   public int capacity()
   {
      return list.length;
   }
   public void clear()
   {
      list = new Object[DEFAULT_CAPACITY];
      size = 0;     
   }
   public boolean contains(java.lang.Object element)
   {
      for(int i =0; i<list.length;i++)
      {
         if(element.equals( list[i]))
         {
            return true;
         }
      }
      return false;
   }
   public java.lang.Object get(int index)
   {

      if(index <0 || index >= list.length || index >= size)
      {
         throw new IndexOutOfBoundsException();
      }
     
      return list[index];
      
   }
   public int indexOf(java.lang.Object element)
   {
      for(int i =0; i<list.length;i++)
      {
         if(element.equals( list[i]))
         {
            return i;
         }
      } 
      throw new NoSuchElementException();
  
   }
   public java.lang.Object remove(int index)
   {
      int i;
      if(index <0 || index > list.length || index >= size)
      {
         throw new IndexOutOfBoundsException();
      }
      Object temp = list[index];
      list[index] = null;
      for(i = index;  i < size-1; i++) 
      {
         list[i] = list[i+1];
      }
      list[i] = null;
      size = size -1;
      return temp;   
   }
   public java.lang.Object set(int index, java.lang.Object element)
   {
      if(index <0 || index > list.length || index >= size)
      {
         throw new IndexOutOfBoundsException();
      }


      Object temp;
      temp = list[index];
      list[index] = element;
      return temp;
   }
   public int size()
   {
      return size;
   }
   
   public void trimToSize()
   { 
     Object[] temp;
     if(size > DEFAULT_CAPACITY)
     {
        temp = new Object[size];
        System.arraycopy(list, 0, temp, 0, size);
        list = temp;
     }
     else if(list.length >  DEFAULT_CAPACITY)
     {
        temp = new Object[DEFAULT_CAPACITY];
        System.arraycopy(list, 0, temp, 0, size);
        list = temp;
     }
 
   }
   public java.lang.Object[] unusualMethodForTestDriverOnly()
   {
      return list;
   }
                
}