
public class MyPoint3D 
{
   private MyPoint2D point;
   private double maxZ, z;
   
   public MyPoint3D(double maxX, double maxY, double maxZ)
   {
      
      if(maxX <=0 || maxY <=0 || maxZ <=0)
      {
         throw new java.lang.IllegalArgumentException(); 
         
      }
      point = new MyPoint2D(maxX,maxY);
      
      this.maxZ = z;
  
     
     
   }
   
   public MyPoint3D(double maxX, double maxY, double maxZ, double x, double y, double z)
   {
      if(maxX <=0 || maxY <=0 || maxZ <=0)
      {
         throw new java.lang.IllegalArgumentException(); 
         
      }
      this.maxZ = z;
      
      if(Math.abs(x) > maxX || Math.abs(y) > maxY || Math.abs(z) > maxZ)
      {
         throw new DimensionOutOfBoundsException();
      }
     
      this.point.setLocation(0.0,0.0);
      this.z = z;
   }
   
   
   public double getX()
   {
      return this.point.getX();
   }
   
   public double getY()
   {
      return this.point.getY();
   }
   
   public double getZ()
   {
      return this.z;
   }
   
   public void setLocation(double x, double y, double z)
   {
      if(Math.abs(z) > maxZ)
      {
         throw new DimensionOutOfBoundsException();
      }
      
      this.point.setLocation(x, y);
      this.z = z;
   }
   
   public boolean equals(Object o)
   {
      if(o == null)
      {
         return false;
      }
      
      if(this.getClass()!= o.getClass())
      {
         return false;
      }
      
      if(this.point.getX() != ((MyPoint3D)o).point.getX())
      {
         return false;
      }
      
      if(this.point.getY() != ((MyPoint3D)o).point.getY())
      {
         return false;
      }
      if(this.z != ((MyPoint3D)o).z)
      {
            return false;
      }
      return true;
   }
   
   public String toString()
   {
      return "(" + this.point.getX() +", " +this.point.getY() +", " +this.z +")" ;
   }
}
