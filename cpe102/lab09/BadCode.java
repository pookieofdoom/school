class BadCode {
   public void nullPointer() 
   {
      String a = null;
      System.out.println(a.toString());
   }

   public void classCast() 
   {
      Object x = new Integer(0);
      System.out.println((String)x);
   }

   public void arrayOOB() 
   {
      int lol[] = {3,4,5};
      System.out.println(lol[900000000]);
   }

   public void dothethrow(int which) throws MyChecked
   {
      if(which == 1) 
      {
         nullPointer();
      } 
      else if(which == 2) 
      {
         classCast();
      } 
      else if(which == 3) 
      {
         arrayOOB();
      }
      else if(which ==4)
      {
         MyChecked z = new MyChecked();
         z.checking();
      }
      else if(which == 5)
      {
         MyUnchecked a = new MyUnchecked();
         a.unchecking();
      }
   }
}