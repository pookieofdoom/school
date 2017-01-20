/**
 * Provided source for CPE 102 Lab on the Chain of Responsibility pattern.
 *
 * @author Kurt Mammen
 */
import java.util.*;
import java.io.*;

public class Person
{
   private String first;
   private String last;
   private String state;
   private int age;

   /**
    * Constructor a Person with the specified characteristics.
    *
    * @param first The first name of the person.
    * @param last The last name of the person.
    * @param state The two-character state abreviation where the person lives.
    * @param age The current age (in years) of the person.
    */
   public Person(String first,
                 String last,
                 String state,
                 int age)
   {
      this.first = first;
      this.last = last;
      this.state = state;
      this.age = age;
   }

   /**
    * The overridden equals method.
    *
    * @param o The reference to compare with this for equality.
    *
    * @return true when o is logically equal to this, otherwise false.
    */
   public boolean equals(Object o)
   {
      if (o == null || getClass() != o.getClass())
      {
         return false;
      }

      if (age != ((Person)o).age)
      {
         return false;
      }
   
      if (!first.equals(((Person)o).first))
      {
         return false;
      }
   
      if (!last.equals(((Person)o).last))
      {
         return false;
      }
   
      if (!state.equals(((Person)o).state))
      {
         return false;
      }
   
      return true;
   }

   /**
    * The overridden toString method.
    *
    * @return A String containing all of a Person's information separated by
    *         spaces.
    */
   public String toString()
   {
      return first + " "
           + last + " "
           + state + " "
           + age;
   }

   /**
    * Accessor method for first name of the person.
    *
    * @return The first name of the person.
    */
   public String getFirst()
   {
      return first;
   }

   /**
    * Accessor method for last name of the person.
    *
    * @return The last name of the person.
    */
   public String getLast()
   {
      return last;
   }

   /**
    * Accessor method for the state the person lives in.
    *
    * @return The two-character abreviation for the state the person lives in.
    */
   public String getState()
   {
      return state;
   }

   /**
    * Accessor method for age of the person.
    *
    * @return The age of the person.
    */
   public int getAge()
   {
      return age;
   }

   /**
    * A static method that writes a List of People to a file.
    *
    * @param fileName The name of the file to write to.
    * @param people The list of Person objects to write to the file.
    *
    * @throws FileNotFoundException
    */
   public static void writeFile(String fileName, List<Person> people)
   throws FileNotFoundException
   {
      PrintWriter out = new PrintWriter(new File(fileName));

      for (Person p : people)
      {
         out.println(p);
      }

      out.close();
   }

   /**
    * A static method that reads a text file of Person data into a list.
    *
    * @param fileName The name of the file to read from.
    *
    * @throws FileNotFoundException
    *
    * @return A list of People read from the file.
    */
   public static ArrayList<Person> readFile(String fileName)
   throws FileNotFoundException
   {
      ArrayList<Person> list = new ArrayList<Person>();

      Scanner scnr = new Scanner(new File(fileName));

      while(scnr.hasNextLine())
      {
         Scanner line = new Scanner(scnr.nextLine());

         Person p = new Person(line.next(),
                               line.next(),
                               line.next(),
                               Integer.valueOf(line.next()));

         list.add(p);
      }

      scnr.close();
      list.trimToSize();
      return list;
   }
}
