public class Student extends Person
{
   private double gpa;
   
   public Student(double gpa, String name, int legs)
   {
      super(name,legs);
      this.gpa = gpa;
   }
   
   public boolean equals(Object o)
   {
      if(!super.equals(o))
      {
         return false;
      }
      
      if(this.gpa != ((Student)o).gpa)
      {
         return false;
      }
      return true;
   }
   
   public String toString()
   {
      return super.toString() +" and a Student Object with a " +this.gpa +" gpa";
   }
}