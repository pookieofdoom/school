import java.util.*;
import java.io.*;

public class HTDriver
{
	public static void main(String[] args)
	{
		Scanner scanner = new Scanner(System.in);

		System.out.print("Enter input filename: ");
		String filename = scanner.next();

		Scanner fs = null;
		File input = null;
		
		HashTable students = new HashTable(0);

		try
		{
			input = new File(filename);
			fs = new Scanner(input);

			int lines = fs.nextInt();
			fs.nextLine();

			students = new HashTable(lines);

			for(int i = 0; i < lines; i++)
			{
				boolean skip = true;   // Skip line if true, otherwise read it in and add to heap
				boolean firstRun = true;
				long id = 0;   // Potential student ID
				String name = null;  // Potential student last name

				// Read in the next line of the file
				String line = fs.nextLine();
				// Create a new scanner to process the file line
				Scanner lineScanner = new Scanner(line);

				// Process the file line token by token
				while(lineScanner.hasNext() && (!skip || firstRun))
				{
					if(firstRun)
					{
						firstRun = false;
					}
					
					// Check if the first token is a long
					if(lineScanner.hasNextLong()) // File line starts with a long
					{
						skip = false;
						
						// Read in student ID
						id = lineScanner.nextLong();
						
						// Make sure student ID is valid (> 0)
						if(id <= 0)
						{
							// If student ID is <= 0, skip line
							skip = true;
						}

						// Check if the next token is a string
						if(lineScanner.hasNext() && !lineScanner.hasNextLong())
						{
							// Read in student last name
							name = lineScanner.next();

							// Check if the line has anything after the last name
							if(lineScanner.hasNext())
							{
								// If there are any tokens after the last name, skip the entire line
								skip = true;
							}
						}
						else  // Second token is not a last name (it's a long, so it's an ID)
						{
							// If second token is invalid, skip the entire line
							skip = true;
						}
					}
					else  // First token is not a long (ID)
					{
						// If the first token is invalid, skip the entire line
						skip = true;
					}
				}
				// Close the scanner for the file line
				lineScanner.close();

				// If the line was not marked as invalid, read in the student data and
				// add it to the heap
				if(!skip)
				{
					// Create new Student with the given ID and last name
					Student student = new Student(id, name);
					// Insert the new student into the hash table
					students.insert(student);
				}
			}
		}
		catch(FileNotFoundException e)
		{
			System.out.println("File not found.");
		}
		finally
		{
			fs.close();
		}
		
		scanner.nextLine();

		// Character representing the user's choice; initialized to 'c', a variable not
		// used by any menu choices but not 'q'; guarantees loop will run at least once
		char choice = 'c';

		// Menu
		System.out.print("Choose one of the following operations:\n"
				+ "\t" + "a - add the element\n"
				+ "\t" + "d - delete the element\n"
				+ "\t" + "f - find and retrieve the element\n"
				+ "\t" + "n - get the number of elements in the collection\n"
				+ "\t" + "e - check if the collection is empty\n"
				+ "\t" + "k - make the hash table empty\n"
				+ "\t" + "p - print the content of the hash table\n"
				+ "\t" + "o - output the elements of the collection\n"
				+ "\t" + "q - Quit the program\n");

		// Prompt user for choice and execute choice until user chooses to quit
		while (choice != 'q')
		{
			// Prompt user for choice and read it in
			System.out.print("Enter choice: ");
			choice = scanner.nextLine().charAt(0);

			// Execute the requested choice
			switch (choice)
			{
			case 'a':	// Insert a value into the collection
				// Prompt user for value to insert
				System.out.print("Enter student data: ");
				
				boolean skip = false;   // Skip line if true, otherwise read it in and add to heap
				long id = 0;   // Potential student ID
				String name = null;  // Potential student last name

				// Read in the next line of the file
				String line = scanner.nextLine();
				// Create a new scanner to process the file line
				Scanner lineScanner = new Scanner(line);

				// Process the input line token by token
				while(lineScanner.hasNext() && !skip)
				{
					// Check if the first token is a long
					if(lineScanner.hasNextLong()) // File line is a long
					{
						// Read in student ID
						id = lineScanner.nextLong();

						// Make sure student ID is valid (> 0)
						if(id <= 0)
						{
							// If student ID is <= 0, skip line
							skip = true;
						}

						// Check if the next token is a string
						if(lineScanner.hasNext() && !lineScanner.hasNextLong())
						{
							// Read in student last name
							name = lineScanner.next();

							// Check if the line has anything after the last name
							if(lineScanner.hasNext())
							{
								// If there are any tokens after the last name, skip the entire line
								skip = true;
							}
						}
						else  // Second token is not a last name (it's a long, so it's an ID)
						{
							// If second token is invalid, skip the entire line
							skip = true;
						}
					}
					else  // First token is not a long (ID)
					{
						// If the first token is invalid, skip the entire line
						skip = true;
					}
				}
				// Close the scanner for the file line
				lineScanner.close();

				// If the line was not marked as invalid, read in the student data and
				// add it to the heap
				if(!skip)
				{
					// Create new Student with the given ID and last name
					Student student = new Student(id, name);
					// Insert the new student into the hash table
					students.insert(student);
				}
				else
				{
					System.out.println("Invalid student record.");
				}
				break;
			case 'd':	// Delete specified value from collection
				// Prompt user for key of object to delete
				System.out.print("Enter a key: ");
				// Check if the user entered an long
				if(scanner.hasNextLong())
				{
					// Read in the long
					id = scanner.nextLong();
					
					if(id <= 0)
					{
						// Tell user an invalid value was input
						System.out.println("Invalid input");
						// Kill any leftover input
						scanner.nextLine();
						break;
					}
					
					Student dummy = new Student(id, "Dummy");
					// Delete specified value from collection
					students.delete(dummy);
					// Feedback message telling user that the value was deleted
					System.out.println("element with key " + id + " deleted");
					// Kill any leftover input
					scanner.nextLine();
					break;
				}
				else
				{
					// Tell user an invalid value was input
					System.out.println("Invalid input");
					// Kill any leftover input
					scanner.nextLine();
					break;
				}
			case 'f':	// Search the collection for the specified value
				// Prompt user for key to search for
				System.out.print("Enter a key: ");
				// Check if the user entered an long
				if(scanner.hasNextLong())
				{
					// Read in the long
					id = scanner.nextLong();
					
					if(id <= 0)
					{
						// Tell user an invalid value was input
						System.out.println("Invalid input");
						// Kill any leftover input
						scanner.nextLine();
						break;
					}
					
					Student dummy = new Student(id, "Dummy");
					// Search for specified value in collection
					Student temp = (Student)students.find(dummy);
					// Feedback message telling user that the value was found
					if(temp != null)
					{
						System.out.println("Student with ID " + id + " found");
					}
					else
					{
						System.out.println("Student with ID " + id + " not found");
					}
					// Kill any leftover input
					scanner.nextLine();
					break;
				}
				else
				{
					// Tell user an invalid value was input
					System.out.println("Invalid input");
					// Kill any leftover input
					scanner.nextLine();
					break;
				}
			case 'e':	// Check if the hash table is empty
				if(students.isEmpty())
				{
					// Feedback message telling the user the hash table is empty
					System.out.println("collection is empty");
				}
				else
				{
					// Feedback message telling the user the hash table is not empty
					System.out.println("collection is not empty");
				}
				break;
			case 'k':	// Make the hash table empty
				// Make the collection empty by invoking HashTable's makeEmpty method
				students.makeEmpty();
				// Feedback message  telling the user that the hash table has been made empty
				System.out.println("the hash table has been made empty");
				break;
			case 'n':	// Display how many nodes (the size of the collection) there are
				// Feedback message telling the user how many nodes are in the collection
				System.out.println("there are " + students.elementCount() + " elements");
				break;
			case 'p':	// Print the contents of the hash table using printTable
				students.printTable();
				break;
			case 'o':	// Print all elements in the hash table using the iterator
				Iterator iterator = students.iterator();
				
				while(iterator.hasNext())
				{
					System.out.println(iterator.next().toString());
				}
				
				break;
			case 'q':	// Quit
				// Feedback message telling user the application is closing
				System.out.println("Farewell");
				break;
			default:	// Invalid choice entered
				// Feedback message telling user that an invalid choice was entered
				System.out.println("Invalid choice");
				break;
			}
		}

	}
}
