/**
 * Project 1
 * Due: April 17, 2014
 * 
 * @author Jeremy Billote - jbillote@calpoly.edu
 * @author Anthony Dinh - adinh03@calpoly.edu
 */

import java.util.*;

// Class to test stack
public class StackTest
{
   // Main; run when program run from console
   // Tests MyStack class 
	public static void main(String[] args)
	{
	   // Sample stack holding strings
		MyStack<String> stringStack = new MyStack<String>();
      // Scanner object to read from keyboard
		Scanner scanner = new Scanner(System.in);
      // Represents choice from user; initialized to 'c' to ensure initial value not 'q'
		char choice = 'c';
		
      // Print menu
		System.out.print("Choose one of the following operations:\n"
				+ "- push/add (enter the letter a)\n"
				+ "- pop/delete (enter the letter d)\n"
				+ "- peek (enter the letter p) \n"
				+ "- check if the list is empty (enter the letter e) \n"
				+ "- Quit (enter the letter q)\n");
				
      // Loop to ask user for input while they don't want to quit ('q' not entered)
		while (choice != 'q')
		{
         // Ask user for choice and read it in
			System.out.print("Enter choice: ");
			choice = scanner.nextLine().charAt(0);

         // Evaluate choice
			switch (choice)
			{
			// When 'a' is entered, prompt user for a value and push it onto the stack and tell
			// user that it was pushed
			case 'a':
				System.out.print("Enter a value: ");
				String enq = scanner.nextLine();
				stringStack.push(enq);
				System.out.println(enq + " pushed in");
				break;
         // When 'd' is entered, pop top element from stack and tell user what element was
			// popped. If stack is empty, tell user
			case 'd':
				try
				{
					String dq = stringStack.pop();
					System.out.println(dq + " popped out");
				}
				catch (EmptyStackException e)
				{
					System.out.println("Invalid operation on an empty stack");
				}
				break;
			// When 'e' is entered, tell user if stack is empty or not
			case 'e':
				if (stringStack.isEmpty())
				{
					System.out.println("empty");
				}
				else
				{
					System.out.println("not empty");
				}
				break;
			// When 'p' is entered, tell user what the top value of the stack is. If stack is empty,
			// tell user.
			case 'p':
				try
				{
					System.out.println(stringStack.peek() + " on the top");
				}
				catch(EmptyStackException e)
				{
					System.out.println("Invalid operation on an empty stack");
				}
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
