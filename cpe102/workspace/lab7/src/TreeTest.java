import java.util.Scanner;


public class TreeTest
{
   public static void main (String[] args)
   {
       Integer[] arr = new Integer[20];
       
       System.out.print("input: ");
       Scanner sc = new Scanner(System.in);
       int size = 0;
       while(sc.hasNextInt() && size<20)
       {
          arr[size] = sc.nextInt();
          
          size++;
          
          
          
       }
       
       if(size ==0)
       {
          System.out.println("the tree is empty");
       }
       
       if(TreeWork.isHeap(arr, size))
       {
          System.out.println("IS a heap");
          
       }
       else
       {
          System.out.println("is NOT a heap");
          
       }
       
       TreeWork.printTree(arr, size);
      
   }
}
