public class ConvexPolygon implements Shape
{
   private java.awt.Point[]  vertices;
   private java.awt.Color color;
   private boolean filled;
   
   public ConvexPolygon(java.awt.Point[] vertices, java.awt.Color color, boolean filled)
   {
     
      this.vertices = vertices;
      this.color = color;
      this. filled = filled;
      
   }
   
   
   public java.awt.Point getVertex(int index)
   {
      return this.vertices[index];
   }
   
   public void setVertex(int index, java.awt.Point vertex)
   {
      this.vertices[index] = vertex;
   }
   
  public boolean equals(Object o)
   {
      if(!(o instanceof ConvexPolygon))
      {
         return false;
      }
      if(this.vertices.length != ((ConvexPolygon)o).vertices.length)
      {
         return false;
      }
      for (int i=0; i<this.vertices.length;i++)
      {
         if(!(this.vertices[i].equals( ((ConvexPolygon)o).vertices[i])))
         {
           
            
            return false;
         }
      }

      if(!(this.color.equals(((ConvexPolygon)o).color)))
      {
         return false;
      }
      if(this.filled != ((ConvexPolygon)o).filled)
      {
         return false;
      }
   
      return true;
   }

   public double getArea()
   {
      double sum1 =0.0;
      double sum2=0.0;
      for (int i = 0; i<this.vertices.length;i++)
      {
         if(i!=this.vertices.length-1)
         {
            sum1 = sum1 + this.vertices[i].getX()*this.vertices[i+1].getY();
            sum2 = sum2 +this.vertices[i].getY()*this.vertices[i+1].getX();
          
         }
         else
         {
            sum1 = sum1 + this.vertices[i].getX() * this.vertices[0].getY();
            sum2 = sum2 +this.vertices[i].getY() * this.vertices[0].getX();
         }
      }
      
      
      return 0.5 * (sum1-sum2);
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
      return this.vertices[0];
   } 
   
   public void setPosition(java.awt.Point position)
   {
      int xdiff, ydiff;
      xdiff = (int)position.getX() - (int)this.vertices[0].getX();
      ydiff = (int)position.getY() - (int)this.vertices[0].getY();
      this.vertices[0] = position;
      for (int i=1; i<this.vertices.length;i++)
      {
        java.awt.Point np = new java.awt.Point(xdiff+(int)this.vertices[i].getX(), 
            ydiff+(int)this.vertices[i].getY());
         
         this.setVertex(i,np);
      }
      
   }
   
   public void move(java.awt.Point delta)
   {
      double x = delta.getX();
      double y = delta.getY();
      for(int i=0; i<this.vertices.length;i++)
      {
         this.vertices[i].setLocation(this.vertices[i].getX() + x, this.vertices[i].getY() + y);
      }
   }
  
}