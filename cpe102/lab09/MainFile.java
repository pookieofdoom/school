class MainFile {
   public static void main(String[] args) {
      System.out.println("Enter exception to throw:");
      java.util.Scanner sc = new java.util.Scanner(System.in);
      int i = sc.nextInt();
      BadCode test = new BadCode();
      try {
         if(i>=1 && i<=5) {
            test.dothethrow(i);
         }
      }
      catch (NullPointerException e) {
         System.out.println("caught NullPointerException!");
      }
      catch (ClassCastException e) {
         System.out.println("caught ClassCastException!");
      }
      catch (ArrayIndexOutOfBoundsException e) {
         System.out.println("caught ArrayIndexOutOfBoundsException!");
      }
      catch (MyChecked e)
      {
         System.out.println("caught MyChecked");
      }
      
      finally {
         System.out.println("end of program.");
      }
   }
}