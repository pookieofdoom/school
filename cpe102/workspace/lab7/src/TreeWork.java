
public class TreeWork 
{
   public static <T extends Comparable<? super T>> boolean isHeap (T[] arr, int N)
   {
      for(int i=0; i<N;i++)
      {
	
	 if(i*2+1 >= N)
         { 
            break;
         }	  
	
         if(arr[i*2+1] != null && arr[i].compareTo(arr[i*2+1]) > 0 )
         {
	     
            return false;
         }
	
	if(i*2+2 >= N)
	{
	   break;
	}
	
	if (arr[i*2+2] != null &&  arr[i].compareTo(arr[i*2+2]) > 0)
	{
		return false;
	}
  
         
      }
	
      return true;
   }
   
   public static <T> void printTree (T[] arr, int N)
   {      
      int line = 0;
      int nodes = 0;
      for(int i = 0; i < N; i++)
      {
         System.out.print(arr[i].toString() + " ");
         nodes++;
         if(nodes == Math.pow(2, line))
         {
            System.out.print("\n");
            line++;
            nodes = 0;
         }
	
      }
	if(nodes != 0)
	{
	System.out.print("\n");
	}
   }
}
