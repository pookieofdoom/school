import java.util.Scanner;

public class AVLTest
{
   public static void main(String[] args)
   {
      BasicAVL intQueue = new BasicAVL();
      Scanner scanner = new Scanner(System.in);
      char choice = 'c';

      System.out.print("Choose one of the following operations:\n"
            + "- insert/add (enter the letter a)\n"
            + "- print array (enter the letter p) \n"
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
               intQueue.insert(enq);
               System.out.println(enq + " inserted");
               scanner.nextLine();
            }
            else
            {
               System.out.println("Invalid input");
               scanner.nextLine();
            }
            break;
        
         case 'p':
            intQueue.print();
            break;
         case 'q':
            System.out.println("quitting");
            break;
         default:
            System.out.println("Invalid choice");
            break;
         }
      }
      

   }
}