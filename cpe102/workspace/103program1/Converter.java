/**
 * Project 1
 * Due: April 17, 2014
 * 
 * @author Jeremy Billote - jbillote@calpoly.edu
 * @author Anthony Dinh - adinh03@calpoly.edu
 */

import java.util.StringTokenizer;

// Class to convert infix to postfix and evaluate postfix expressions
public class Converter
{
   // Convert infix to postfix
	public static String infixToPostfix(String expression)
	{
	   // String to be returned
		String output = new String();
		// Stack holding expression's operators
		MyStack<String> stack = new MyStack<String>();
		// Used to read in characters separated by spaces
		StringTokenizer st = new StringTokenizer(expression);
		
		// Loop while there are still characters separated by spaces
		while(st.hasMoreTokens())
		{
		   // Get next character separated by space
		   String temp = st.nextToken();
			
		   // Add operands to output; operands can be numbers or letters
			if(Character.isDigit(temp.charAt(0)) || Character.isLetter(temp.charAt(0)))
			{
				output = output + (temp + " ");
			
			}
			// Process operators
			else
			{
			   // Lowest priority operators; immediately push onto stack unless higher or equal 
			   // priority operands are at the top
			   if(temp.equals("+") || temp.equals("-"))
			   {
			      // Pop higher or equal priority operands and add them to output
			      while(!stack.isEmpty() && !stack.peek().equals("("))
			      {
			         output = output + stack.pop() +" ";
			      }
			      
			      stack.push(temp);
			   }
			   // Higher priority operators; immediately push onto stack unless higher or equal
			   // priority operands at the top
			   else if(temp.equals("*") || temp.equals("/"))
			   {
			      // Pop higher or equal priority operands and them to output
			      while(!stack.isEmpty() && (stack.peek().equals("*") || stack.peek().equals("/")))
			      {
			         output = output + (stack.pop() + " ");
			      }
			      
			      stack.push(temp);
			   }
			   // Process parentheses
			   else
			   {
			      // Immediately push open parenthesis
			      if(temp.equals("("))
			      {
			         stack.push(temp);
			      }
			      // Pop entire stack until open parenthesis reached 
			      else
			      {
			         while(!stack.isEmpty() && !stack.peek().equals("("))
			         {
			            output = output + (stack.pop() + " ");
			         }
			         
			         // Pop open parenthesis
			         stack.pop();
			      }
			   }
			}
			
		}
		
		// Pop rest of stack and add to output
		while(!stack.isEmpty())
		{
		   output = output + (stack.pop() + " ");
		}
		   
		// Return output
		return output;
	}
	
	// Evaluate postfix expressions
	public static double postfixVaue (String expression)
	{
	   // Stack holding expression's operands
	   MyStack<String> stack = new MyStack<String>();
      // Used to read in characters separated by spaces
	   StringTokenizer st = new StringTokenizer(expression);
      
      // Loop while there are still characters separated by spaces
      while(st.hasMoreTokens())
      {
         // Get next character separated by space
         String temp = st.nextToken();
         
         // Push operands onto stack
         if(Character.isDigit(temp.charAt(0)))
         {
            stack.push(temp);
         }
         // When an operator is reached, pop the top two operands and evaluate them
         // using the operator and push result back onto stack
         else
         {
            // Very top operand
            double num1 = Double.parseDouble(stack.pop());
            // Second from top operand (when operator reached)
            double num2 = Double.parseDouble(stack.pop());
            
            // Evaluate expression
            switch(temp.charAt(0))
            {
               case '+':
                  stack.push(new Double(num2 + num1).toString());
                  break;
               case '-':
                  stack.push(new Double(num2 - num1).toString());
                  break;
               case '*':
                  stack.push(new Double(num2 * num1).toString());
                  break;
               case '/':
                  stack.push(new Double(num2 / num1).toString());
                  break;
               
            }
         }
         
      }
      
      // Return final value
      return Double.parseDouble(stack.pop());
	}
}