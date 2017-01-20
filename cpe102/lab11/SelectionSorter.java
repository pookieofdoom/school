
import java.util.ArrayList;

public class SelectionSorter
{
   private ArrayList<String> a;

   public SelectionSorter(ArrayList<String> array)
   {
      this.a = array;
   }

   public void sort()
   {
      for (int i = 0; i < a.size() - 1; i++)
      {
         int minPos = minimumPosition(i);
         swap(minPos, i);
      }
   }

   private int minimumPosition(int from)
   {
      int minPos = from;

      for (int i = from + 1; i < a.size(); i++)
      {
         if (a.get(i).compareTo( a.get(minPos)) < 0)
         {
            minPos = i;
         }
      }

      return minPos;
   }

   private void swap(int i, int j)
   {
      String temp = a.get(i);
      a.set(i,a.get(j));
      a.set(j,temp);
   }
}

