/**
 * Project 4
 * Due: May 22, 2014
 * 
 * @author Jeremy Billote - jbillote@calpoly.edu
 * @author Anthony Dinh - adinh03@calpoly.edu
 */

// Class representing a student
public class Student
{
   private long id;  // Student ID
   private String lastName;   // Student last name
   
   // Constructor initializing student ID and last name to values specified by user
   public Student(long id, String lastName)
   {
      this.id = id;
      this.lastName = lastName;
   }
   
   public boolean equals(Object other)
   {
	   if(other == null)
	   {
		   return false;
	   }
	   
	   if(this.getClass() != other.getClass())
	   {
		   return false;
	   }
	   
	   if(this.id != ((Student)other).id)
	   {
		   return false;
	   }
	   
	   return true;
   }
   
   // Return student information in the format specified in the project prompt
   public String toString()
   {
      return "{ id: " + this.id + ", name: " + this.lastName + " }";
   }
   
   public int hashCode()
   {
	   Long key = new Long(id);
	   	   
	   return key.hashCode();
   }
}