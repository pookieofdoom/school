import java.util.*;
public class AStackDriver 
{
   public static void main(String[] args)
   {
      AStack<Integer> intStack = new AStack<Integer>(5);
      Scanner scanner = new Scanner(System.in);
      char choice = 'c';

      System.out.print("Choose one of the following operations:\n"
            + "- push/add (enter the letter a)\n"
            + "- pop/delete (enter the letter d)\n"
            + "- peek (enter the letter p)\n"
            + "- check if the list is empty (enter the letter e) \n"
            + "- quit (enter the letter q)\n");
      
      while (choice != 'q')
      {
         System.out.print("Enter choice: ");
         choice = scanner.nextLine().charAt(0);

         switch (choice)
         {
         case 'a':
            System.out.print("Enter a value: ");
            if (scanner.hasNextInt())
            {
               int enq = scanner.nextInt();
               intStack.push(new Integer(enq));
               System.out.println(enq + " pushed");
               scanner.nextLine();
            }
            else
            {
               System.out.println("Invalid input");
               scanner.nextLine();
            }
            break;
         case 'd':
            try
            {
               int dq = intStack.pop();
               System.out.println(dq + " popped");
            }
            catch (AStack.MyException e)
            {
               System.out.println("Invalid operation: the stack is empty");
            }
            break;
         case 'p':
            try
            {
               int peek = intStack.peek();
               System.out.println(peek +" peeked");
            }
            catch (AStack.MyException e)
            {
               System.out.println("Invalid operation: the stack is empty");
            }
            break;
         case 'e':
            if (intStack.isEmpty())
            {
               System.out.println("empty");
            }
            else
            {
               System.out.println("not empty");
            }
            break;
         case 'q':
            System.out.println("quitting");
            break;
         default:
            System.out.println("Invalid choice");
            break;
         }
      }
      
      while(!intStack.isEmpty())
      {
         int dq = intStack.pop();
         System.out.print(dq + " ");
      }
      System.out.print("\n");
   }
   
}
