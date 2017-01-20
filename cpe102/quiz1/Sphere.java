/**
 * @authorAnthony Dinh
 * @version Lab Quiz 1
 */
 
public class Sphere
{  
   //instance variable
   private double radius;
   
   //default constructor that has radius of 1.0
   public Sphere()
   {
      radius = 1.0;
   }
   
   //constructor that initializes the sphere's radius
   public Sphere(double radius)
   {
      this.radius = radius;
      if(this.radius <= 0)
      {
         throw new IllegalArgumentException();
      }
   }
   
   //methods
   
   public double getRadius()
   {
      return this.radius;
   }
   
   public void setRadius(double radius)
   {
      this.radius = radius; 
   }
   
   
   public double getSurfaceArea()
   {
      return 4.0 * Math.PI * this.radius * this.radius;
     
   }
   
   public double getVolume() 
   {
      return 4.0/3 * Math.PI * this.radius * this.radius * this.radius;
   }
   
   public boolean equals(Sphere other)
   {
      if(this.radius == other.radius)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   
   public String toString()
   {
      return ("The Sphere class is mutable!");
   }
 } 