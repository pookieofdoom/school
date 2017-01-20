
public class MyPoint2D extends java.awt.geom.Point2D
{
   private double x, y, maxX, maxY;
   
   public MyPoint2D(double maxX, double maxY)
   {
      
      if(maxX <=0 || maxY <=0)
      {
         throw new java.lang.IllegalArgumentException(); 
         
      }
      this.maxX = maxX;
      this.maxY = maxY;
      
   }
   
   public MyPoint2D(double maxX, double maxY, double x, double y)
   {
      this(maxX, maxY);
      
      if(Math.abs(x) > maxX || Math.abs(y) > maxY)
      {
         throw new DimensionOutOfBoundsException();
      }
      
      this.x = x;
      this.y = y;
      
   }

 
   public double getX() 
   {
      return this.x;
   }


   public double getY() 
   {
     return this.y;
   }

   
   public void setLocation(double x, double y) 
   {
      if(Math.abs(x) > maxX || Math.abs(y) > maxY)
      {
         throw new DimensionOutOfBoundsException();
      }
      
      this.x = x;
      this.y = y;
      
   }
   
   

   public String toString()
   {
      return "(" + this.x +", " +this.y +")";
   }
}
