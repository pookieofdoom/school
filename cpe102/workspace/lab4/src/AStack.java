
public class AStack<T>
{
   private T[] arr;
   private int top;
   
   public static class MyException extends RuntimeException
   {
      public MyException()
      {
         super();
      }
      
      public MyException (String message)
      {
         super(message);
      }
      
   }
   public AStack(int size)
   {
      arr = (T[]) new Object[size];
      top = -1;
   }
   
   public void push (T item)
   {
      if(top == arr.length -1)
      {
         T[] temp = (T[]) new Object[arr.length*2];
         for(int i=0; i< arr.length;i++)
         {
            temp[i] = arr[i];
         }
         arr = temp;
     
      }
      top++;
      arr[top] = item;
      
   }
   
   public boolean isEmpty()
   {
      return top == -1;
   }
   
   public T pop()
   {
      if(isEmpty())
      {
         throw new MyException();
      }
      T temp = arr[top];
      top--;
      return temp;
   }
   
   public T peek()
   {
      if(isEmpty())
      {
         throw new MyException();
      }
      return arr[top];
   }
   
   
   

}
