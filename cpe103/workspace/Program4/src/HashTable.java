import java.util.*;

/**
 * Project 4
 * Due: May 22, 2014
 * 
 * @author Jeremy Billote - jbillote@calpoly.edu
 * @author Anthony Dinh - adinh03@calpoly.edu
 */

// Class representing a hash table of generic elements
public class HashTable
{
	// Class representing an entry in the hash table
	private class HashEntry
	{
		public Object item;	// Data stored
		public boolean isActive;	// True if the element is active (not deleted)
		
		// Initialize HashEntry given an object x
		public HashEntry(Object x)
		{
			// Set item to x
			item = x;
			// Item has not been deleted yet, so make isActive true
			isActive = true;
		}
	}
	
	// Array representing the hash table
	private HashEntry[] table;
	// Amount of cells storing data, including inactive cells
	private int occupiedCells;
	
	// Initialize the hash table to be an empty table of given size
	public HashTable(int size)
	{
		// Initialize the hash table to a new array of HashEntry's with a size
		// equal to the next prime number greater than or equal to the provided
		// size
		table = new HashEntry[nextPrime(2 * size)];
		// Initialize the number of occupied cells to 0; the table is empty
		occupiedCells = 0;
	}
	
	// Get the next prime number greater than or equal to the given number
	private int nextPrime(int n)
	{
		// If n is even, make it odd
		if(n%2 == 0)
		{
			n = n+1;
		}
		

		// Check if prime is in fact a prime number
		boolean prime = isPrime(n);
		
		// increment n as long as isPrime is false; eventually n will
		// become a prime number
		while(!prime)
		{
			//check the next odd number if prime
			n = n+2;
			// Check if the new value of prime is a prime number
			prime = isPrime(n);
		}
		
		// Return the prime number
		return n;
	}
	
	// Support method for nextPrime; checks the given number, n, to see if it is a
	// prime number; returns true if n is prime
	private boolean isPrime(int n)
	{
		// Check if n is divisible by 2, but not equal to 2;
		// if n is divisible by 2, it is not a prime number
		if(n % 2 == 0 && n != 2)
		{
			return false;
		}
		
		// Check if n is divisible by any odd numbers less than itself and
		// greater than 1; if n is divisible by any odd numbers greater than 1
		// and less than itself, it is not a prime number
		for(int i = 3; i < n; i += 2)
		{
			if(n % i == 0)
			{
				return false;
			}
		}
		
		// Return true if the two previous tests all pass
		return true;
	}
	
	// Inner class representing an iterator to traverse the hash table
	private class Iter implements Iterator
	{
		// Cursor; current index in the array
		int cursor;
		
		// Constructor to initialize the cursor
		public Iter()
		{
			// Find the first index in the table that has an active element
			for(cursor = 0; cursor < table.length; cursor++)
			{
				// Stop updating cursor (break the loop) when an active element is found
				if(table[cursor] != null && table[cursor].isActive)
				{
					break;
				}
			}
		}
		
		// Returns true if there is an active element left in the table that hasn't
		// been traveled to
		public boolean hasNext()
		{
			// Loop through the array, starting from where the cursor is
			for(int i = cursor; i < table.length; i++)
			{
				// Return true the moment an active element is found
				if(table[i] != null && table[i].isActive)
				{
					return true;
				}
			}
			
			// An active element has not been found, so return false
			return false;
		}

		// Return the next active element in the table
		public Object next() 
		{
			// Throw NoSuchElementException if there isn't an unvisited element
			if(!hasNext())
			{
				throw new NoSuchElementException();	
			}
			
			// Save the element to return
			Object temp = table[cursor].item;
			
			// Update cursor to point to the next active element or the end of the table
			for(cursor = cursor + 1; cursor < table.length; cursor++)
			{
				// Break if we find an active element
				if(table[cursor] != null && table[cursor].isActive)
				{
					break;
				}
			}
			
			// Return the saved element
			return temp;
		}
		
		// Unsupported
		public void remove() 
		{
			throw new UnsupportedOperationException();
		}
		
	}
	
