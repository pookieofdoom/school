import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Test 
{
   public static void main(String args[]) throws FileNotFoundException
   {
      ArrayList<Person> list = new ArrayList<Person>();
      //order by last name
      list = Person.readFile("randomPeople.txt");
      Comparator<Person> c1 = new lastOrder();
      Collections.sort(list,c1);
      Person.writeFile("test1", list);
      
      //order by first name
      list = Person.readFile("randomPeople.txt");
      Comparator<Person> c2 = new firstOrder();
      Collections.sort(list,c2);
      Person.writeFile("test2", list);
      
      //order by state
      list = Person.readFile("randomPeople.txt");
      Comparator<Person> c3 = new stateOrder();
      Collections.sort(list,c3);
      Person.writeFile("test3",list);
      
      //order by age
      list = Person.readFile("randomPeople.txt");
      Comparator<Person> c4 = new ageOrder();
      Collections.sort(list,c4);
      Person.writeFile("test4",list);
      
      //order by last name then first name
      list = Person.readFile("randomPeople.txt");
      c1 = new lastOrder(c2);
      Collections.sort(list,c1);
      Person.writeFile("test5", list);
      
      //order by last name then state
      list = Person.readFile("randomPeople.txt");
      c1 = new lastOrder(c3);
      Collections.sort(list,c1);
      Person.writeFile("test6", list);
      
      //order by last name then age
      list = Person.readFile("randomPeople.txt");
      c1 = new lastOrder(c2);
      Collections.sort(list,c1);
      Person.writeFile("test7", list);
      
      //order by age then by state
      list = Person.readFile("randomPeople.txt");
      c4 = new ageOrder(c3);
      Collections.sort(list,c4);
      Person.writeFile("test8", list);
      
      // order by last name, then first name, then state, and finally age
      list = Person.readFile("randomPeople.txt");
      c4 = new ageOrder();
      c3 = new stateOrder(c4);
      c2 = new firstOrder(c3);
      c1 = new lastOrder(c2);
      Collections.sort(list,c1);
      Person.writeFile("test9",list);
     
      
   }

}
