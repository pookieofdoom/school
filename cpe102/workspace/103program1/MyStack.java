/**
 * Project 1
 * Due: April 17, 2014
 * 
 * @author Jeremy Billote - jbillote@calpoly.edu
 * @author Anthony Dinh - adinh03@calpoly.edu
 */

import java.util.*;

// Linked List implementation of a generic stack
public class MyStack<T>
{
	// Inner class representing a linked list's node
	private class Node
	{
	   // Data value at given node
		public T value;
		// Pointer to next node in linked list
		public Node next;
	}

	// Top of the stack
	private Node top;

	// Initialize stack to empty
	public MyStack()
	{
		top = null;
	}

	// Push given element onto top of stack
	public void push(T item)
	{
	   // Node to be pushed to top
		Node temp = new Node();
		// Set new node's value to given element
		temp.value = item;
		// Set new node's next field to point to old top
		temp.next = top;
		// Set new node to be the new top
		top = temp;
	}

	// Pop the top element from the stack and return its value
	public T pop()
	{
	   // Throw EmptyStackException if stack is empty
		if (isEmpty())
		{
			throw new EmptyStackException();
		}

		// Store top element's value to be returned
		T temp = top.value;

		// Set new top to point to what old top's next field pointed to
		top = top.next;

		// Return top element's value
		return temp;
	}

	// Look at top element from the stack and return it's value without deleting it
	public T peek()
	{
      // Throw EmptyStackException if stack is empty
		if (isEmpty())
		{
			throw new EmptyStackException();
		}

		// Return top element's value
		return top.value;
	}

	// Check if stack is empty; stack is empty if top points to nothing (null)
	public boolean isEmpty()
	{
		return top == null;
	}
}