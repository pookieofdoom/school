public class Triangle implements Shape
{
   private java.awt.Point a,b,c;
   private java.awt.Color color;
   private boolean filled;
   
   public Triangle (java.awt.Point a, java.awt.Point b, java.awt.Point c, java.awt.Color color, 
      boolean filled)
   {
      this.a = a;
      this.b = b;
      this.c = c;
      this.color = color;
      this.filled = filled;
   }
   
   public java.awt.Point getVertexA()
   {
      return this.a;
   }
   
   public void setVertexA(java.awt.Point point)
   {
      this.a = point;
   }
   
   public java.awt.Point getVertexB()
   {
      return this.b;
   }
   
   public void setVertexB(java.awt.Point point)
   {
      this.b = point;
   }
   
   public java.awt.Point getVertexC()
   {
      return this.c;
   }
   
   public void setVertexC(java.awt.Point point)
   {
      this.c = point;
   }
   
   public boolean equals(Object o)
   {
      if(!(o instanceof Triangle))
      {
         return false;
      }
      
      if(!(this.a.equals( ((Triangle)o).a)))
      { 
         return false;
      }
      if(!(this.b.equals(((Triangle)o).b)))
      {
         return false;
      }
      if(!(this.c.equals(((Triangle)o).c)))
      {
         return false;
      }
      
      if(!(this.color.equals(((Triangle)o).color)))
      {
         return false;
      }
      if(this.filled != ((Triangle)o).filled)
      {
         return false;
      }
      return true;
   }

   public double getArea()
   {
      double x = a.getX()*(b.getY() - c.getY()) + b.getX()*(c.getY() - a.getY()) 
         + c.getX()*(a.getY() - b.getY());
      return Math.abs(x/2);    
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
      return this.a;
   } 
   
   public void setPosition(java.awt.Point position)
   {
      int xdiff, ydiff;
      xdiff = (int)position.getX() - (int)this.a.getX();
      ydiff = (int)position.getY() - (int)this.a.getY();
      this.a = position;
      java.awt.Point np = new java.awt.Point((int)b.getX()+xdiff,(int)b.getY()+ydiff);
      java.awt.Point np2 = new java.awt.Point((int)c.getX()+xdiff,(int)c.getY()+ydiff);
      this.b = np;
      this.c = np2;
   }
   
   public void move(java.awt.Point delta)
   {
      double x = delta.getX();
      double y = delta.getY();
      this.a.setLocation(this.a.getX() + x, this.a.getY() + y);
      this.b.setLocation(this.b.getX() + x, this.b.getY() + y);
      this.c.setLocation(this.c.getX() + x, this.c.getY() + y);
      
   }
}
   