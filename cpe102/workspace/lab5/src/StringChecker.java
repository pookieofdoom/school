import java.util.*;

public class StringChecker 
{
   public static boolean isBalanced(String string)
   {
      AStack<Character> stack = new AStack<Character>(string.length());
      
      for(int i = 0; i < string.length(); i++)
      {
         char charAt = string.charAt(i);
         
         if(!(Character.isDigit(charAt) || Character.isLetter(charAt)))
         {
            if(charAt == '(' || charAt == '[' || charAt == '{')
            {
               stack.push(charAt);
            }
            else if(charAt == ')' || charAt == ']' || charAt == '}')
            {
               if(stack.isEmpty())
               {
                  return false;
               }
               else
               {
                  char top = stack.pop();
                  
                  switch(top)
                  {
                     case '(':
                        if(charAt != ')')
                        {
                           return false;
                        }
                        break;
                     case '[':
                        if(charAt != ']')
                        {
                           return false;
                        }
                        break;
                     case '{':
                        if(charAt != '}')
                        {
                           return false;
                        }
                        break;
                  }
               }
            }
         }
      }
      
      return stack.isEmpty();
      
   }
   
   public static void main(String[] args)
   {
      Scanner scanner = new Scanner(System.in);
      char choice = 'c';
      
      while(choice != 'n')
      {
         System.out.print("Do you want to check a string? (y/n) ");
         choice = scanner.nextLine().charAt(0);
         
         switch(choice)
         {
         case 'y':
            System.out.print("Enter a string to check: ");
            boolean balanced = isBalanced(scanner.nextLine());
            
            if(balanced)
            {
               System.out.println("The string is balanced.");
            }
            else
            {
               System.out.println("The string is not balanced.");
            }
            break;
         case 'n':
            break;
         default:
            System.out.println("Invalid choice");
            break;
         }
      }
   }
}
