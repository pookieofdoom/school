package program5;
import java.util.*;

public class Test 
{
   public static void main(String[] args) throws DictionaryException
   {
      ArrayList<String> herro = new ArrayList<String>();
      try 
      {
         
         Dictionary a = new Dictionary("partialRandomDict.txt", true);  
         a.iterator();
         a.lookUp("MOTHERLY");
      } 
      catch (DictionaryException e) 
      {
         e.printStackTrace();
      }
      
   }

}
