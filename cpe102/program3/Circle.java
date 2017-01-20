public class Circle implements Shape
{
   private double radius;
   private java.awt.Point position;
   private java.awt.Color color;
   private boolean filled;
   
   public Circle (double radius, java.awt.Point position, java.awt.Color color, boolean filled)
   {
      this.radius = radius;
      this.position = position;
      this.color = color;
      this.filled = filled;
   }
   
   public double getRadius()
   {
      return this.radius;
   }
   
   public void setRadius(double radius)
   {
      this.radius = radius;
   }
   
   public boolean equals(Object o)
   {
      if(!(o instanceof Circle))
      {
         return false;
      }
      if(this.radius != ((Circle)o).radius)
      { 
         return false;
      }
      if(!(this.position.equals( ((Circle)o).position)))
      {
         return false;
      }
      if(!(this.color.equals( ((Circle)o).color)))
      {
         return false;
      }
      if(this.filled != ((Circle)o).filled)
      {
         return false;
      }
      return true;
   }
   
   public double getArea()
   {
      return this.radius * this.radius * Math.PI;
   }
   
   public java.awt.Color getColor()
   {
      return this.color;
   }
   
   public void setColor(java.awt.Color color)
   {
      this.color = color;
   }
   
   public boolean getFilled()
   {
      if(this.filled)
      {
         return true;
      }
      
      return false;
   }
   
   public void setFilled(boolean filled)
   {
      this.filled = filled;
   }
   
   public java.awt.Point getPosition()
   {
      return this.position;
   } 
   
   public void setPosition(java.awt.Point position)
   {
      this.position = position;
   }
   
   public void move(java.awt.Point delta)
   {
      double x = delta.getX();
      double y = delta.getY();
      this.position.setLocation(this.position.getX() + x, this.position.getY() + y);
   }
   
}
