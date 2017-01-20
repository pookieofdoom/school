public class MyChecked extends Exception 
{
   public MyChecked()
   {
   }
   
   public MyChecked(String msg)
   {
      super(msg);
   }
   
   public void checking() throws MyChecked
   {
      throw new MyChecked("FK");
   }
}
