
public class Test 
{
   public static void main (String[] args)
   {
      Stack<String> stack = new Stack<String>();
      stack.push("A");
      stack.push("B");
      stack.push("C");
      System.out.println(stack.pop());
      stack.push("D");
      System.out.println(stack.pop());
      System.out.println(stack.pop());
      System.out.println(stack.pop()); 
      
     
   }
}
