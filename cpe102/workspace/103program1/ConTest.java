/**
 * Project 1
 * Due: April 17, 2014
 * 
 * @author Jeremy Billote - jbillote@calpoly.edu
 * @author Anthony Dinh - adinh03@calpoly.edu
 */

import java.util.EmptyStackException;
import java.util.Scanner;

// Class to test Converter class
public class ConTest 
{
   // Main; run when program run from console
   // Tests Converter class
   public static void main (String[] args)
   {
      // Scanner object to read from keyboard
      Scanner scanner = new Scanner(System.in);
      
      // Print menu
      System.out.println("Choose one of the following operations: \n"
            + "- Infix to postfix conversion (enter the letter i) \n"
            + "- Postfix expression evaluation (enter the letter p) \n"
            + "- Arithmeric expression evaluation (enter the letter a) \n"
            + "- Quit the program (enter the letter q) \n");
      
      // Represents choice from user; initialized to 'c' to ensure initial value not 'q'
      char choice = 'c';
      
      // Loop to ask user for input while they don't want to quit ('q' not entered)
      while (choice != 'q')
      {
         // Ask user for choice and read it in
         System.out.print("Enter choice: ");
         choice = scanner.nextLine().charAt(0);

         // Evaluate choice
         switch (choice)
         {
         // When 'i' is entered, prompt user for infix expression, convert it to postfix
         // and display it to user
         case 'i':
            System.out.print("Enter an infix expression: ");
            String postfix = Converter.infixToPostfix(scanner.nextLine());
            System.out.println("the postfix expression is: " + postfix);
            break;
         // When 'p' is entered prompt user for postfix expression, evaluate it, and display
         // result to user
         case 'p':
            System.out.print("Enter a postfix expression: ");
            System.out.println("the value of the postfix expression is: " + 
                  new Double(Converter.postfixVaue(scanner.nextLine())));
            break;
         // When 'a' is entered, prompt user for arithmetic expression, evaluate it, and display
         // result to user
         case 'a':
            System.out.print("Enter an arithmetic expression: ");
            postfix = Converter.infixToPostfix(scanner.nextLine());
            System.out.println("the value of the arithmetic expression is: "
                  + new Double(Converter.postfixVaue(postfix)).toString());
            break;
         // When 'q' is entered, quit program
         case 'q':
            System.out.println("Farewell message goes here");
            break;
         // Tell user if invalid choice was entered
         default:
            System.out.println("Invalid choice");
            break;
         }
      }
   }
}
