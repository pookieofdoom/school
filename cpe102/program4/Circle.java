

public class Circle extends Ellipse
{

   public Circle (double radius, java.awt.Point position, java.awt.Color color, boolean filled)
   {
      super(radius,radius,position,color,filled);

   }

   public double getRadius()
   {
      return Math.sqrt(getArea()/Math.PI);

   }

   public void setRadius(double radius)
   {
      super.setSemiMinorAxis(radius);
      super.setSemiMajorAxis(radius);
   }

   public void setSemiMajorAxis(double x)
   {
      
      super.setSemiMajorAxis(x);
      super.setSemiMinorAxis(x);
   }

   public void setSemiMinorAxis(double x)
   {
      
      super.setSemiMinorAxis(x);
      super.setSemiMajorAxis(x);

   }












}
