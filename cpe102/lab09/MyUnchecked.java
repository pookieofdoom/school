public class MyUnchecked extends RuntimeException
{
   public MyUnchecked()
   {
   }
   
   public MyUnchecked(String msg)
   {
      super(msg);
   }
   
   
   public void unchecking() 
   {
      throw new MyUnchecked("HERRO");
   }
}