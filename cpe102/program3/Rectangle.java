public class Rectangle implements Shape
{
   private int width, height;
   private java.awt.Point position;
   private java.awt.Color color;
   private boolean filled;
   
   public Rectangle(int width, int height, java.awt.Point position, java.awt.Color color, boolean filled)
   {
      this.width = width;
      this.height = height;
      this.position = position;
      this.color = color;
      this.filled = filled;
   }
   
   public int getWidth()
   {
      return this.width;
   }
   
   public void setWidth(int width)
   {
      this.width = width;
   }
   
   public int getHeight()
   {
      return this.height;
   }
   
   public void setHeight(int height)
   {
      this.height = height;
   }
   
   public boolean equals(Object o)
   {
      if(!(o instanceof Rectangle))
      {
         return false;
      }
      
      if(this.width != ((Rectangle)o).width)
      { 
         return false;
      }
      if(this.height != ((Rectangle)o).height)
      {
         return false;
      }
      if(!(this.position.equals(((Rectangle)o).position)))
      {
         return false;
      }
      if(!(this.color.equals(((Rectangle)o).color)))
      {
         return false;
      }
      if(this.filled != ((Rectangle)o).filled)
      {
         return false;
      }
      return true;
   }
   
    public double getArea()
   {
      return this.width * this.height;    
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