	// Insert an object into the table
	public void insert(Object item)
	{
		// Find a table index for the item
		int index = findPosition(item);
		
		// If the index is empty, insert the item as a new entry
		if(table[index]== null)
		{
			// Create a new HashEntry for the item
			HashEntry temp = new HashEntry(item);
			// Insert the new entry into the table
			table[index] = temp;
			// A new cell is occupied, so increment occupied cells
			occupiedCells++;
			
			// Rehash the table if the table is more than half empty
			if(!(occupiedCells < table.length / 2))
			{
				rehash();
			}
		}
		// If the index is not empty, reactivate the entry
		else
		{
			// Reactivate the entry if it is inactive, otherwise no action needs
			// to be taken
			if(!table[index].isActive)
			{
				table[index].isActive = true;
			}
		}
	}
	
	// Rehash (resize and reinsert all active elements) the table
	private void rehash()
	{
		// Make a temporary table pointing to the current table
		HashEntry[] temp = table;
		// Make table point to a new table of an increased length
		table = new HashEntry[nextPrime(2 * temp.length)];
		// Reset the number of occupied cells
		occupiedCells = 0;
		
		// Copy all active elements from the old table to the new one
		for(int i = 0; i < temp.length; i++)
		{
			// Check if element exists and if it is active
			if(temp[i] != null && temp[i].isActive)
			{
				// Find a position for the item in the new table
				int index = findPosition(temp[i].item);
				// Add the item to the new table
				table[index] = temp[i];
				// Increment occupied cells
				occupiedCells++;
			}
		}
	}

	// Find a position in the table for given element
	private int findPosition(Object x)
	{
		// Number used in quadratic probing formula; number of cells occupied
		// by same hash value
		int i = 0;
		// Hash the object
		int hashValue = hash(x);
		// Make index the hashValue
		int index = hashValue;
		
		// If the cell is occupied and the item is not there, keep probing
		while(table[index] != null && !table[index].item.equals(x))
		{
			// Increment number of cells occupied by same hashValue
			i++;
			// Calculate new index
			index =  (hashValue + (int)Math.pow(i, 2)) % table.length;
		}
		
		// Return position
		return index;
	}
	
	// Obtain hashValue for given object
	private int hash(Object x)
	{
		// hashValue is the object's hashcode modded with the table length
		return x.hashCode() % table.length;
	}
	
	// Delete a given element
	public void delete(Object item)
	{
		// Find an index for the given element
		int index = findPosition(item);
		
		// Make the item at index inactive
		if(table[index] != null && table[index].isActive)
		{
			table[index].isActive = false;
		}
	}
	
	// Search for a given element and return it
	public Object find(Object item)
	{
		// Find an index for the given element
		int index = findPosition(item);
		// Boolean representing if the object was found
		boolean found;
		
		// If the given index is not empty and the element is active, the item
		// was found
		if(table[index] != null && table[index].isActive)
		{
			found = true;
		}
		else
		{
			found = false;
		}
		
		// If we found the item, return it
		if(found)
		{
			return table[index].item;
		}
		
		// If the item was not found, return null
		return null;
	}
	
	// Return number of active elements in the table
	public int elementCount()
	{
		// Number of active elements
		int count = 0;
		
		// Iterate through the array and increment the number of active elements
		// if an active element is found
		for(int i = 0; i < table.length; i++)
		{
			if(table[i] != null && table[i].isActive)
			{
				count++;
			}
		}
		
		// Return number of active elements
		return count;
	}
	
	public boolean isEmpty()
	{
		for(int i = 0; i < table.length; i++)
		{
			if(table[i] != null && table[i].isActive)
			{
				return false;
			}
		}
		
		return true;
	}
	
	public void makeEmpty()
	{
		int size = table.length;
		table = new HashEntry[size];
		occupiedCells = 0;
	}
	
	public void printTable()
	{
		for(int i = 0; i < table.length; i++)
		{
			Object content;
			boolean active;
			
			if(table[i] == null)
			{
				System.out.println("[" + i + "]: empty");
			}
			else
			{
				content = table[i].item;
				active = table[i].isActive;
				
				if(active)
				{
					System.out.println("[" + i + "]: " + content.toString() + ", active");
				}
				else
				{
					System.out.println("[" + i + "]: " + content.toString() + ", inactive");
				}
			}
		}
	}
	
	public Iterator iterator()
	{
		return new Iter();
	}
}