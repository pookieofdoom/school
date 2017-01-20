import java.awt.Point;

public class Ellipse extends Shape
{

   private double semiMajorAxis, semiMinorAxis;
   private Point position;

   public Ellipse(double semiMajorAxis, double semiMinorAxis, Point position, java.awt.Color color, boolean filled)
   {
      super(color,filled);
      this.semiMajorAxis = semiMajorAxis;
      this.semiMinorAxis = semiMinorAxis;
      this.position = new Point(position);
   }

   public double getSemiMajorAxis()
   {
      return this.semiMajorAxis;
   }

   public void setSemiMajorAxis(double x)
   {
      if(x < this.semiMinorAxis && x != this.semiMajorAxis)
      {
         this.semiMajorAxis = this.semiMinorAxis;
         this.semiMinorAxis = x;
      }
      else
      {
         this.semiMajorAxis = x;
      }
   }
   public double getSemiMinorAxis()
   {
      return this.semiMinorAxis;

   }

   public void setSemiMinorAxis(double x)
   {
      if(x > this.semiMajorAxis && x != this.semiMinorAxis)
      {
         this.semiMinorAxis = this.semiMajorAxis;
         this.semiMajorAxis = x;
      }
      else
      {
         this.semiMinorAxis = x;
      }
   }

   public double getArea() 
   {

      return Math.PI * this.semiMajorAxis * this.semiMinorAxis;
   }



   public Point getPosition() 
   {

      return new Point(this.position);
   }


   public void setPosition(Point position) 
   {
      this.position = new Point(position); 
   }


   public void move(Point delta) 
   {
      double x = delta.getX();
      double y = delta.getY();
      this.position.setLocation(this.position.getX() + x, this.position.getY() + y);

   }
   
   public boolean equals(Object o)
   {
      if(!super.equals(o))
      {
         return false;
      }
      if(this.semiMajorAxis!= ((Ellipse)o).semiMajorAxis)
      {
         return false;
      }
      if(this.semiMinorAxis!= ((Ellipse)o).semiMinorAxis)
      {
         return false;
      }
      if(!(this.position.equals(((Ellipse)o).position)))
      {
         return false;
      }


      return true;
   }

}
